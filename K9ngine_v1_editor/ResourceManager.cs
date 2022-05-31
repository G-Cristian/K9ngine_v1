using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;
using System.IO;
using System.Xml.Serialization;
using System.Drawing.Imaging;

namespace K9ngine_v1_editor
{
    public class ResourceManager
    {
        public const string EditorDirectory = @"EditorAssets\";
        public const string GameDirectory = @"GameAssets\";
        public const string EditorTextureDirectory = @"EditorAssets\Textures\";
        public const string GameTextureDirectory = @"GameAssets\Textures\";
        public const string EditorShaderDirectory = @"EditorAssets\Shader\";
        public const string GameShaderDirectory = @"GameAssets\Shader\";
        public const string EditorMaterialDirectory = @"EditorAssets\Material\";
        public const string GameMaterialDirectory = @"GameAssets\Material\";
        public const string EditorMeshDirectory = @"EditorAssets\Mesh\";
        public const string GameMeshDirectory = @"GameAssets\Mesh\";
        public const string EditorSpriteDirectory = @"EditorAssets\Sprite\";
        public const string GameSpriteDirectory = @"GameAssets\Sprite\";

        private static ResourceManager _instance = null;
        private Dictionary<Int32, Texture> _textures = new Dictionary<Int32, Texture>();
        private Dictionary<Int32, Shader> _shaders = new Dictionary<Int32, Shader>();
        private Dictionary<Int32, Material> _materials = new Dictionary<Int32, Material>();
        private Dictionary<Int32, Mesh> _meshes = new Dictionary<Int32, Mesh>();
        private Dictionary<Int32, Sprite> _sprites = new Dictionary<Int32, Sprite>();

        public Dictionary<Int32, Texture>.ValueCollection Textures { get { return _textures.Values; } }
        public Dictionary<Int32, Material>.ValueCollection Materials { get { return _materials.Values; } }
        private ResourceManager() { }

        public static ResourceManager GetInstance()
        {
            if (_instance == null)
            {
                _instance = new ResourceManager();
            }

            return _instance;
        }

        #region Helpers
        private string GetMetadataFileFromPath(string path)
        {
            string metadataPath = Path.GetDirectoryName(path)+@"\";
            metadataPath+= Path.GetFileNameWithoutExtension(path);
            metadataPath += ".meta";

            return metadataPath;
        }
        private bool HasMetadataFile(string path)
        {
            return File.Exists(GetMetadataFileFromPath(path));
        }
        private string CopyFromPathToDestinyDirectory(string path, string directory)
        {
            Directory.CreateDirectory(directory);
            string newPath = Path.Combine(directory, Path.GetFileName(path));
            try
            {
                File.Copy(path, newPath);
            }
            catch (Exception)
            {

            }

            return newPath;
        }

        private void SaveString(FileStream file, String str)
        {
            byte[] strBytes = Encoding.ASCII.GetBytes(str);
            byte[] strLen = new byte[1];
            strLen[0] = (byte)strBytes.Length;
            file.Write(strLen, 0, strLen.Length);
            file.Write(strBytes, 0, strBytes.Length);
        }

        private void SaveFloat(FileStream file, float value)
        {
            var valueBytes = BitConverter.GetBytes(value);
            file.Write(valueBytes, 0, valueBytes.Length);
        }

        private void SaveInt(FileStream file, int value)
        {
            var valueBytes = BitConverter.GetBytes(value);
            file.Write(valueBytes, 0, valueBytes.Length);
        }

        private void SaveBool(FileStream file, bool value)
        {
            var valueBytes = BitConverter.GetBytes(value);
            file.Write(valueBytes, 0, valueBytes.Length);
        }

        #endregion

        #region Generics
        private T LoadMetadata<T>(string path) where T:class
        {
            T metadata = null;

            XmlSerializer ser = new XmlSerializer(typeof(T));
            using (FileStream file = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                metadata = ser.Deserialize(file) as T;
            }

            return metadata;
        }

