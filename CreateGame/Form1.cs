using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CreateGame
{
    public struct data
    {
        public int x, y, w, h;
        // 0 : 볼
        // 1 : 블럭
        // 2 : 벽
        public int type;
        // 블록에 관한 점수
        public int score;
    }
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        
        List<data> list = new List<data>();
        int createMode = 0;
        Point down;
        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (createMode == 0)
            {
                list.Add(new data
                {
                    x = e.X,
                    y = e.Y,
                    type = createMode
                });
                using (Graphics graphics = panel1.CreateGraphics())
                {
                    graphics.FillEllipse(Brushes.Black, e.X - 10, e.Y - 10, 20, 20);
                }
            }else
            {
                down = e.Location;
            }
        }
        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            if (createMode == 1)
            {
                int lx = (e.X - down.X) / 50;
                int ly = (e.Y - down.Y) / 50;
                for (int x = 0; x < lx; x++)
                {
                    for (int y = 0; y < ly; y++)
                    {
                        list.Add(new data
                        {
                            x = down.X + (50 * x),
                            y = down.Y + (50 * y),
                            w = 50,
                            h = 50,
                            score = int.Parse(block_score_text.Text),
                            type = createMode
                        });
                        using (Graphics graphics = panel1.CreateGraphics())
                        {
                            graphics.FillRectangle(Brushes.Blue, down.X + (50 * x), down.Y + (50 * y), 50, 50);
                        }
                    }
                }
            }
            else if (createMode == 2)
            {
                int lx = (e.X - down.X) / 50;
                int ly = (e.Y - down.Y) / 50;

                for (int x = 0; x < lx; x++)
                {
                    for (int y = 0; y < ly; y++)
                    {
                        list.Add(new data
                        {
                            x = down.X + (50 * x),
                            y = down.Y + (50 * y),
                            w = 50,
                            h = 50,
                            type = createMode
                        });
                        using (Graphics graphics = panel1.CreateGraphics())
                        {
                            graphics.FillRectangle(Brushes.Red, down.X + (50 * x), down.Y + (50 * y), 50, 50);
                        }
                    }
                }
                
               
            }
        }

        #region mode setting
        private void ball_button_Click(object sender, EventArgs e)
        {
            createMode = 0;
        }
        private void block_button_Click(object sender, EventArgs e)
        {
            createMode = 1;
        }
        private void wall_button_Click(object sender, EventArgs e)
        {
            createMode = 2;
        }
        #endregion

        private void clear_button_Click(object sender, EventArgs e)
        {
            list.Clear();
        }

        private void save_button_Click(object sender, EventArgs e)
        {
            StreamWriter sw = new StreamWriter("001.m");
            sw.WriteLine($"{int.Parse(try_text.Text)} {int.Parse(clear_text.Text)} {list.Count}");
            // 0 : 볼
            // 1 : 블럭
            // 2 : 벽
            foreach (var item in list)
            {
                sw.Write($"{item.type} ");
                switch (item.type)
                {
                    case 0:
                        sw.WriteLine($"{item.x} {item.y}");
                        break;
                    case 1:
                        // x, y, w, h, score
                        sw.WriteLine($"{item.x} {item.y} {item.w} {item.h} {item.score}");
                        break;
                    case 2:
                        // x, y, w, h
                        sw.WriteLine($"{item.x} {item.y} {item.w} {item.h}");
                        break;
                }
            }
            sw.Close();
        }

    }
}
