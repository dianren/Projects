#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;




void readFile(const char *r_fileName, vector<struct pixel> &v);
void writeFile(const char *n_fileName, vector<struct pixel> &v);
double find_max(vector<struct pixel> &v, int channel, int flag);
double find_min(vector<struct pixel> &v, int channel, int flag);
void normalization(int l, vector<struct pixel> &v, int channel, int flag);
void rgbTOcmy(vector<struct pixel> &v);
void errorDiffusion(vector<struct pixel> &v, int channel);
void cmyTOrgb(vector<struct pixel> &v);
struct pyramid MBVQ(double C, double M, double Y);
struct color findShortestDistance(struct pixel p, pyramid x);
void colorErrorDiffusion(vector<struct pixel> &v);
double shortD(struct color p, pyramid x);
void show(pyramid pyr);
void initialize();



struct pixel
{
    unsigned char rgb[3];
    double d_rgb[3];
    double cmy[3];
};


struct color
{
    double c;
    double m;
    double y;
};





struct pyramid
{
    double p1[3];
    double p2[3];
    double p3[3];
    double p4[3];
};

double W[3] = {0, 0, 0};
double C[3] = {0, 1, 0};
double B[3] = {1, 1, 0};
double M[3] = {1, 0, 0};
double Y[3] = {0, 0, 1};
double G[3] = {0, 1, 1};
double K[3] = {1, 1, 1};
double R[3] = {1, 0, 1};



pyramid CMYW;
pyramid MYGC;
pyramid RGMY;
pyramid KRGB;
pyramid RGBM;
pyramid CMGB;

    





int height = 258;
int width = 350;
int bytes = 3;
int red = 0;
int green = 1;
int blue = 2;
int flag_char = 1;
int flag_double = 0;









int main()
{
    const char *r_fileName = "trees.raw";
    const char *n_fileName = "trees_sepreate.raw";
    const char *n1_fileName = "trees_MBVP.raw";
    vector<struct pixel> v;
    
    initialize();
    
    
   
    readFile(r_fileName, v);
    
    normalization(1, v, red, flag_char);
    normalization(1, v, green, flag_char);
    normalization(1, v, blue, flag_char);
    rgbTOcmy(v);
    //errorDiffusion(v, red);
    //errorDiffusion(v, green);
    //errorDiffusion(v, blue);
    colorErrorDiffusion(v);
    cmyTOrgb(v);
    normalization(255, v, red, flag_double);
    normalization(255, v, green, flag_double);
    normalization(255, v, blue, flag_double);
    writeFile(n1_fileName, v);
    
    
    return 0;
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


double find_max(vector<struct pixel> &v, int channel, int flag)
{
    double max;
    
    if(flag == flag_char)
    {
        
        max = (double)v.at(0).rgb[channel];
        
        for(int i = 1; i < height * width; i++)
        {
            if(max < (double)v.at(i).rgb[channel])
            {
                max = (double)v.at(i).rgb[channel];
            }
        }
        //cout << max<<endl;
        //return max;
    }
    else if(flag == flag_double)
    {
        
        max = v.at(0).d_rgb[channel];
        
        for(int i = 1; i < height * width; i++)
        {
            if(max < v.at(i).d_rgb[channel])
            {
                max = v.at(i).d_rgb[channel];
            }
        }
        //cout << max<<endl;
        //return max;
    }
    return max;
}


double find_min(vector<struct pixel> &v, int channel, int flag)
{
    double min;
    
    if(flag == flag_char)
    {
        
        min = (double)v.at(0).rgb[channel];
        
        for(int i = 1; i < height * width; i++)
        {
            if(min > (double)v.at(i).rgb[channel])
            {
                min = (double)v.at(i).rgb[channel];
            }
        }
        //cout << max<<endl;
        //return max;
    }
    else if(flag == flag_double)
    {
        
        min = v.at(0).d_rgb[channel];
        
        for(int i = 1; i < height * width; i++)
        {
            if(min > v.at(i).d_rgb[channel])
            {
                min = v.at(i).d_rgb[channel];
            }
        }
        //cout << max<<endl;
        //return max;
    }
    return min;
}


void normalization(int l, vector<struct pixel> &v, int channel, int flag)
{
    
    double max, min;
    
    if(flag == flag_char)
    {
        max = find_max(v, channel, flag);
        min = find_min(v, channel, flag);
        
        //cout<< max << " " << min << endl;
        for(int i = 0; i < height * width; i++)
        {
            v.at(i).d_rgb[channel] = ((double)(v.at(i).rgb[channel] - min) * l) / (max - min);
        }
    }
    else if(flag == flag_double)
    {
        max = find_max(v, channel, flag);
        min = find_min(v, channel, flag);
        
        //cout<< max << " " << min << endl;
        for(int i = 0; i < height * width; i++)
        {
            v.at(i).rgb[channel] = (unsigned char)(((v.at(i).d_rgb[channel] - min) * l) / (max - min));
        }
        
    }
    
}


void rgbTOcmy(vector<struct pixel> &v)
{
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < bytes; j++)
        {
            v.at(i).cmy[j] = 1 - v.at(i).d_rgb[j];
        }
    }
}


