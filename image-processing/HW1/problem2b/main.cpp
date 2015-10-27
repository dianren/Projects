#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "color.h"
using namespace std;

void oil_painting(int size1, int size2, int BytesPerPixel, int len, const char *r_fileName, const char *n_fileName);




int main()
{
    
    ///////////first image/////////
    oil_painting(360, 360, 3, 3, "scene2_256.raw", "scene2_256_winsize3.raw");
    oil_painting(360, 360, 3, 5, "scene2_256.raw", "scene2_256_winsize5.raw");
    oil_painting(360, 360, 3, 7, "scene2_256.raw", "scene2_256_winsize7.raw");
    oil_painting(360, 360, 3, 9, "scene2_256.raw", "scene2_256_winsize9.raw");
    oil_painting(360, 360, 3, 11, "scene2_256.raw", "scene2_256_winsize11.raw");
    
    
    ///////////second image////////
    oil_painting(384, 384, 3, 3, "Trojan_256.raw", "Trojan_256_winsize3.raw");
    oil_painting(384, 384, 3, 5, "Trojan_256.raw", "Trojan_256_winsize5.raw");
    oil_painting(384, 384, 3, 7, "Trojan_256.raw", "Trojan_256_winsize7.raw");
    oil_painting(384, 384, 3, 9, "Trojan_256.raw", "Trojan_256_winsize9.raw");
    oil_painting(384, 384, 3, 11, "Trojan_256.raw", "Trojan_256_winsize11.raw");
}




void oil_painting(int size1, int size2, int BytesPerPixel, int len, const char *r_fileName, const char *n_fileName)
{
    unsigned char s_Data[size1][size2][BytesPerPixel];
    unsigned char out_Data[size1][size2][BytesPerPixel];
    int wsize = len * len;
    int n = (len - 1) / 2;
    FILE *file;
    
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    fread(s_Data, sizeof(unsigned char), size1 * size2 * BytesPerPixel, file);
    fclose(file);
    
    
    ////////////////////////////copy in s1_Data array/////////////////////////////
    
    unsigned char s1_Data[size1 + 2 * n][size2][BytesPerPixel];
    
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < size2; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                s1_Data[i][j][k] = s_Data[n-i][j][k];
            }
        }
    }
    
    for(int i = 0; i < size1; i++)
    {
        for(int j = 0; j < size2; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                s1_Data[i + n][j][k] = s_Data[i][j][k];
            }
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < size2; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                s1_Data[size1 - 1 + 2 * n - i][j][k] = s_Data[size1 - 1 - n + i][j][k];
            }
        }
    }
    
    
    
    
    
    ///////////////////////////copy in s2_Data from s1_Data////////////////////////
    
    unsigned char s2_Data[size1 + 2 * n][size2 + 2 * n][BytesPerPixel];
    
    for(int i = 0; i < size1 + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                s2_Data[i][j][k] = s1_Data[i][n - j][k];
            }
        }
    }
    
    for(int i = 0; i < size1 + 2 * n; i++)
    {
        for(int j = 0; j < size2; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                s2_Data[i][j + n][k] = s1_Data[i][j][k];
            }
        }
    }
    
    for(int i = 0; i < size1 + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                s2_Data[i][size2 - 1 + 2 * n - j][k] = s1_Data[i][size2 - 1 - n + j][k];
            }
        }
    }
    
    
    
    const char *tname = "text.raw";
    if (!(file = fopen(tname,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(s2_Data, sizeof(unsigned char), (size1 + 2*n) * (size2 + 2*n) * BytesPerPixel, file);
    fclose(file);
    
    //////////////////////chose the largest frequency color////////////////////////
    
    color c;
    vector<color> v_color;
    
    
    /////////////scan pixels in s2_Data array///////////////////////
    
    for(int m = 0; m < size1; m++)
    {
        for(int f = 0; f < size2; f++)
        {
            
            wsize = len * len;///each time initialize the window size
            
            
            /////copy pixels in color vector/////////
            
            for(int i = m; i < m + len; i++)
            {
                for(int j = f; j < f + len; j++)
                {
                    c.R = s2_Data[i][j][0];
                    c.G = s2_Data[i][j][1];
                    c.B = s2_Data[i][j][2];
                    v_color.push_back(c);
                }
            }
            
            
            ///count the number of colors in windowsize///
            
            
            
            for(int i = 0; i < wsize - 1; i++)
            {
                for(int j = i + 1; j < wsize; j++)
                {
                    if(v_color.at(i).R == v_color.at(j).R && v_color.at(i).G == v_color.at(j).G && v_color.at(i).B == v_color.at(j).B)
                    {
                        v_color.at(i).counter++;
                        v_color.erase(v_color.begin() + j);
                        j--;
                        wsize--;
                    }
                }
            }
            
            
            
            /////////chose the largest frequency color/////
            
            
            color c1;
            c1.counter = v_color.at(0).counter;
            c1.R =v_color.at(0).R;
            c1.G =v_color.at(0).G;
            c1.B =v_color.at(0).B;
            
            
            for(int i = 1; i < wsize; i++)
            {
                if(c1.counter < v_color.at(i).counter)
                {
                    c1.counter = v_color.at(i).counter;
                    c1.R = v_color.at(i).R;
                    c1.G = v_color.at(i).G;
                    c1.B = v_color.at(i).B;
                }
            }
            
            
            
            
            ////give the value to the middle of window//////
            
            
            out_Data[m][f][0] = c1.R;
            out_Data[m][f][1] = c1.G;
            out_Data[m][f][2] = c1.B;
            
            
            ///////release the vector//////////////
            
            v_color.clear();
        }
    }
    
    
    
    ////////////////////// output the new image /////////////////////////////////
    
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(out_Data, sizeof(unsigned char), size1 * size2 * BytesPerPixel, file);
    fclose(file);
}



