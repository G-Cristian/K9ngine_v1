
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
            this.label5.Location = new System.Drawing.Point(12, 145);
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
            this.cbGammaCorrect.Location = new System.Drawing.Point(109, 142);
            this.cbGammaCorrect.Name = "cbGammaCorrect";
            this.cbGammaCorrect.Size = new System.Drawing.Size(66, 23);
            this.cbGammaCorrect.TabIndex = 9;
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(422, 183);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 11;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnExport
            // 
            this.btnExport.Location = new System.Drawing.Point(341, 183);
            this.btnExport.Name = "btnExport";
            this.btnExport.Size = new System.Drawing.Size(75, 23);
            this.btnExport.TabIndex = 12;
            this.btnExport.Text = "Export";
            this.btnExport.UseVisualStyleBackColor = true;
            this.btnExport.Click += new System.EventHandler(this.btnExport_Click);
            // 
            // TextureDataEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(513, 218);
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
    }
}