        private void SaveMetadata<T>(T textureMetadata, string path) where T : class
        {
            XmlSerializer ser = new XmlSerializer(typeof(T));
            string fileName = GetMetadataFileFromPath(path);
            using (FileStream file = new FileStream(fileName, FileMode.Create, FileAccess.Write))
            {
                ser.Serialize(file, textureMetadata);
            }
        }

        private T GetResource<T>(int guid, Dictionary<Int32, T> container) where T : class
        {
            T outResource = null;

            if (container.TryGetValue(guid, out outResource))
            {
                return outResource;
            }

            return null;
        }

        #endregion

        #region Texture

        public Texture LoadTexture(String path)
        {
            if (!HasMetadataFile(path))
            {
                path = CopyFromPathToDestinyDirectory(path, EditorTextureDirectory);
            }
            path = Path.Combine(EditorTextureDirectory, Path.GetFileName(path));

            Int32 guid = Hasher.Hash(path);
            Texture texture = GetTexture(guid);
            if (texture == null)
            {
                Image data = Image.FromFile(path);
                string metadataPath = GetMetadataFileFromPath(path);
                Texture.TextureMetadata metadata = null;
                if (File.Exists(metadataPath))
                {
                    metadata = LoadMetadata<Texture.TextureMetadata>(metadataPath);
                    guid = metadata.Guid;
                }
                else
                {
                    Texture.FormatEnum format;
                    switch (data.PixelFormat)
                    {
                        case System.Drawing.Imaging.PixelFormat.Format24bppRgb:
                            format = Texture.FormatEnum.RGB24;
                            break;
                        case System.Drawing.Imaging.PixelFormat.Format32bppArgb:
                            format = Texture.FormatEnum.ARGB32;
                            break;
                        default:
                            throw new Exception("Format not supported.");
                    }

                    metadata = new Texture.TextureMetadata(guid, path, 0, format, false);
                    SaveMetadata<Texture.TextureMetadata>(metadata, metadata.Path);
                }

                texture = new Texture(data, metadata);
                AddTexture(guid, texture);
            }

            return texture;
        }

        public void SaveTextureMetadata(Texture.TextureMetadata textureMetadata)
        {
            SaveMetadata<Texture.TextureMetadata>(textureMetadata, textureMetadata.Path);
        }

        public void ExportTexture(Texture texture, string folder = GameTextureDirectory)
        {
            string filePath = folder;
            filePath += Path.GetFileNameWithoutExtension(texture.Metadata.Path);
            string infoPath = filePath + ".info";
            string texturePath = filePath + ".tex";

            Int32 nrChannels = (texture.Metadata.Format == Texture.FormatEnum.RGB24 ? 3 : 4);

            using (FileStream file = new FileStream(infoPath, FileMode.Create, FileAccess.Write))
            {
                //TODO: In the future, implement another aproach to take into consideration indianess
                var width = BitConverter.GetBytes(texture.Data.Width);
                var height = BitConverter.GetBytes(texture.Data.Height);
                var nrChannelsAsArray = BitConverter.GetBytes(nrChannels);
                var gammaCorrect = BitConverter.GetBytes(texture.Metadata.GammaCorrect);
                file.Write(width, 0, width.Length);
                file.Write(height, 0, height.Length);
                file.Write(nrChannelsAsArray, 0, nrChannelsAsArray.Length);
                file.Write(gammaCorrect, 0, gammaCorrect.Length);
            }
            Bitmap bitmap = (Bitmap)texture.Data;
            Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
            BitmapData data = bitmap.LockBits(rect, ImageLockMode.ReadOnly, bitmap.PixelFormat);

            // Get the address of the first line.
            IntPtr ptr = data.Scan0;

            // Declare an array to hold the bytes of the bitmap.
            //int bytes = Math.Abs(data.Stride) * bitmap.Height;
            int bytes = nrChannels * bitmap.Width * bitmap.Height;
            byte[] pixelsValues = new byte[bytes];
            // Copy the RGB values into the array.
            System.Runtime.InteropServices.Marshal.Copy(ptr, pixelsValues, 0, bytes);
            bitmap.UnlockBits(data);

            using (FileStream file = new FileStream(texturePath, FileMode.Create, FileAccess.Write))
            {
                //TODO: In the future, implement another aproach to take into consideration indianess
                file.Write(pixelsValues, 0, pixelsValues.Length);
            }
        }

