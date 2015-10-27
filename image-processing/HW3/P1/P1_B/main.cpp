#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;


void readFile(const char *r_fileName, vector<struct pixel> &v);
void writeFile(const char *n_fileName, vector<struct pixel> &v);
void horizontalShear(vector<struct pixel> &v);
void verticalShear(vector<struct pixel> &v);
void writeFile1(const char *n_fileName, vector<struct pixel> &v);



struct pixel
{
    unsigned char rgb[3];
    int x;
    int y;
};



int height = 512;
int width = 512;
int bytes = 3;
int width1 = 576;
int height1 = 576;




int main()
{
    vector<struct pixel> v;
    vector<struct pixel> v1;
    
    const char *r_fileName = "jennifer.raw";
    const char *n_fileName = "jennifer_horiz.raw";
    const char *n1_fileName = "jennifer_vertical.raw";
    
    readFile(r_fileName, v);
    horizontalShear(v);
    //verticalShear(v);
    writeFile(n_fileName, v);
    
    
    readFile(r_fileName, v1);
    
    verticalShear(v1);
    writeFile1(n1_fileName, v1);

    
    
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



void writeFile1(const char *n_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char output[height1][width][bytes];
    
    for(int i = 0; i < height1; i++)
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
    fwrite(output, sizeof(unsigned char), width * height1 * bytes, file);
    fclose(file);
}


void writeFile(const char *n_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char output[height][width1][bytes];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width1; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = v.at(i * width1 + j).rgb[k];
            }
            
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), width1 * height * bytes, file);
    fclose(file);
}





void horizontalShear(vector<struct pixel> &v)
{
    unsigned char input[height][width][bytes];
    unsigned char output[height][width1][bytes];
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
        for(int j = 0; j < width1; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = 0;
            }
        }
    }
    
    v.clear();
    
    ////// first part //////////
    double a = 0.4961;
    
    for(int i = 0; i < 128; i++)
    {
        for(int j = (int)(i * a); j < width + (int)(i * a); j++)
        {
            
            double j1 = j  - (i * a);
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[i][(int)j1][k];
            }
        }
        
    }
    
    for(int i = 256; i < 384; i++)
    {
        for(int j = (int)((i - 256) * a); j < width + (int)((i - 256) * a); j++)
        {
            
            double j1 = j  - ((i - 256) * a);
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[i][(int)j1][k];
            }
        }
        
    }
    
    
    ///// second part ////////////////////
    
    for(int i = 128; i < 256; i++)
    {
        int b = (int)(127 * a) - (int)((i - 128) * a);
        
        for(int j = b; j < width + b; j++)
        {
            
            double j1 = j  - b;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[i][(int)j1][k];
            }
        }
    }
    
    for(int i = 384; i < 512; i++)
    {
        int b = (int)(127 * a) - (int)((i - 384) * a);
        
        for(int j = b; j < width + b; j++)
        {
            
            double j1 = j  - b;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[i][(int)j1][k];
            }
        }
    }
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width1; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = output[i][j][k];
            }
            v.push_back(p);
        }
    }

    
}



void verticalShear(vector<struct pixel> &v)
{
    unsigned char input[height][width][bytes];
    unsigned char output[height1][width][bytes];
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
    
    
    for(int i = 0; i < height1; i++)
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
    
    ////// first part //////////
    double a = 0.4961;
    
    for(int j = 0; j < 128; j++)
    {
        for(int i = (int)(j * a); i < height + (int)(j * a); i++)
        {
            
            double i1 = i  - (j * a);
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)i1][j][k];
            }
        }
        
    }
    
    for(int j = 256; j < 384; j++)
    {
        for(int i = (int)((j - 256) * a); i < height + (int)((j - 256) * a); i++)
        {
            
            double i1 = i  - ((j - 256) * a);
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)i1][j][k];
            }
        }
        
    }
    
    
    ///// second part ////////////////////
    
    for(int j = 128; j < 256; j++)
    {
        int b = (int)(127 * a) - (int)((j - 128) * a);
        
        for(int i = b; i < height + b; i++)
        {
            
            double i1 = i  - b;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)i1][j][k];
            }
        }
    }
    
    for(int j = 384; j < 512; j++)
    {
        int b = (int)(127 * a) - (int)((j - 384) * a);
        
        for(int i = b; i < height + b; i++)
        {
            
            double i1 = i  - b;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[(int)i1][j][k];
            }
        }
    }
    
    
    for(int i = 0; i < height1; i++)
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






