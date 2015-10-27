#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;



int main()
{
    FILE *file;
    int width = 481;
    int height = 321;
    int BytesPerPixel = 3;
    int lumin = 256;
    const char *r_fileName = "chat.raw";
    const char *n_fileName = "film_chat1.raw";
    const char *out_fileName = "film_chat2.raw";
    const char *ori_fileName = "original.raw";
    //const char *oriout_fileName = "original_out.raw";
    const char *film_fileName = "film.raw";
    const char *ori_fName[3] = {"ori_R_data.txt", "ori_G_data.txt", "ori_B_data.txt"};
    const char *film_fName[3] = {"film_R_data.txt", "film_G_data.txt", "film_B_data.txt"};
    //const char *h_fName[3] = {"h_data1.txt", "h_data2.txt", "h_data3.txt"};
    unsigned char c_Data[height][width][BytesPerPixel];
    unsigned char v_Data[height][width][BytesPerPixel];
    unsigned char ori_Data[750][1000][BytesPerPixel];
    unsigned char film_Data[750][1000][BytesPerPixel];

    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    fread(c_Data, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);
    
    
//////////////////  invert the image /////////////////////////////
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                v_Data[i][width - 1 - j][k] = c_Data[i][j][k];
            }
        }
    }
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                v_Data[i][j][k] = 255 - v_Data[i][j][k];
            }
        }
    }
    
    
/////////////////////////  calulate the transfer function /////////////////////
    
    if (!(file = fopen(ori_fileName,"rb")))
    {
        cout << "Cannot open file: " << ori_fileName << endl;
        exit(1);
    }
    fread(ori_Data, sizeof(unsigned char), 750 * 1000 * BytesPerPixel, file);
    fclose(file);
    
    
    if (!(file = fopen(film_fileName,"rb")))
    {
        cout << "Cannot open file: " << film_fileName << endl;
        exit(1);
    }
    fread(film_Data, sizeof(unsigned char), 750 * 1000 * BytesPerPixel, file);
    fclose(file);

    
    
    int ori_count[lumin][BytesPerPixel];
    int film_count[lumin][BytesPerPixel];
    
    for(int i = 0; i < lumin; i++)
    {
        for(int j = 0; j < BytesPerPixel; j++)
        {
            ori_count[i][j] = 0;
            film_count[i][j] = 0;
        }
    }

    
    for(int i = 0; i < 750; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            for(int k = 0; k < lumin; k++)
            {
                if(ori_Data[i][j][0] == k)
                {
                    ori_count[k][0]++;
                }
                
                if(ori_Data[i][j][1] == k)
                {
                    ori_count[k][1]++;
                }
                
                if(ori_Data[i][j][2] == k)
                {
                    ori_count[k][2]++;
                }
            }
        }
    }
    
    for(int i = 0; i < 750; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            for(int k = 0; k < lumin; k++)
            {
                if(film_Data[i][j][0] == k)
                {
                    film_count[k][0]++;
                }
                
                if(film_Data[i][j][1] == k)
                {
                    film_count[k][1]++;
                }
                
                if(film_Data[i][j][2] == k)
                {
                    film_count[k][2]++;
                }
            }
        }
    }

    
    
  ///////////// write data into txt files ////////////////////
    for(int j = 0; j < BytesPerPixel; j++)
    {
        if((file = fopen(ori_fName[j], "wb")) != NULL)
        {
            for(int i = 0; i < lumin; i++)
            {
                fprintf(file, "%d ", ori_count[i][j]);
            }
        }
        fclose(file);
    }

    
    for(int j = 0; j < BytesPerPixel; j++)
    {
        if((file = fopen(film_fName[j], "wb")) != NULL)
        {
            for(int i = 0; i < lumin; i++)
            {
                fprintf(file, "%d ", film_count[i][j]);
            }
        }
        fclose(file);
    }

    
///////////////////////linear transfer the image/////////////////////
    unsigned char out_Data[height][width][BytesPerPixel];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out_Data[i][j][0] = v_Data[i][j][0] * 0.66 + 99;
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out_Data[i][j][1] = v_Data[i][j][1] * 0.67 + 35;
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out_Data[i][j][2] = v_Data[i][j][2] * 0.58 + 26;
        }
    }
    
    
    
  /////////////////////////////////////////////
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(v_Data, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);
    
    if (!(file = fopen(out_fileName,"wb")))
    {
        cout << "Cannot open file: " << out_fileName << endl;
        exit(1);
    }
    fwrite(out_Data, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);

}