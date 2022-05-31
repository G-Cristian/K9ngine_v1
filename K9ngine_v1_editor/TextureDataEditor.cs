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
    public partial class TextureDataEditor : Form
    {
        public Texture Texture { get; set; }
        public TextureDataEditor()
        {
            InitializeComponent();
        }

        private void TextureDataEditor_Load(object sender, EventArgs e)
        {
            if(Texture != null)
            {
                Texture.TextureMetadata textureMetadata = Texture.Metadata;
                tbGUID.Text = textureMetadata.Guid.ToString();
                tbName.Text = Texture.Name;
                tbVersion.Text = textureMetadata.Version.ToString();
                tbFormat.Text = textureMetadata.Format.ToString();
                cbGammaCorrect.SelectedIndex = textureMetadata.GammaCorrect ? 0 : 1;

            }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            Texture.TextureMetadata textureMetadata = Texture.Metadata;
            uint version;
            if(uint.TryParse(tbVersion.Text, out version))
            {
                textureMetadata.Version = version;
            }
            textureMetadata.GammaCorrect = cbGammaCorrect.SelectedIndex == 0;

            ResourceManager.GetInstance().SaveTextureMetadata(textureMetadata);
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            ResourceManager.GetInstance().ExportTexture(Texture);
        }
    }
}
