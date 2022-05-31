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
    public partial class MaterialEditor : Form
    {
        public Material Material { get; set; }
        public MaterialEditor()
        {
            InitializeComponent();
        }

        private void MaterialEditor_Load(object sender, EventArgs e)
        {
            cbPassGroup.DataSource = Enum.GetValues(typeof(Material.PassGroup));
            cbDepthSortGroup.DataSource = Enum.GetValues(typeof(Material.DepthSortOrderGroup));

            FillComboBox(cbDiffuse, ResourceManager.GetInstance().Textures.ToList());
            //FillComboBox(cbSpecular, ResourceManager.GetInstance().Textures.ToList());

            if (Material == null)
            {
                tbName.ReadOnly = false;
            }
            else
            {
                tbName.ReadOnly = true;
                CompleteMaterialData();
            }
        }
        private void FillComboBox<T>(ComboBox comboBox, T data)
        {
            comboBox.ValueMember = "Name";
            comboBox.DisplayMember = "Name";
            comboBox.DataSource = data;
        }
        private void CompleteMaterialData()
        {
            if (Material != null)
            {
                tbGUID.Text = Material.Guid.ToString();
                tbName.Text = Material.Name;
                tbShaderName.Text = Material.ShaderName;
                //cbDiffuse.SelectedIndex = searchIndex<Texture>(cbDiffuse, Material.DiffuseTexture);
                //cbSpecular.SelectedIndex= searchIndex<Texture>(cbSpecular, Material.SpecularTexture);
                cbDiffuse.SelectedValue= Material.DiffuseTexture;
                tbSpecular.Text = Material.SpecularTexture;
                tbShininess.Text = Material.Shininess.ToString();
                cbPassGroup.SelectedIndex = ((int)Material.Pass);
                cbDepthSortGroup.SelectedIndex = ((int)Material.DepthSortOrder);
                chbRenderToTexture.Checked = Material.RenderToTexture;
                chbCulling.Checked = Material.Culling;
            }
        }

        private int searchIndex<T>(ComboBox comboBox, string name) where T:BaseAsset
        {
            for(int i = 0; i < comboBox.Items.Count; i++)
            {
                T itemVal = comboBox.Items[i] as T;
                if (itemVal != null && itemVal.Guid.ToString() == name)
                {
                    return i;
                }
            }

            return 0;
        }

        private void FillMaterialData()
        {
            if (Material == null)
            {
                Material = new Material();
            }

            Int32 guid;
            if (string.IsNullOrEmpty(tbGUID.Text))
            {
                guid = 0;
            }
            else
            {
                if (!Int32.TryParse(tbGUID.Text, out guid))
                {
                    guid = 0;
                }
            }

            Material.Guid = guid;
            Material.Name = tbName.Text;
            Material.ShaderName = tbShaderName.Text;
            Material.DiffuseTexture = cbDiffuse.SelectedValue?.ToString();
            Material.SpecularTexture = tbSpecular.Text;
            float shininess = 0.0f;
            if (string.IsNullOrEmpty(tbShininess.Text))
            {
                shininess = 0.0f;
            }
            else
            {
                if (!float.TryParse(tbShininess.Text, out shininess))
                {
                    shininess = 0.0f;
                }
            }
            Material.Shininess = shininess;

            Material.PassGroup pass;
            Enum.TryParse<Material.PassGroup>(cbPassGroup.SelectedValue.ToString(), out pass);
            Material.Pass = pass;

            Material.DepthSortOrderGroup depthSortOrder;
            Enum.TryParse<Material.DepthSortOrderGroup>(cbDepthSortGroup.SelectedValue.ToString(), out depthSortOrder);
            Material.DepthSortOrder = depthSortOrder;

            Material.RenderToTexture = chbRenderToTexture.Checked;
            Material.Culling = chbCulling.Checked;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            FillMaterialData();
            ResourceManager.GetInstance().SaveMaterialMetadata(Material);
            tbGUID.Text = Material.Guid.ToString();
            tbName.ReadOnly = true;
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            if (Material != null)
            {
                FillMaterialData();
                ResourceManager.GetInstance().ExportMaterial(Material);
            }
        }
    }
}
