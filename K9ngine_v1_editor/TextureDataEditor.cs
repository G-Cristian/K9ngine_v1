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
            cbWrapS.DataSource = Enum.GetValues(typeof(Texture.WrapMode));
            cbWrapT.DataSource = Enum.GetValues(typeof(Texture.WrapMode));

            cbFilterMin.DataSource = Enum.GetValues(typeof(Texture.FilterMode));
            cbFilterMag.DataSource = Enum.GetValues(typeof(Texture.FilterMode));

            if (Texture != null)
            {
                Texture.TextureMetadata textureMetadata = Texture.Metadata;
                tbGUID.Text = textureMetadata.Guid.ToString();
                tbName.Text = Texture.Name;
                tbVersion.Text = textureMetadata.Version.ToString();
                tbFormat.Text = textureMetadata.Format.ToString();
                cbWrapS.SelectedIndex = ((int)textureMetadata.WrapModeS);
                cbWrapT.SelectedIndex = ((int)textureMetadata.WrapModeT);
                cbFilterMin.SelectedIndex = ((int)textureMetadata.FilterModeMin);
                cbFilterMag.SelectedIndex = ((int)textureMetadata.FilterModeMag);
                cbGammaCorrect.SelectedIndex = textureMetadata.GammaCorrect ? 0 : 1;
                cbFlipY.SelectedIndex = textureMetadata.FlipY ? 0 : 1;
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

            Texture.WrapMode wrapModeS;
            Enum.TryParse<Texture.WrapMode>(cbWrapS.SelectedValue.ToString(), out wrapModeS);
            textureMetadata.WrapModeS = wrapModeS;

            Texture.WrapMode wrapModeT;
            Enum.TryParse<Texture.WrapMode>(cbWrapT.SelectedValue.ToString(), out wrapModeT);
            textureMetadata.WrapModeT = wrapModeT;

            Texture.FilterMode filterModeMin;
            Enum.TryParse<Texture.FilterMode>(cbFilterMin.SelectedValue.ToString(), out filterModeMin);
            textureMetadata.FilterModeMin = filterModeMin;

            Texture.FilterMode filterModeMag;
            Enum.TryParse<Texture.FilterMode>(cbFilterMag.SelectedValue.ToString(), out filterModeMag);
            textureMetadata.FilterModeMag = filterModeMag;

            textureMetadata.GammaCorrect = cbGammaCorrect.SelectedIndex == 0;
            textureMetadata.FlipY = cbFlipY.SelectedIndex == 0;

            ResourceManager.GetInstance().SaveTextureMetadata(textureMetadata);
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            ResourceManager.GetInstance().ExportTexture(Texture);
        }
    }
}