void cmyTOrgb(vector<struct pixel> &v)
{
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < bytes; j++)
        {
            v.at(i).d_rgb[j] = 1 - v.at(i).cmy[j];
        }
    }
}


void errorDiffusion(vector<struct pixel> &v, int channel)
{
    int i, j;
    double pixel[height][width][bytes];
    double output[height][width][bytes];
    double error;
    
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            pixel[i][j][channel] = v.at(i * width + j).cmy[channel];
        }
    }
    
    
    //// even rows begins /////////
    
    for(i = 0; i < height; i += 2)
    {
        for(j = 0; j < width; j++)
        {
            if(j == 0)
            {
                if(pixel[i][j][channel] <= 0.5)
                {
                    output[i][j][channel] = 0;
                }
                else
                {
                    output[i][j][channel] = 1;
                }
                
                error = pixel[i][j][channel] - output[i][j][channel];
                pixel[i][j + 1][channel] += error * 7 / 13;
                pixel[i + 1][j][channel] += error * 5 / 13;
                pixel[i + 1][j + 1][channel] += error * 1 / 13;
                
            }
            else if(j == (width - 1))
            {
                if(pixel[i][j][channel] <= 0.5)
                {
                    output[i][j][channel] = 0;
                }
                else
                {
                    output[i][j][channel] = 1;
                }
                
                error = pixel[i][j][channel] - output[i][j][channel];
                pixel[i + 1][j][channel] += error * 5 / 8;
                pixel[i + 1][j - 1][channel] += error * 3 / 8;
                
            }
            else
            {
                if(pixel[i][j][channel] <= 0.5)
                {
                    output[i][j][channel] = 0;
                }
                else
                {
                    output[i][j][channel] = 1;
                }
                
                error = pixel[i][j][channel] - output[i][j][channel];
                pixel[i][j + 1][channel] += error * 7 / 16;
                pixel[i + 1][j - 1][channel] += error * 3 / 16;
                pixel[i + 1][j][channel] += error * 5 / 16;
                pixel[i + 1][j + 1][channel] += error * 1 / 16;
            }
        }
    }
    
    
    ////// odd row begins ////////
    
    for(i = 1; i < height; i += 2)
    {
        for(j = width - 1; j >= 0; j--)
        {
            
            
            if(i == height - 1)
            {
                if(j == 0)
                {
                    if(pixel[i][j][channel] <= 0.5)
                    {
                        output[i][j][channel] = 0;
                    }
                    else
                    {
                        output[i][j][channel] = 1;
                    }
                }
                else
                {
                    if(pixel[i][j][channel] <= 0.5)
                    {
                        output[i][j][channel] = 0;
                    }
                    else
                    {
                        output[i][j][channel] = 1;
                    }
                    
                    error = pixel[i][j][channel] - output[i][j][channel];
                    pixel[i][j - 1][channel] += error;
                    
                }
            }
            else
            {
                
                if(j == width - 1)
                {
                    if(pixel[i][j][channel] <= 0.5)
                    {
                        output[i][j][channel] = 0;
                    }
                    else
                    {
                        output[i][j][channel] = 1;
                    }
                    
                    error = pixel[i][j][channel] - output[i][j][channel];
                    pixel[i][j - 1][channel] += error * 7 / 13;
                    pixel[i + 1][j][channel] += error * 5 / 13;
                    pixel[i + 1][j - 1][channel] += error * 1 / 13;
                    
                }
                else if(j == 0)
                {
                    if(pixel[i][j][channel] <= 0.5)
                    {
                        output[i][j][channel] = 0;
                    }
                    else
                    {
                        output[i][j][channel] = 1;
                    }
                    
                    error = pixel[i][j][channel] - output[i][j][channel];
                    pixel[i + 1][j][channel] += error * 5 / 8;
                    pixel[i + 1][j + 1][channel] += error * 3 / 8;
                    
                }
                else
                {
                    if(pixel[i][j][channel] <= 0.5)
                    {
                        output[i][j][channel] = 0;
                    }
                    else
                    {
                        output[i][j][channel] = 1;
                    }
                    
                    error = pixel[i][j][channel] - output[i][j][channel];
                    pixel[i][j - 1][channel] += error * 7 / 16;
                    pixel[i + 1][j - 1][channel] += error * 1 / 16;
                    pixel[i + 1][j][channel] += error * 5 / 16;
                    pixel[i + 1][j + 1][channel] += error * 3 / 16;
                    
                }
            }
        }
    }
    
    
    ////// copy back to vector ////////
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            v.at(i * width + j).cmy[channel] = output[i][j][channel];
        }
    }
    
}



