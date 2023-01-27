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
    public partial class ShaderEditor : Form
    {
        public Shader Shader { get; set; }
        public ShaderEditor()
        {
            InitializeComponent();
        }

        private void ShaderEditor_Load(object sender, EventArgs e)
        {
            if(Shader == null)
            {
                tbName.ReadOnly = false;
            }
            else
            {
                tbName.ReadOnly = true;
                CompleteShaderData();
            }
        }

        private void CompleteShaderData()
        {
            if(Shader != null)
            {
                tbGUID.Text = Shader.Guid.ToString();
                tbName.Text = Shader.Name;
                foreach (Shader.ShaderItem shaderItem in Shader.Items)
                {
                    switch (shaderItem.Type)
                    {
                        case Shader.ShaderType.Vertex:
                            tbVertexShader.Text = shaderItem.FileName;
                            break;
                        case Shader.ShaderType.Fragment:
                            tbFragmentShader.Text = shaderItem.FileName;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private void FillShaderData()
        {
            if (Shader == null)
            {
                Shader = new Shader();
            }

            Int32 guid;
            if (string.IsNullOrEmpty(tbGUID.Text))
            {
                guid = 0;
            }
            else
            {
                if(!Int32.TryParse(tbGUID.Text, out guid))
                {
                    guid = 0;
                }
            }

            Shader.Guid = guid;
            Shader.Name = tbName.Text;
            
            Shader.ShaderItem shaderItem = new Shader.ShaderItem();
            shaderItem.Type = Shader.ShaderType.Vertex;
            shaderItem.FileName = tbVertexShader.Text;
            Shader.Items.Add(shaderItem);

            shaderItem = new Shader.ShaderItem();
            shaderItem.Type = Shader.ShaderType.Fragment;
            shaderItem.FileName = tbFragmentShader.Text;
            Shader.Items.Add(shaderItem);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            FillShaderData();
            ResourceManager.GetInstance().SaveShaderMetadata(Shader);
            tbGUID.Text = Shader.Guid.ToString();
            tbName.ReadOnly = true;
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            if(Shader != null)
            {
                FillShaderData();
                ResourceManager.GetInstance().ExportShader(Shader);
            }
        }
    }
}
