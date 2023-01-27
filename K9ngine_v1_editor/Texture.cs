using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;
using System.IO;

namespace K9ngine_v1_editor
{
    public class Texture : BaseAsset
    {
        public enum FormatEnum { RGB24, ARGB32 };
        public enum WrapMode { REPEAT, CLAMP_TO_EDGE };
        public enum FilterMode { NEAREST, LINEAR, LINEAR_MIPMAP_LINEAR };
        [Serializable]
        public class TextureMetadata
        {
            public Int32 Guid { get; set; }
            public String Path { get; set; }
            public uint Version { get; set; }
            public FormatEnum Format { get; set; }
            public WrapMode WrapModeS { get; set; }
            public WrapMode WrapModeT { get; set; }
            public FilterMode FilterModeMin { get; set; }
            public FilterMode FilterModeMag { get; set; }
            public bool GammaCorrect { get; set; }
            public bool FlipY { get; set; }

            public TextureMetadata()
            {

            }
            public TextureMetadata(Int32 guid, String path, uint version, FormatEnum format, bool gammaCorrect, bool flipY)
            {
                Guid = guid;
                Path = path;
                Version = version;
                Format = format;
                GammaCorrect = gammaCorrect;
                FlipY = flipY;
            }
        }
        public override int Guid { get => Metadata != null ? Metadata.Guid : 0; set { if (Metadata != null) { Metadata.Guid = value; } } }

        public override string Name { get => Metadata != null ? Path.GetFileNameWithoutExtension(Metadata.Path) : string.Empty; set { if (Metadata != null) { Metadata.Path = value;} } }
        public Image Data { get; private set; }
        public TextureMetadata Metadata { get; private set; }

        public Texture(Image data, TextureMetadata metadata)
        {
            Data = data;
            Metadata = metadata;
        }
    }
}
