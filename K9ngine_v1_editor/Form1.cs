using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace K9ngine_v1_editor
{
    public partial class Form1 : Form
    {
        private Dictionary<Int32, AssetIcon> _assetsIcons = new System.Collections.Generic.Dictionary<Int32, AssetIcon>();


        public Form1()
        {
            InitializeComponent();
        }

        private void LoadEditorAssets(string assetsDirectory, Action<string> loadingFunction, bool loadingMetaExtention)
        {
            foreach (string file in Directory.GetFiles(assetsDirectory))
            {
                string extension = Path.GetExtension(file);
                if((loadingMetaExtention && extension == ".meta") ||
                    (!loadingMetaExtention && extension != ".meta"))
                {
                    loadingFunction(file);
                }
            }
        }

        private void LoadEditorTextureAssets()
        {
            LoadEditorAssets(ResourceManager.EditorTextureDirectory, LoadTexture, false);
        }

        private void LoadEditorShaderAssets()
        {
            LoadEditorAssets(ResourceManager.EditorShaderDirectory, LoadShader, true);
        }
        private void LoadEditorMaterialAssets()
        {
            LoadEditorAssets(ResourceManager.EditorMaterialDirectory, LoadMaterial, true);
        }

        private void LoadEditorSpriteAssets()
        {
            LoadEditorAssets(ResourceManager.EditorSpriteDirectory, LoadSprite, true);
        }

        private void LoadAllEditorAssets()
        {
            LoadEditorTextureAssets();
            LoadEditorShaderAssets();
            LoadEditorMaterialAssets();
            LoadEditorSpriteAssets();
        }

        private void AddAsset(BaseAsset asset, Image image)
        {
            if (!_assetsIcons.ContainsKey(asset.Guid))
            {
                AssetIcon assetIcon = new AssetIcon();
                assetIcon.AssetImage = image;
                assetIcon.AssetName = Path.GetFileName(asset.Name);
                assetIcon.Tag = asset;
                assetIcon.DoubleClickEvent += AssetIcon_DoubleClick;
                _assetsIcons.Add(asset.Guid, assetIcon);
                flpAssets.Controls.Add(assetIcon);
            }
            else
            {
                MessageBox.Show(this,
                    "Asset with Guid " + asset.Guid + " already exists (path: " + asset.Name + ").",
                    "Error adding asset");
            }
        }

        private void LoadTexture(string path)
        {
            Texture texture = ResourceManager.GetInstance().LoadTexture(path);
            AddAsset(texture, texture.Data);
        }

        private void LoadShader(string path)
        {
            Shader shader = ResourceManager.GetInstance().LoadShader(path);
            AddAsset(shader, null);
        }

        private void LoadMaterial(string path)
        {
            Material material = ResourceManager.GetInstance().LoadMaterial(path);
            AddAsset(material, null);
        }

        private void LoadSprite(string path)
        {
            Sprite sprite = ResourceManager.GetInstance().LoadSprite(path);
            AddAsset(sprite, null);
        }

        private void ShowTextureDataEditorDialog(Texture texture)
        {
            TextureDataEditor textureDataEditor = new TextureDataEditor();
            textureDataEditor.Texture = texture;
            textureDataEditor.ShowDialog(this);
        }

        private Shader ShowShaderDataEditorDialog(Shader shader)
        {
            ShaderEditor shaderDataEditor = new ShaderEditor();
            shaderDataEditor.Shader = shader;
            shaderDataEditor.ShowDialog(this);

            return shaderDataEditor.Shader;
        }

        private Material ShowMaterialDataEditorDialog(Material material)
        {
            MaterialEditor materialDataEditor = new MaterialEditor();
            materialDataEditor.Material = material;
            materialDataEditor.ShowDialog(this);

            return materialDataEditor.Material;
        }

        private Sprite ShowSpriteDataEditorDialog(Sprite sprite)
        {
            SpriteEditor spriteDataEditor = new SpriteEditor();
            spriteDataEditor.Sprite = sprite;
            spriteDataEditor.ShowDialog(this);

            return spriteDataEditor.Sprite;
        }

        private void AssetIcon_DoubleClick(object sender, EventArgs e)
        {
            AssetIcon assetIcon = sender as AssetIcon;
            if (assetIcon != null)
            {
                if (assetIcon.Tag is Texture)
                {
                    Texture texture = assetIcon.Tag as Texture;
                    if (texture != null)
                    {
                        ShowTextureDataEditorDialog(texture);
                    }
                }
                else if(assetIcon.Tag is Shader)
                {
                    Shader shader = assetIcon.Tag as Shader;
                    if (shader != null)
                    {
                        ShowShaderDataEditorDialog(shader);
                    }
                }
                else if (assetIcon.Tag is Material)
                {
                    Material material = assetIcon.Tag as Material;
                    if (material != null)
                    {
                        ShowMaterialDataEditorDialog(material);
                    }
                }
                else if (assetIcon.Tag is Sprite)
                {
                    Sprite sprite = assetIcon.Tag as Sprite;
                    if (sprite != null)
                    {
                        ShowSpriteDataEditorDialog(sprite);
                    }
                }
            }
        }

        private void textureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(openFileDialog1.ShowDialog(this) == DialogResult.OK)
            {
                try
                {
                    LoadTexture(openFileDialog1.FileName);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(this, ex.Message, "Error loading texture.");
                }
            }
        }

        private void tsmShader_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog(this) == DialogResult.OK)
            {
                try
                {
                    LoadShader(openFileDialog1.FileName);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(this, ex.Message, "Error loading shader.");
                }
            }
        }

        private void CreateAssetDirectoryIfNeeded(String directory)
        {
            if (!Directory.GetDirectories(Directory.GetCurrentDirectory()).Contains(directory))
            {
                Directory.CreateDirectory(directory);
            }
        }
        private void CreateEditorAssetsDirectoryIfNeeded()
        {
            CreateAssetDirectoryIfNeeded(ResourceManager.EditorDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.EditorTextureDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.EditorShaderDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.EditorMaterialDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.EditorSpriteDirectory);
        }
        private void CreateGameAssetsDirectoriesIfNeeded()
        {
            CreateAssetDirectoryIfNeeded(ResourceManager.GameDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.GameTextureDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.GameShaderDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.GameMaterialDirectory);
            CreateAssetDirectoryIfNeeded(ResourceManager.GameSpriteDirectory);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            CreateEditorAssetsDirectoryIfNeeded();
            CreateGameAssetsDirectoriesIfNeeded();
            LoadAllEditorAssets();
        }

        private void tsmCreateShader_Click(object sender, EventArgs e)
        {
            Shader shader = ShowShaderDataEditorDialog(null);
            if(shader != null)
            {
                LoadShader(shader.Name + ".meta");
            }
        }

        private void tsmMaterial_Click(object sender, EventArgs e)
        {
            Material material = ShowMaterialDataEditorDialog(null);
            if (material != null)
            {
                LoadMaterial(material.Name + ".meta");
            }
        }

        private void tsmCreateQuad_Click(object sender, EventArgs e)
        {

        }

        private void tsmSprite_Click(object sender, EventArgs e)
        {
            Sprite sprite = ShowSpriteDataEditorDialog(null);
            if (sprite != null)
            {
                LoadSprite(sprite.Name + ".meta");
            }
        }
    }
}