pyramid MBVQ(double C, double M, double Y)
{
    
    if((C + M) < 1)
    {
        if((M + Y) < 1)
        {
            if((C + M + Y) < 1)
            {
                //show(CMYW);
                return CMYW;
                
            }
            else
            {
                //show(MYGC);
                return MYGC;
                
            }
        }
        else
        {
            //show(RGMY);
            return RGMY;
            
        }
    }
    else
    {
        if(!((M + Y) < 1))
        {
            if(!((C + M + Y) < 2))
            {
                //show(KRGB);
                return KRGB;
                
            }
            else
            {
                //show(RGBM);
                return RGBM;
                
            }
        }
        else
        {
            //show(CMGB);
            return CMGB;
            
        }
    }

}


color findShortestDistance(struct color p, pyramid x)
{
    double d[4], min;
    color p1;
    
    d[0] = sqrt((p.c - x.p1[1]) * (p.c - x.p1[1]) + (p.m - x.p1[0]) * (p.m - x.p1[0]) + (p.y - x.p1[2]) * (p.y - x.p1[2]));
    d[1] = sqrt((p.c - x.p2[1]) * (p.c - x.p2[1]) + (p.m - x.p2[0]) * (p.m - x.p2[0]) + (p.y - x.p2[2]) * (p.y - x.p2[2]));
    d[2] = sqrt((p.c - x.p3[1]) * (p.c - x.p3[1]) + (p.m - x.p3[0]) * (p.m - x.p3[0]) + (p.y - x.p3[2]) * (p.y - x.p3[2]));
    d[3] = sqrt((p.c - x.p4[1]) * (p.c - x.p4[1]) + (p.m - x.p4[0]) * (p.m - x.p4[0]) + (p.y - x.p4[2]) * (p.y - x.p4[2]));
    
    
    
    min = d[0];
    
    for(int i = 1; i < 4; i++)
    {
        if(min > d[i])
        {
            min = d[i];
        }
    
    }
    
    if(min == d[0])
    {
        p1.c = x.p1[1];
        p1.m = x.p1[0];
        p1.y = x.p1[2];
        
    }
    else if(min == d[1])
    {
        p1.c = x.p2[1];
        p1.m = x.p2[0];
        p1.y = x.p2[2];
    }
    else if(min == d[2])
    {
        p1.c = x.p3[1];
        p1.m = x.p3[0];
        p1.y = x.p3[2];
    }
    else if(min == d[3])
    {
        p1.c = x.p4[1];
        p1.m = x.p4[0];
        p1.y = x.p4[2];
    }
    return p1;
}