        public void AddTexture(Int32 guid, Texture texture)
        {
            _textures[guid] = texture;
        }

        public Texture GetTexture(Int32 guid)
        {
            return GetResource<Texture>(guid, _textures);
        }

        #endregion

        #region Shader
        public Shader LoadShader(String path)
        {
            path = Path.Combine(EditorShaderDirectory, Path.GetFileName(path));
            Int32 guid = Hasher.Hash(path);
            Shader shader = GetShader(guid);
            if(shader == null)
            {
                shader = LoadMetadata<Shader>(path);
                AddShader(guid, shader);
            }

            return shader;
        }

        public void SaveShaderMetadata(Shader shader)
        {
            string path = EditorShaderDirectory + shader.Name + ".meta";
            if(shader.Guid == 0)
            {
                shader.Guid = Hasher.Hash(path);
            }
            SaveMetadata<Shader>(shader, path);
        }
        public void ExportShader(Shader shader, string folder = GameShaderDirectory)
        {
            string filePath = folder;
            filePath += shader.Name;
            string infoPath = filePath + ".shd";

            using (FileStream file = new FileStream(infoPath, FileMode.Create, FileAccess.Write))
            {
                foreach (Shader.ShaderItem item in shader.Items)
                {
                    byte[] type = new byte[1];
                    type[0] = ((byte)item.Type);
                    
                    byte[] fileName = Encoding.ASCII.GetBytes(item.FileName);
                    byte[] strLen = new byte[1];
                    strLen[0] = (byte)fileName.Length;

                    file.Write(type, 0, type.Length);
                    file.Write(strLen, 0, strLen.Length);
                    file.Write(fileName, 0, fileName.Length);

                    string srcPath = EditorShaderDirectory + item.FileName;
                    //string dstPath = folder + item.FileName;
                    CopyFromPathToDestinyDirectory(srcPath, folder);
                }
            }
        }
        public void AddShader(Int32 guid, Shader shader)
        {
            _shaders[guid] = shader;
        }
        public Shader GetShader(Int32 guid)
        {
            return GetResource<Shader>(guid, _shaders);
        }

        #endregion

        #region Material
        public Material LoadMaterial(String path)
        {
            path = Path.Combine(EditorMaterialDirectory, Path.GetFileName(path));
            Int32 guid = Hasher.Hash(path);
            Material material = GetMaterial(guid);
            if (material == null)
            {
                material = LoadMetadata<Material>(path);
                AddMaterial(guid, material);
            }

            return material;
        }

        public void SaveMaterialMetadata(Material material)
        {
            string path = EditorMaterialDirectory + material.Name + ".meta";
            if (material.Guid == 0)
            {
                material.Guid = Hasher.Hash(path);
            }
            SaveMetadata<Material>(material, path);
        }
        public void ExportMaterial(Material material, string folder = GameMaterialDirectory)
        {
            string filePath = folder;
            filePath += material.Name;
            string infoPath = filePath + ".mat";

            using (FileStream file = new FileStream(infoPath, FileMode.Create, FileAccess.Write))
            {
                //save shader name
                SaveString(file, material.ShaderName);
                SaveString(file, material.DiffuseTexture);
                SaveString(file, material.SpecularTexture);
                SaveFloat(file, material.Shininess);
                SaveInt(file, ((int)material.Pass));
                SaveInt(file, ((int)material.DepthSortOrder));
                SaveBool(file, material.RenderToTexture);
                SaveBool(file, material.Culling);
            }
        }

