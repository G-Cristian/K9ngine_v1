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
    public partial class AssetIcon : UserControl
    {
        public event EventHandler DoubleClickEvent;
        public AssetIcon()
        {
            InitializeComponent();
        }

        private Image _assetImage = null;
        public Image AssetImage
        {
            get
            {
                return _assetImage;
            }
            set
            {
                _assetImage = value;
                pictureBox1.Image = _assetImage;
            }
        }

        private String _assetName = "";
        public String AssetName
        {
            get
            {
                return _assetName;
            }
            set
            {
                _assetName = value;
                textBox1.Text = _assetName;
            }
        }
        private void SelectItem()
        {
            BackColor = Color.Blue;
        }
        private void AssetIcon_Click(object sender, EventArgs e)
        {
            SelectItem();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            SelectItem();
        }

        private void pictureBox1_DoubleClick(object sender, EventArgs e)
        {
            if(DoubleClickEvent != null)
            {
                DoubleClickEvent.Invoke(this, e);
            }
        }

        private void AssetIcon_DoubleClick(object sender, EventArgs e)
        {
            if (DoubleClickEvent != null)
            {
                DoubleClickEvent.Invoke(sender, e);
            }
        }
    }
}
