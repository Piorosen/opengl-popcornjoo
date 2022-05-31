namespace CreateGame
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.save_button = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.ball_button = new System.Windows.Forms.Button();
            this.block_button = new System.Windows.Forms.Button();
            this.wall_button = new System.Windows.Forms.Button();
            this.try_text = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.block_score_text = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.clear_button = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.clear_text = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // save_button
            // 
            this.save_button.Location = new System.Drawing.Point(41, 47);
            this.save_button.Name = "save_button";
            this.save_button.Size = new System.Drawing.Size(75, 23);
            this.save_button.TabIndex = 1;
            this.save_button.Text = "save";
            this.save_button.UseVisualStyleBackColor = true;
            this.save_button.Click += new System.EventHandler(this.save_button_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.LightGray;
            this.panel1.Location = new System.Drawing.Point(243, 47);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(834, 559);
            this.panel1.TabIndex = 2;
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            this.panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseUp);
            // 
            // ball_button
            // 
            this.ball_button.Location = new System.Drawing.Point(41, 170);
            this.ball_button.Name = "ball_button";
            this.ball_button.Size = new System.Drawing.Size(122, 45);
            this.ball_button.TabIndex = 3;
            this.ball_button.Text = "ball";
            this.ball_button.UseVisualStyleBackColor = true;
            this.ball_button.Click += new System.EventHandler(this.ball_button_Click);
            // 
            // block_button
            // 
            this.block_button.Location = new System.Drawing.Point(41, 221);
            this.block_button.Name = "block_button";
            this.block_button.Size = new System.Drawing.Size(122, 45);
            this.block_button.TabIndex = 4;
            this.block_button.Text = "block";
            this.block_button.UseVisualStyleBackColor = true;
            this.block_button.Click += new System.EventHandler(this.block_button_Click);
            // 
            // wall_button
            // 
            this.wall_button.Location = new System.Drawing.Point(41, 350);
            this.wall_button.Name = "wall_button";
            this.wall_button.Size = new System.Drawing.Size(122, 45);
            this.wall_button.TabIndex = 5;
            this.wall_button.Text = "wall";
            this.wall_button.UseVisualStyleBackColor = true;
            this.wall_button.Click += new System.EventHandler(this.wall_button_Click);
            // 
            // try_text
            // 
            this.try_text.Location = new System.Drawing.Point(29, 447);
            this.try_text.Name = "try_text";
            this.try_text.Size = new System.Drawing.Size(153, 28);
            this.try_text.TabIndex = 6;
            this.try_text.Text = "10";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 426);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 18);
            this.label1.TabIndex = 7;
            this.label1.Text = "시도 횟수";
            // 
            // block_score_text
            // 
            this.block_score_text.Location = new System.Drawing.Point(41, 305);
            this.block_score_text.Name = "block_score_text";
            this.block_score_text.Size = new System.Drawing.Size(153, 28);
            this.block_score_text.TabIndex = 8;
            this.block_score_text.Text = "1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(38, 284);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(86, 18);
            this.label2.TabIndex = 9;
            this.label2.Text = "벽돌 점수";
            // 
            // clear_button
            // 
            this.clear_button.Location = new System.Drawing.Point(41, 76);
            this.clear_button.Name = "clear_button";
            this.clear_button.Size = new System.Drawing.Size(75, 23);
            this.clear_button.TabIndex = 10;
            this.clear_button.Text = "clear";
            this.clear_button.UseVisualStyleBackColor = true;
            this.clear_button.Click += new System.EventHandler(this.clear_button_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(26, 502);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(104, 18);
            this.label3.TabIndex = 12;
            this.label3.Text = "클리어 점수";
            // 
            // clear_text
            // 
            this.clear_text.Location = new System.Drawing.Point(29, 523);
            this.clear_text.Name = "clear_text";
            this.clear_text.Size = new System.Drawing.Size(153, 28);
            this.clear_text.TabIndex = 11;
            this.clear_text.Text = "10";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1119, 631);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.clear_text);
            this.Controls.Add(this.clear_button);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.block_score_text);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.try_text);
            this.Controls.Add(this.wall_button);
            this.Controls.Add(this.block_button);
            this.Controls.Add(this.ball_button);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.save_button);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button save_button;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button ball_button;
        private System.Windows.Forms.Button block_button;
        private System.Windows.Forms.Button wall_button;
        private System.Windows.Forms.TextBox try_text;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox block_score_text;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button clear_button;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox clear_text;
    }
}

