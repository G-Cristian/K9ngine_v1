using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace K9ngine_v1_editor
{
    [Serializable]
    public class Material:BaseAsset
    {
        public enum PassGroup { Deferred_Geometry, Deferred_Lighting, Pass_One, Pass_Two, PassThree };
        public enum DepthSortOrderGroup { No_Sort, Increasing, Decreasing };

        public string ShaderName { get; set; }
        public string DiffuseTexture { get; set; }
        public string SpecularTexture { get; set; }
        public float Shininess { get; set; }
        public PassGroup Pass { get; set; }
        public DepthSortOrderGroup DepthSortOrder { get; set; }
        public bool RenderToTexture { get; set; }
        public bool Culling { get; set; }
        
        public Material():base()
        {
            ShaderName = String.Empty;
            DiffuseTexture = String.Empty;
            SpecularTexture = String.Empty;
            Shininess = 0.0f;
            Pass = PassGroup.Pass_One;
            DepthSortOrder = DepthSortOrderGroup.No_Sort;
            RenderToTexture = false;
            Culling = true;
        }


    }
}
