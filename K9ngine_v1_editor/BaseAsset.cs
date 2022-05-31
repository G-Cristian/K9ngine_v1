using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace K9ngine_v1_editor
{
    [Serializable]
    public class BaseAsset
    {
        public virtual Int32 Guid { get; set; }
        public virtual string Name { get; set; }

        public BaseAsset()
        {
            Guid = 0;
            Name = String.Empty;
        }
    }
}
