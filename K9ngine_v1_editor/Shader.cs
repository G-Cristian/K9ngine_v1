using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace K9ngine_v1_editor
{
    [Serializable]
    public class Shader:BaseAsset
    {
        public enum ShaderType { Vertex = 0, Fragment = 1 }
        [Serializable]
        public class ShaderItem
        {
            public ShaderType Type { get; set; }
            public string FileName { get; set; }
        }

        public List<ShaderItem> Items { get; set; }

        public Shader():base()
        {
            Items = new List<ShaderItem>();
        }
    }
}
