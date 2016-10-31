﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SceneTool
{
    
    public partial class mainscreen : Form
    {
        Scene scene;
        const int NUM_CELLS = 80;
        const int CELL_SIZE = 5;
        public mainscreen()
        {
            scene = new SceneTool.Scene();
            InitializeComponent();
        }

        private void scenewindow_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Pen p = new Pen(Color.Gray);

            for(int i = 0; i <= NUM_CELLS; i++)
            {
                // Vertical
                g.DrawLine(p, i * CELL_SIZE, 0, i * CELL_SIZE, NUM_CELLS * CELL_SIZE);
                // Horizontal
                g.DrawLine(p, 0, i * CELL_SIZE, NUM_CELLS * CELL_SIZE, i * CELL_SIZE);
            }
        }

        private void newscene_Click(object sender, EventArgs e)
        {
            startpanel.Visible = false;
            scenewindow.Visible = true;
            tabControl.Visible = true;
            clearbutton.Visible = true;
            loadbutton.Visible = true;
            savescenebutton.Visible = true;
        }

        private void createlightbutton_Click(object sender, EventArgs e)
        {
            buildlightpanel.Visible = true;
            lightpanel.Visible = false;
        }

        private void buildlightbackbutton_Click(object sender, EventArgs e)
        {
            buildlightpanel.Visible = false;
            lightpanel.Visible = true;
        }

        private void buildlightbutton_Click(object sender, EventArgs e)
        {
            if(directionalradio.Checked)
            {
                double[] direction = new double[3];
                double[] ambient = new double[4];
                double[] diffuse = new double[4];

                //get direction
                bool result = Double.TryParse(lightdirectionX.Text, out direction[0]);
                if(!result)
                {
                    //error handling
                }
                result= Double.TryParse(lightdirectionY.Text, out direction[1]);
                if(!result)
                {
                    //error handling
                }
                result = Double.TryParse(lightdirectionZ.Text, out direction[2]);
                if(!result)
                {
                    //error handling
                }

                //get ambient
                result = Double.TryParse(ambientR.Text, out ambient[0]);
                if(! result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientG.Text, out ambient[1]);
                if(!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientB.Text, out ambient[2]);
                if(!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientA.Text, out ambient[3]);
                if (!result)
                {
                    //error handling
                }



                //get diffuse

                result = Double.TryParse(diffuseR.Text, out diffuse[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseG.Text, out ambient[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseG.Text, out ambient[2]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseA.Text, out ambient[3]);
                if (!result)
                {
                    //error handling
                }

                //actually build the thing
                scene.buildDirectionalLight(ambient,diffuse,direction);
            }
            else if(pointradio.Checked)
            {
                double[] position = new double[3];
                double[] ambient = new double[4];
                double[] diffuse = new double[4];

                //get position
                bool result = Double.TryParse(lightpositionX.Text, out position[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(lightpositionY.Text, out position[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(lightpositionZ.Text, out position[2]);
                if (!result)
                {
                    //error handling
                }

                //get ambient
                result = Double.TryParse(ambientR.Text, out ambient[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientG.Text, out ambient[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientB.Text, out ambient[2]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientA.Text, out ambient[3]);
                if (!result)
                {
                    //error handling
                }



                //get diffuse

                result = Double.TryParse(diffuseR.Text, out diffuse[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseG.Text, out ambient[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseG.Text, out ambient[2]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseA.Text, out ambient[3]);
                if (!result)
                {
                    //error handling
                }
                scene.buildPointLight(ambient,diffuse,position);
            }
            else if(spotradio.Checked)
            {
                double[] direction = new double[3];
                double[] position = new double[3];
                double[] ambient = new double[4];
                double[] diffuse = new double[4];

                //get direction
                bool result = Double.TryParse(lightdirectionX.Text, out direction[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(lightdirectionY.Text, out direction[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(lightdirectionZ.Text, out direction[2]);
                if (!result)
                {
                    //error handling
                }

                //get position
                result = Double.TryParse(lightpositionX.Text, out position[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(lightpositionY.Text, out position[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(lightpositionZ.Text, out position[2]);
                if (!result)
                {
                    //error handling
                }

                //get ambient
                result = Double.TryParse(ambientR.Text, out ambient[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientG.Text, out ambient[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientB.Text, out ambient[2]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(ambientA.Text, out ambient[3]);
                if (!result)
                {
                    //error handling
                }



                //get diffuse

                result = Double.TryParse(diffuseR.Text, out diffuse[0]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseG.Text, out ambient[1]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseG.Text, out ambient[2]);
                if (!result)
                {
                    //error handling
                }
                result = Double.TryParse(diffuseA.Text, out ambient[3]);
                if (!result)
                {
                    //error handling
                }
                scene.buildSpotLight(ambient,diffuse,position,direction);
            }
        }

        private void loadmeshbutton_Click(object sender, EventArgs e)
        {
            scene.loadMesh(meshfilepath.Text);
        }

        private void deletemeshbutton_Click(object sender, EventArgs e)
        {
            
            scene.deleteMesh(currentmeshlist.SelectedIndex);
        }

        private void loadtexturebutton_Click(object sender, EventArgs e)
        {
            if (diffuseradio.Checked)
                scene.loadDiffuse(texturefilepath.Text);
            else if (normalradio.Checked)
                scene.loadNormal(texturefilepath.Text);
            else if (specularradio.Checked)
                scene.loadSpecular(texturefilepath.Text);
            else if (multiplyradio.Checked)
                scene.loadMultiply(texturefilepath.Text);
        }

        private void deletetexturebutton_Click(object sender, EventArgs e)
        {
            scene.deleteTexture(currenttextureslist.SelectedIndex);
        }

        private void loadshaderbutton_Click(object sender, EventArgs e)
        {
            if (pixelshaderradio.Checked)
                scene.loadPixelShader(shaderfilepath.Text);
            else if (vertexshaderradio.Checked)
                scene.loadVertexShader(shaderfilepath.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            scene.deleteShader(currentshaderlist.SelectedIndex);
        }

        private void editwallsbutton_Click(object sender, EventArgs e)
        {
            propertiespanel.Visible = false;
            walleditorpanel.Visible = true;
        }

        private void mainscreen_Load(object sender, EventArgs e)
        {

        }

        private void directionalradio_CheckedChanged(object sender, EventArgs e)
        {
            if(directionalradio.Checked) //prevent what we can't use right now
            {
                lightpositionX.Text = "";
                lightpositionX.ReadOnly = true;
                lightpositionY.Text = "";
                lightpositionY.ReadOnly = true;
                lightpositionZ.Text = "";
                lightpositionZ.ReadOnly = true;
                lightdirectionW.Text = "";
                lightdirectionW.ReadOnly = true;
                lightdirectionW.BorderStyle = BorderStyle.None;
                lightpositionX.BackColor = Color.DarkGray;
                lightpositionY.BackColor = Color.DarkGray;
                lightpositionZ.BackColor = Color.DarkGray;

            }
            else //reset everything to normal
            {
                lightpositionX.ReadOnly = false;
                lightpositionY.ReadOnly = false;
                lightpositionZ.ReadOnly = false;
                lightdirectionW.ReadOnly = false;
                lightpositionX.BackColor = Color.White;
                lightpositionY.BackColor = Color.White;
                lightpositionZ.BackColor = Color.White;
                lightdirectionW.BorderStyle = BorderStyle.Fixed3D;

            }
        }

        private void pointradio_CheckedChanged(object sender, EventArgs e)
        {
            if (directionalradio.Checked) //prevent what we can't use right now
            {
                lightdirectionX.Text = "";
                lightdirectionX.ReadOnly = true;
                lightdirectionY.Text = "";
                lightdirectionY.ReadOnly = true;
                lightdirectionZ.Text = "";
                lightdirectionZ.ReadOnly = true;
                lightdirectionW.Text = "";
                lightdirectionW.ReadOnly = true;
                lightdirectionW.BorderStyle = BorderStyle.None;
                lightdirectionX.BackColor = Color.DarkGray;
                lightdirectionY.BackColor = Color.DarkGray;
                lightdirectionZ.BackColor = Color.DarkGray;

            }
            else //reset everything to normal
            {
                lightdirectionX.ReadOnly = false;
                lightdirectionY.ReadOnly = false;
                lightdirectionZ.ReadOnly = false;
                lightdirectionW.ReadOnly = false;
                lightdirectionX.BackColor = Color.White;
                lightdirectionY.BackColor = Color.White;
                lightdirectionZ.BackColor = Color.White;
                lightdirectionW.BorderStyle = BorderStyle.Fixed3D;

            }
        }

      
    }
}