void colorErrorDiffusion(vector<struct pixel> &v)
{
    int i, j, k;
    double input[height][width][bytes];
    double updated[height][width][bytes];
    double output[height][width][bytes];
    double error[bytes];
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            for(k = 0; k < bytes; k++)
            {
                input[i][j][k] = v.at(i * width + j).cmy[k]; ////original
                updated[i][j][k] = v.at(i * width + j).cmy[k]; //// updated
            }
        }
    }
    
    
    ///////////////// even row  begins ///////////////////////////
    
    for(i = 0; i < height; i += 2)
    {
        for(j = 0; j < width; j++)
        {
            color updated_p;
            updated_p.c = updated[i][j][0];
            updated_p.m = updated[i][j][1];
            updated_p.y = updated[i][j][2];
            
            
            pyramid pyr = MBVQ(input[i][j][0], input[i][j][1], input[i][j][2]); /// find area
            
            
            color out_p = findShortestDistance(updated_p, pyr);/// find output color
            
            output[i][j][0] = out_p.c;
            output[i][j][1] = out_p.m;
            output[i][j][2] = out_p.y;
            
            if(j == 0)
            {
                
                for(k = 0; k < bytes; k++)
                {
                    error[k] = updated[i][j][k] - output[i][j][k];
                    updated[i][j + 1][k] += error[k] * 7 / 13;
                    updated[i + 1][j][k] += error[k] * 5 / 13;
                    updated[i + 1][j + 1][k] += error[k] * 1 / 13;
                }
                
            }
            else if(j == (width - 1))
            {
                for(k = 0; k < bytes; k++)
                {
                    error[k] = updated[i][j][k] - output[i][j][k];
                    updated[i + 1][j][k] += error[k] * 5 / 8;
                    updated[i + 1][j - 1][k] += error[k] * 3 / 8;
                }
            }
            else
            {
                for(k = 0; k < bytes; k++)
                {
                    error[k] = updated[i][j][k] - output[i][j][k];
                    updated[i][j + 1][k] += error[k] * 7 / 16;
                    updated[i + 1][j - 1][k] += error[k] * 3 / 16;
                    updated[i + 1][j][k] += error[k] * 5 / 16;
                    updated[i + 1][j + 1][k] += error[k] * 1 / 16;
                }
            }
        }
    }

    
    
    
    ////// odd row begins ////////
    
    for(i = 1; i < height; i += 2)
    {
        for(j = width - 1; j >= 0; j--)
        {
            
            color updated_p1;
            updated_p1.c = updated[i][j][0];
            updated_p1.m = updated[i][j][1];
            updated_p1.y = updated[i][j][2];
     
            pyramid pyr1 = MBVQ(input[i][j][0], input[i][j][1], input[i][j][2]); /// find area
            
            color out_p1 = findShortestDistance(updated_p1, pyr1);/// find output color
            
            
            output[i][j][0] = out_p1.c;
            output[i][j][1] = out_p1.m;
            output[i][j][2] = out_p1.y;

            
            
            
            if(i == height - 1)///////////  last row  ////////
            {
                if(j == 0)
                {
                    for(k = 0; k < bytes; k++)
                    {
                        error[k] = 0;
                        updated[i][j - 1][k] += error[k];
                    }
                }
                else
                {
                    for(k = 0; k < bytes; k++)
                    {
                        error[k] = updated[i][j][k] - output[i][j][k];
                        updated[i][j - 1][k] += error[k];
                    }
                }
            }
            else////////////  other odd rows ///////////////
            {
                
                if(j == width - 1)
                {
                    for(k = 0; k < bytes; k++)
                    {
                        error[k] = updated[i][j][k] - output[i][j][k];
                        updated[i][j - 1][k] += error[k] * 7 / 13;
                        updated[i + 1][j][k] += error[k] * 5 / 13;
                        updated[i + 1][j - 1][k] += error[k] * 1 / 13;
                    }
                    
                }
                else if(j == 0)
                {
                    
                    for(k = 0; k < bytes; k++)
                    {
                        error[k] = updated[i][j][k] - output[i][j][k];
                        updated[i + 1][j][k] += error[k] * 5 / 8;
                        updated[i + 1][j + 1][k] += error[k] * 3 / 8;
                    }
                    
                }
                else
                {
                    
                    for(k = 0; k < bytes; k++)
                    {
                        error[k] = updated[i][j][k] - output[i][j][k];
                        updated[i][j - 1][k] += error[k] * 7 / 16;
                        updated[i + 1][j - 1][k] += error[k] * 1 / 16;
                        updated[i + 1][j][k] += error[k] * 5 / 16;
                        updated[i + 1][j + 1][k] += error[k] * 3 / 16;
                    }
                    
                }
            }
        }
    }

    ////// copy back to vector ////////
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            for(k = 0; k < bytes; k++)
            {
                v.at(i * width + j).cmy[k] = output[i][j][k];
            }
        }
    }

}






