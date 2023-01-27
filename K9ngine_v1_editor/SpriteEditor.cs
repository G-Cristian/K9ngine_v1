using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace K9ngine_v1_editor
{
    public partial class SpriteEditor : Form
    {
        public Sprite Sprite { get; set; }
        public SpriteEditor()
        {
            InitializeComponent();
        }

        private void SpriteEditor_Load(object sender, EventArgs e)
        {
            FillComboBox(cbSpritesheets, ResourceManager.GetInstance().Textures.ToList());
            FillComboBox(cbMaterials, ResourceManager.GetInstance().Materials.ToList());

            if (Sprite == null)
            {
                tbName.ReadOnly = false;
            }
            else
            {
                tbName.ReadOnly = true;
                CompleteData();
            }
        }

        private void FillComboBox<T>(ComboBox comboBox, T data)
        {
            comboBox.ValueMember = "Name";
            comboBox.DisplayMember = "Name";
            comboBox.DataSource = data;
        }

        private void CompleteData()
        {
            if(Sprite != null)
            {
                tbGUID.Text = Sprite.Guid.ToString();
                tbName.Text = Sprite.Name;
                //TODO
            }
        }

        private int searchIndex<T>(ComboBox comboBox, string name) where T : BaseAsset
        {
            for (int i = 0; i < comboBox.Items.Count; i++)
            {
                T itemVal = comboBox.Items[i] as T;
                if (itemVal != null && itemVal.Guid.ToString() == name)
                {
                    return i;
                }
            }

            return 0;
        }
    }
}