        public void AddMaterial(Int32 guid, Material material)
        {
            _materials[guid] = material;
        }
        public Material GetMaterial(Int32 guid)
        {
            return GetResource<Material>(guid, _materials);
        }

        #endregion

        #region Mesh

        public Mesh LoadMesh(String path)
        {
            path = Path.Combine(EditorMeshDirectory, Path.GetFileName(path));
            Int32 guid = Hasher.Hash(path);
            Mesh mesh = GetMesh(guid);
            if (mesh == null)
            {
                mesh = LoadMetadata<Mesh>(path);
                AddMesh(guid, mesh);
            }

            return mesh;
        }

        public void SaveMeshMetadata(Mesh mesh)
        {
            string path = EditorMeshDirectory + mesh.Name + ".meta";
            if (mesh.Guid == 0)
            {
                mesh.Guid = Hasher.Hash(path);
            }
            SaveMetadata<Mesh>(mesh, path);
        }

        public void ExportMesh(Mesh mesh, string folder = GameMeshDirectory)
        {
            string filePath = folder;
            filePath += mesh.Name;
            string infoPath = filePath + ".mesh";

            using (FileStream file = new FileStream(infoPath, FileMode.Create, FileAccess.Write))
            {
                //Save number of vertices
                SaveInt(file, mesh.Vertices.Count);
                //Save number of Indices
                SaveInt(file, mesh.Indices.Count);

                //Save vertices
                foreach (Vertex vertex in mesh.Vertices)
                {
                    SaveFloat(file, vertex.Position.x);
                    SaveFloat(file, vertex.Position.y);
                    SaveFloat(file, vertex.Position.z);
                    SaveFloat(file, vertex.Normal.x);
                    SaveFloat(file, vertex.Normal.y);
                    SaveFloat(file, vertex.Normal.z);
                    SaveFloat(file, vertex.TextureCoord.x);
                    SaveFloat(file, vertex.TextureCoord.y);
                }

                //Save Indices
                foreach (int index in mesh.Indices)
                {
                    SaveInt(file, index);
                }    
            }
        }

        public void AddMesh(Int32 guid, Mesh mesh)
        {
            _meshes[guid] = mesh;
        }
        public Mesh GetMesh(Int32 guid)
        {
            return GetResource<Mesh>(guid, _meshes);
        }

        #endregion

        #region Sprite
        public Sprite LoadSprite(String path)
        {
            path = Path.Combine(EditorSpriteDirectory, Path.GetFileName(path));
            Int32 guid = Hasher.Hash(path);
            Sprite sprite = GetSprite(guid);
            if (sprite == null)
            {
                sprite = LoadMetadata<Sprite>(path);
                AddSprite(guid, sprite);
            }

            return sprite;
        }
        public void SaveSpriteMetadata(Sprite sprite)
        {
            string path = EditorMeshDirectory + sprite.Name + ".meta";
            if (sprite.Guid == 0)
            {
                sprite.Guid = Hasher.Hash(path);
            }
            SaveMetadata<Sprite>(sprite, path);
        }
        public void ExportSprite(Sprite sprite, string folder = GameSpriteDirectory)
        {
            string filePath = folder;
            filePath += sprite.Name;
            string infoPath = filePath + ".sprite";

            using (FileStream file = new FileStream(infoPath, FileMode.Create, FileAccess.Write))
            {
                SaveString(file, sprite.SpriteSheetName);
                SaveString(file, sprite.MaterialName);
                SaveString(file, sprite.QuadName);
            }
        }
        public void AddSprite(Int32 guid, Sprite sprite)
        {
            _sprites[guid] = sprite;
        }
        public Sprite GetSprite(Int32 guid)
        {
            return GetResource<Sprite>(guid, _sprites);
        }

        #endregion
    }
}
