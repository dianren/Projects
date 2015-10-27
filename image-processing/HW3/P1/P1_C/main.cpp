#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;


void readFile(const char *r_fileName, vector<struct pixel> &v);
void writeFile(const char *n_fileName, vector<struct pixel> &v);
void warping(vector<struct pixel> &v);
void reverseWarping(vector<struct pixel> &v);






struct pixel
{
    unsigned char rgb[3];
    int x;
    int y;
};







int height = 512;
int width = 512;
int bytes = 3;




int main()
{
    vector<struct pixel> v;
    
    
    const char *r_fileName = "fruits.raw";
    const char *n_fileName = "fruits_warping.raw";
    
    readFile(r_fileName, v);
    warping(v);
    reverseWarping(v);
    writeFile(n_fileName, v);

    
}





void readFile(const char *r_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char input[height][width][bytes];
    pixel p;
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    
    fread(input, sizeof(unsigned char), width * height * bytes, file);
    fclose(file);
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = input[i][j][k];
            }
            v.push_back(p);
        }
    }
    
}


void writeFile(const char *n_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char output[height][width][bytes];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = v.at(i * width + j).rgb[k];
            }
            
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), width * height * bytes, file);
    fclose(file);
}


void warping(vector<struct pixel> &v)
{
    
    
    unsigned char input[height][width][bytes];
    unsigned char output[height][width][bytes];
    pixel p;
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = v.at(i * width + j).rgb[k];
            }
            
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = 0;
            }
        }
    }
    
    v.clear();
    
    
