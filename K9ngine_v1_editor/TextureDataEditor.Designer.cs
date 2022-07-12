
namespace K9ngine_v1_editor
{
    partial class TextureDataEditor
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.tbGUID = new System.Windows.Forms.TextBox();
            this.tbName = new System.Windows.Forms.TextBox();
            this.tbVersion = new System.Windows.Forms.TextBox();
            this.tbFormat = new System.Windows.Forms.TextBox();
            this.cbGammaCorrect = new System.Windows.Forms.ComboBox();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnExport = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.cbFilterMin = new System.Windows.Forms.ComboBox();
            this.cbWrapS = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.cbWrapT = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.cbFilterMag = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.cbFlipY = new System.Windows.Forms.ComboBox();
            this.label10 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "GUID";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 108);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(45, 15);
            this.label3.TabIndex = 3;
            this.label3.Text = "Format";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 80);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(45, 15);
            this.label4.TabIndex = 2;
            this.label4.Text = "Version";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 271);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(91, 15);
            this.label5.TabIndex = 4;
            this.label5.Text = "Gamma Correct";
            // 
            // tbGUID
            // 
            this.tbGUID.Location = new System.Drawing.Point(109, 25);
            this.tbGUID.Name = "tbGUID";
            this.tbGUID.ReadOnly = true;
            this.tbGUID.Size = new System.Drawing.Size(307, 23);
            this.tbGUID.TabIndex = 5;
            // 
            // tbName
            // 
            this.tbName.Location = new System.Drawing.Point(109, 54);
            this.tbName.Name = "tbName";
            this.tbName.ReadOnly = true;
            this.tbName.Size = new System.Drawing.Size(307, 23);
            this.tbName.TabIndex = 6;
            // 
            // tbVersion
            // 
            this.tbVersion.Location = new System.Drawing.Point(109, 83);
            this.tbVersion.Name = "tbVersion";
            this.tbVersion.Size = new System.Drawing.Size(307, 23);
            this.tbVersion.TabIndex = 7;
            // 
            // tbFormat
            // 
            this.tbFormat.Location = new System.Drawing.Point(109, 112);
            this.tbFormat.Name = "tbFormat";
            this.tbFormat.ReadOnly = true;
            this.tbFormat.Size = new System.Drawing.Size(307, 23);
            this.tbFormat.TabIndex = 8;
            // 
            // cbGammaCorrect
            // 
            this.cbGammaCorrect.FormattingEnabled = true;
            this.cbGammaCorrect.Items.AddRange(new object[] {
            "Yes",
            "No"});
            this.cbGammaCorrect.Location = new System.Drawing.Point(107, 268);
            this.cbGammaCorrect.Name = "cbGammaCorrect";
            this.cbGammaCorrect.Size = new System.Drawing.Size(66, 23);
            this.cbGammaCorrect.TabIndex = 9;
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSave.Location = new System.Drawing.Point(426, 321);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 11;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnExport
            // 
            this.btnExport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnExport.Location = new System.Drawing.Point(345, 321);
            this.btnExport.Name = "btnExport";
            this.btnExport.Size = new System.Drawing.Size(75, 23);
            this.btnExport.TabIndex = 12;
            this.btnExport.Text = "Export";
            this.btnExport.UseVisualStyleBackColor = true;
            this.btnExport.Click += new System.EventHandler(this.btnExport_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 198);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(57, 15);
            this.label6.TabIndex = 13;
            this.label6.Text = "Filter Min";
            // 
            // cbFilterMin
            // 
            this.cbFilterMin.FormattingEnabled = true;
            this.cbFilterMin.Location = new System.Drawing.Point(109, 198);
            this.cbFilterMin.Name = "cbFilterMin";
            this.cbFilterMin.Size = new System.Drawing.Size(307, 23);
            this.cbFilterMin.TabIndex = 14;
            // 
            // cbWrapS
            // 
            this.cbWrapS.FormattingEnabled = true;
            this.cbWrapS.Location = new System.Drawing.Point(109, 141);
            this.cbWrapS.Name = "cbWrapS";
            this.cbWrapS.Size = new System.Drawing.Size(307, 23);
            this.cbWrapS.TabIndex = 16;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(13, 141);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 15);
            this.label7.TabIndex = 15;
            this.label7.Text = "Wrap S";
            // 
            // cbWrapT
            // 
            this.cbWrapT.FormattingEnabled = true;
            this.cbWrapT.Location = new System.Drawing.Point(109, 170);
            this.cbWrapT.Name = "cbWrapT";
            this.cbWrapT.Size = new System.Drawing.Size(307, 23);
            this.cbWrapT.TabIndex = 18;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(13, 170);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 15);
            this.label8.TabIndex = 17;
            this.label8.Text = "Wrap T";
            // 
            // cbFilterMag
            // 
            this.cbFilterMag.FormattingEnabled = true;
            this.cbFilterMag.Location = new System.Drawing.Point(109, 227);
            this.cbFilterMag.Name = "cbFilterMag";
            this.cbFilterMag.Size = new System.Drawing.Size(307, 23);
            this.cbFilterMag.TabIndex = 20;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(10, 227);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(60, 15);
            this.label9.TabIndex = 19;
            this.label9.Text = "Filter Mag";
            // 
            // cbFlipY
            // 
            this.cbFlipY.FormattingEnabled = true;
            this.cbFlipY.Items.AddRange(new object[] {
            "Yes",
            "No"});
            this.cbFlipY.Location = new System.Drawing.Point(107, 301);
            this.cbFlipY.Name = "cbFlipY";
            this.cbFlipY.Size = new System.Drawing.Size(66, 23);
            this.cbFlipY.TabIndex = 22;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(10, 304);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(36, 15);
            this.label10.TabIndex = 21;
            this.label10.Text = "Flip Y";
            // 
            // TextureDataEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(513, 356);
            this.Controls.Add(this.cbFlipY);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.cbFilterMag);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.cbWrapT);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.cbWrapS);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.cbFilterMin);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.btnExport);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.cbGammaCorrect);
            this.Controls.Add(this.tbFormat);
            this.Controls.Add(this.tbVersion);
            this.Controls.Add(this.tbName);
            this.Controls.Add(this.tbGUID);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "TextureDataEditor";
            this.Text = "TextureDataEditor";
            this.Load += new System.EventHandler(this.TextureDataEditor_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tbGUID;
        private System.Windows.Forms.TextBox tbName;
        private System.Windows.Forms.TextBox tbVersion;
        private System.Windows.Forms.TextBox tbFormat;
        private System.Windows.Forms.ComboBox cbGammaCorrect;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnExport;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox cbFilterMin;
        private System.Windows.Forms.ComboBox cbWrapS;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cbWrapT;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ComboBox cbFilterMag;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox cbFlipY;
        private System.Windows.Forms.Label label10;
    }
}