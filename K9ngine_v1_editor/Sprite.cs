using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace K9ngine_v1_editor
{
    [Serializable]
    public class Sprite : BaseAsset
    {
        public String SpriteSheetName { get; set; }
        public String MaterialName { get; set; }
        public String QuadName { get; set; }
        public Sprite()
        {
            SpriteSheetName = String.Empty;
            MaterialName = String.Empty;
            QuadName = String.Empty;
        }
    }
}