////////////////////// part 1  /////////////////////////////
    
    double a1[3][3] = {{1.417, 0, 0},
                        {0.417, 1, 0},
                        {0, 0, 1}};
    
    double a8[3][3] = {{1.417, 0, 0},
                        {-0.417, 1, 0},
                        {0, 0, 1}};
    
    double f = 2.4;// 180/75 = 2.4
    
    for(int i = 0; i < 76; i++)
    {
        for(int j = 255 - (int)(i * f); j < 256; j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a1[0][0] * j1 + a1[0][1] * i1 + a1[0][2] * 1;
            double y1 = a1[1][0] * j1 + a1[1][1] * i1 + a1[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }

        }
        
        
        for(int j = 256; j < 256 + (int)(i * f); j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a8[0][0] * j1 + a8[0][1] * i1 + a8[0][2] * 1;
            double y1 = a8[1][0] * j1 + a8[1][1] * i1 + a8[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }

        
    }

    for(int i = 76; i < 256; i++)
    {
        for(int j = i; j < 256; j++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a1[0][0] * j1 + a1[0][1] * i1 + a1[0][2] * 1;
            double y1 = a1[1][0] * j1 + a1[1][1] * i1 + a1[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }

        }
        
        
        for(int j = 256; j < 512 - i; j++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a8[0][0] * j1 + a8[0][1] * i1 + a8[0][2] * 1;
            double y1 = a8[1][0] * j1 + a8[1][1] * i1 + a8[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
            
        }
    }
    
    
////////////////////// part 2  /////////////////////////////
    
    double a2[3][3] = {{1, 0.417, 0},
                        {0, 1.417, 0},
                        {0, 0, 1}};
    
    double a3[3][3] = {{1, -0.417, 0},
                        {0, 1.417, 0},
                        {0, 0, 1}};
    
    f = 2.4;// 180/75 = 2.4
    
    for(int j = 0; j < 76; j++)
    {
        for(int i = 255 - (int)(j * f); i < 256; i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a2[0][0] * j1 + a2[0][1] * i1 + a2[0][2] * 1;
            double y1 = a2[1][0] * j1 + a2[1][1] * i1 + a2[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
        for(int i = 256; i < 256 + (int)(j * f); i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a3[0][0] * j1 + a3[0][1] * i1 + a3[0][2] * 1;
            double y1 = a3[1][0] * j1 + a3[1][1] * i1 + a3[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
    }
    
    for(int j = 76; j < 256; j++)
    {
        for(int i = j; i < 256; i++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a2[0][0] * j1 + a2[0][1] * i1 + a2[0][2] * 1;
            double y1 = a2[1][0] * j1 + a2[1][1] * i1 + a2[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
            
        }
        
        
        for(int i = 256; i < 512 - j; i++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a3[0][0] * j1 + a3[0][1] * i1 + a3[0][2] * 1;
            double y1 = a3[1][0] * j1 + a3[1][1] * i1 + a3[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
            
        }
    }

    
  
////////////////////// part 3  /////////////////////////////
    
    
    double a4[3][3] = {{1.417, 0, 0},
                        {-0.417, 1, 0},
                        {0, 0, 1}};
    
    double a5[3][3] = {{1.417, 0, 0},
                        {0.417, 1, 0},
                        {0, 0, 1}};
    
    f = 2.4;// 180/75 = 2.4
    
    
    for(int i = 512; i > 436; i--)
    {
        for(int j = 255 - (int)((512 - i) * f); j < 256; j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a4[0][0] * j1 + a4[0][1] * i1 + a4[0][2] * 1;
            double y1 = a4[1][0] * j1 + a4[1][1] * i1 + a4[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
        for(int j = 256; j < 256 + (int)((512 - i) * f); j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a5[0][0] * j1 + a5[0][1] * i1 + a5[0][2] * 1;
            double y1 = a5[1][0] * j1 + a5[1][1] * i1 + a5[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
    }
    
    for(int i = 436; i > 255; i--)
    {
        for(int j = 512 - i; j < 256; j++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a4[0][0] * j1 + a4[0][1] * i1 + a4[0][2] * 1;
            double y1 = a4[1][0] * j1 + a4[1][1] * i1 + a4[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
            
        }
        
        
        for(int j = 256; j < i + 1; j++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a5[0][0] * j1 + a5[0][1] * i1 + a5[0][2] * 1;
            double y1 = a5[1][0] * j1 + a5[1][1] * i1 + a5[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
            
        }
    }

    
    
    ////////////////////// part 4 /////////////////////////////
    
    double a6[3][3] = {{1, 0.417, 0},
                        {0, 1.417, 0},
                        {0, 0, 1}};
    
    double a7[3][3] = {{1, -0.417, 0},
                        {0, 1.417, 0},
                        {0, 0, 1}};
    
    f = 2.4;// 180/75 = 2.4
    
    for(int j = 512; j > 436; j--)
    {
        for(int i = 255 - (int)((512 - j) * f); i < 256; i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a7[0][0] * j1 + a7[0][1] * i1 + a7[0][2] * 1;
            double y1 = a7[1][0] * j1 + a7[1][1] * i1 + a7[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
        for(int i = 256; i < 256 + (int)((512 - j) * f); i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a6[0][0] * j1 + a6[0][1] * i1 + a6[0][2] * 1;
            double y1 = a6[1][0] * j1 + a6[1][1] * i1 + a6[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
    }
    
    for(int j = 436; j > 255; j--)
    {
        for(int i = 512 - j; i < 256; i++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a7[0][0] * j1 + a7[0][1] * i1 + a7[0][2] * 1;
            double y1 = a7[1][0] * j1 + a7[1][1] * i1 + a7[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
            
        }
        
        
        for(int i = 256; i < j + 1; i++)
        {
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a6[0][0] * j1 + a6[0][1] * i1 + a6[0][2] * 1;
            double y1 = a6[1][0] * j1 + a6[1][1] * i1 + a6[1][2] * 1;
            
            int x = (int)x1 + 255;
            int y = (int)y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
            
        }
    }
  
    
    
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = output[i][j][k];
            }
            v.push_back(p);
        }
    }

}



void reverseWarping(vector<struct pixel> &v)
{
    unsigned char input[height][width][bytes];
    unsigned char output[height][width][bytes];
    pixel p;
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = v.at(i * width + j).rgb[k];
            }
            
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = 0;
            }
        }
    }
    
    v.clear();
    
    
    ////////////////////// part 1  /////////////////////////////
    
    double a1[3][3] = {{0.706, 0, 0},
                        {-0.294, 1, 0},
                        {0, 0, 1}};
    
    double a8[3][3] = {{0.706, 0, 0},
                        {0.294, 1, 0},
                        {0, 0, 1}};
    
    double f = 2.4;// 180/75 = 2.4
    
    for(int i = 0; i < 256; i++)
    {
        for(int j = i; j < 256; j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a1[0][0] * j1 + a1[0][1] * i1 + a1[0][2] * 1;
            double y1 = a1[1][0] * j1 + a1[1][1] * i1 + a1[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
        for(int j = 256; j < 512 - i; j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a8[0][0] * j1 + a8[0][1] * i1 + a8[0][2] * 1;
            double y1 = a8[1][0] * j1 + a8[1][1] * i1 + a8[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
    }
    
////////////////////// part 2  /////////////////////////////
    
    double a2[3][3] = {{1, -0.294, 0},
                        {0, 0.706, 0},
                        {0, 0, 1}};
    
    double a3[3][3] = {{1, 0.294, 0},
                        {0, 0.706, 0},
                        {0, 0, 1}};
    
    f = 2.4;// 180/75 = 2.4
    
    for(int j = 0; j < 256; j++)
    {
        for(int i = j; i < 256; i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a2[0][0] * j1 + a2[0][1] * i1 + a2[0][2] * 1;
            double y1 = a2[1][0] * j1 + a2[1][1] * i1 + a2[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
        for(int i = 256; i < 512 - j; i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a3[0][0] * j1 + a3[0][1] * i1 + a3[0][2] * 1;
            double y1 = a3[1][0] * j1 + a3[1][1] * i1 + a3[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
    }
    
    
    
    
    ////////////////////// part 3  /////////////////////////////
    
    
    double a4[3][3] = {{0.706, 0, 0},
                        {0.294, 1, 0},
                        {0, 0, 1}};
    
    double a5[3][3] = {{0.706, 0, 0},
                        {-0.294, 1, 0},
                        {0, 0, 1}};
    
    f = 2.4;// 180/75 = 2.4
    
    
    for(int i = 512; i > 256; i--)
    {
        for(int j = 512 - i; j < 256; j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a4[0][0] * j1 + a4[0][1] * i1 + a4[0][2] * 1;
            double y1 = a4[1][0] * j1 + a4[1][1] * i1 + a4[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
        for(int j = 256; j < i; j++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a5[0][0] * j1 + a5[0][1] * i1 + a5[0][2] * 1;
            double y1 = a5[1][0] * j1 + a5[1][1] * i1 + a5[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
    }
    
////////////////////// part 4 /////////////////////////////
    
    double a6[3][3] = {{1, -0.294, 0},
                        {0, 0.706, 0},
                        {0, 0, 1}};
    
    double a7[3][3] = {{1, 0.294, 0},
                        {0, 0.706, 0},
                        {0, 0, 1}};
    
    f = 2.4;// 180/75 = 2.4
    
    for(int j = 512; j > 256; j--)
    {
        for(int i = 512 - j; i < 256; i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a7[0][0] * j1 + a7[0][1] * i1 + a7[0][2] * 1;
            double y1 = a7[1][0] * j1 + a7[1][1] * i1 + a7[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
        for(int i = 256; i < j + 1; i++)
        {
            
            int i1 = i - 255;
            int j1 = j - 255;
            
            double x1 = a6[0][0] * j1 + a6[0][1] * i1 + a6[0][2] * 1;
            double y1 = a6[1][0] * j1 + a6[1][1] * i1 + a6[1][2] * 1;
            
            double x = x1 + 255;
            double y = y1 + 255;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)y][(int)x][k];
            }
            
        }
        
        
    }
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = output[i][j][k];
            }
            v.push_back(p);
        }
    }

}




