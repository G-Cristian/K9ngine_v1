
namespace K9ngine_v1_editor
{
    partial class MaterialEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tbName = new System.Windows.Forms.TextBox();
            this.tbGUID = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tbShaderName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.tbShininess = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.cbPassGroup = new System.Windows.Forms.ComboBox();
            this.cbDepthSortGroup = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.chbCulling = new System.Windows.Forms.CheckBox();
            this.chbRenderToTexture = new System.Windows.Forms.CheckBox();
            this.btnExport = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.cbDiffuse = new System.Windows.Forms.ComboBox();
            this.tbSpecular = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbName
            // 
            this.tbName.Location = new System.Drawing.Point(111, 44);
            this.tbName.Name = "tbName";
            this.tbName.Size = new System.Drawing.Size(150, 23);
            this.tbName.TabIndex = 9;
            // 
            // tbGUID
            // 
            this.tbGUID.Location = new System.Drawing.Point(111, 12);
            this.tbGUID.Name = "tbGUID";
            this.tbGUID.ReadOnly = true;
            this.tbGUID.Size = new System.Drawing.Size(150, 23);
            this.tbGUID.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(11, 44);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(39, 15);
            this.label4.TabIndex = 7;
            this.label4.Text = "Name";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 15);
            this.label1.TabIndex = 6;
            this.label1.Text = "GUID";
            // 
            // tbShaderName
            // 
            this.tbShaderName.Location = new System.Drawing.Point(111, 73);
            this.tbShaderName.Name = "tbShaderName";
            this.tbShaderName.Size = new System.Drawing.Size(150, 23);
            this.tbShaderName.TabIndex = 11;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 73);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(78, 15);
            this.label2.TabIndex = 10;
            this.label2.Text = "Shader Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 102);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(85, 15);
            this.label3.TabIndex = 12;
            this.label3.Text = "Diffuse Texture";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(11, 131);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(93, 15);
            this.label5.TabIndex = 14;
            this.label5.Text = "Specular Texture";
            // 
            // tbShininess
            // 
            this.tbShininess.Location = new System.Drawing.Point(111, 160);
            this.tbShininess.Name = "tbShininess";
            this.tbShininess.Size = new System.Drawing.Size(150, 23);
            this.tbShininess.TabIndex = 17;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(11, 160);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(56, 15);
            this.label6.TabIndex = 16;
            this.label6.Text = "Shininess";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 193);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(66, 15);
            this.label7.TabIndex = 18;
            this.label7.Text = "Pass Group";
            // 
            // cbPassGroup
            // 
            this.cbPassGroup.FormattingEnabled = true;
            this.cbPassGroup.Location = new System.Drawing.Point(111, 190);
            this.cbPassGroup.Name = "cbPassGroup";
            this.cbPassGroup.Size = new System.Drawing.Size(150, 23);
            this.cbPassGroup.TabIndex = 19;
            // 
            // cbDepthSortGroup
            // 
            this.cbDepthSortGroup.FormattingEnabled = true;
            this.cbDepthSortGroup.Location = new System.Drawing.Point(111, 219);
            this.cbDepthSortGroup.Name = "cbDepthSortGroup";
            this.cbDepthSortGroup.Size = new System.Drawing.Size(150, 23);
            this.cbDepthSortGroup.TabIndex = 21;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(12, 222);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(99, 15);
            this.label8.TabIndex = 20;
            this.label8.Text = "Depth Sort Group";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.chbCulling);
            this.groupBox1.Controls.Add(this.chbRenderToTexture);
            this.groupBox1.Location = new System.Drawing.Point(391, 17);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(306, 225);
            this.groupBox1.TabIndex = 24;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Render State";
            // 
            // chbCulling
            // 
            this.chbCulling.AutoSize = true;
            this.chbCulling.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.chbCulling.Location = new System.Drawing.Point(60, 45);
            this.chbCulling.Name = "chbCulling";
            this.chbCulling.Size = new System.Drawing.Size(64, 19);
            this.chbCulling.TabIndex = 25;
            this.chbCulling.Text = "Culling";
            this.chbCulling.UseVisualStyleBackColor = true;
            // 
            // chbRenderToTexture
            // 
            this.chbRenderToTexture.AutoSize = true;
            this.chbRenderToTexture.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.chbRenderToTexture.Location = new System.Drawing.Point(6, 22);
            this.chbRenderToTexture.Name = "chbRenderToTexture";
            this.chbRenderToTexture.Size = new System.Drawing.Size(118, 19);
            this.chbRenderToTexture.TabIndex = 24;
            this.chbRenderToTexture.Text = "Render to Texture";
            this.chbRenderToTexture.UseVisualStyleBackColor = true;
            // 
            // btnExport
            // 
            this.btnExport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnExport.Location = new System.Drawing.Point(622, 248);
            this.btnExport.Name = "btnExport";
            this.btnExport.Size = new System.Drawing.Size(75, 23);
            this.btnExport.TabIndex = 25;
            this.btnExport.Text = "Export";
            this.btnExport.UseVisualStyleBackColor = true;
            this.btnExport.Click += new System.EventHandler(this.btnExport_Click);
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSave.Location = new System.Drawing.Point(703, 247);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 26;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // cbDiffuse
            // 
            this.cbDiffuse.FormattingEnabled = true;
            this.cbDiffuse.Location = new System.Drawing.Point(111, 102);
            this.cbDiffuse.Name = "cbDiffuse";
            this.cbDiffuse.Size = new System.Drawing.Size(150, 23);
            this.cbDiffuse.TabIndex = 27;
            // 
            // tbSpecular
            // 
            this.tbSpecular.Location = new System.Drawing.Point(111, 128);
            this.tbSpecular.Name = "tbSpecular";
            this.tbSpecular.Size = new System.Drawing.Size(150, 23);
            this.tbSpecular.TabIndex = 28;
            // 
            // MaterialEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(790, 282);
            this.Controls.Add(this.tbSpecular);
            this.Controls.Add(this.cbDiffuse);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnExport);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.cbDepthSortGroup);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.cbPassGroup);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.tbShininess);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tbShaderName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbName);
            this.Controls.Add(this.tbGUID);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Name = "MaterialEditor";
            this.Text = "MaterialEditor";
            this.Load += new System.EventHandler(this.MaterialEditor_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbName;
        private System.Windows.Forms.TextBox tbGUID;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbShaderName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tbShininess;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cbPassGroup;
        private System.Windows.Forms.ComboBox cbDepthSortGroup;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox chbCulling;
        private System.Windows.Forms.CheckBox chbRenderToTexture;
        private System.Windows.Forms.Button btnExport;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.ComboBox cbDiffuse;
        private System.Windows.Forms.TextBox tbSpecular;
    }
}