/*void show(pyramid pyr)
{
    cout << "(" << pyr.p1[0] << "," << pyr.p1[1] << "," << pyr.p1[2] << ")";
    cout << "(" << pyr.p2[0] << "," << pyr.p2[1] << "," << pyr.p2[2] << ")";
    cout << "(" << pyr.p3[0] << "," << pyr.p3[1] << "," << pyr.p3[2] << ")";
    cout << "(" << pyr.p4[0] << "," << pyr.p4[1] << "," << pyr.p4[2] << ")";
    cout << endl;
}*/


void initialize()
{
    //cout<< " hhhhhhhhhhhh";
    for(int i = 0; i < 3; i++)
    {
        CMYW.p1[i] = C[i];
        CMYW.p2[i] = M[i];
        CMYW.p3[i] = Y[i];
        CMYW.p4[i] = W[i];
    }
    
    for(int i = 0; i < 3; i++)
    {
        MYGC.p1[i] = M[i];
        MYGC.p2[i] = Y[i];
        MYGC.p3[i] = G[i];
        MYGC.p4[i] = C[i];
    }
    
    for(int i = 0; i < 3; i++)
    {
        RGMY.p1[i] = R[i];
        RGMY.p2[i] = G[i];
        RGMY.p3[i] = M[i];
        RGMY.p4[i] = Y[i];
    }
    
    for(int i = 0; i < 3; i++)
    {
        KRGB.p1[i] = K[i];
        KRGB.p2[i] = R[i];
        KRGB.p3[i] = G[i];
        KRGB.p4[i] = B[i];
    }
    
    for(int i = 0; i < 3; i++)
    {
        RGBM.p1[i] = R[i];
        RGBM.p2[i] = G[i];
        RGBM.p3[i] = B[i];
        RGBM.p4[i] = M[i];
    }
    
    for(int i = 0; i < 3; i++)
    {
        CMGB.p1[i] = C[i];
        CMGB.p2[i] = M[i];
        CMGB.p3[i] = G[i];
        CMGB.p4[i] = B[i];
    }
}




