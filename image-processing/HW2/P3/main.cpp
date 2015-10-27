#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
using namespace std;



void readFile(const char *r_fileName, vector<struct graypixel> &v);
void fixedThreshold(vector<struct graypixel> &v, vector<struct graypixel> &v1);
void writeFile(const char *n_fileName, vector<struct graypixel> &v1);
void randomThreshold(vector<struct graypixel> &v, vector<struct graypixel> &v1);
void matrix44(vector<double> &d_v22, vector<double> &d_v44);
void matrix22(vector<double> &d_v22);
void thre_matrix(int n, vector<double> &d_vnn, vector<double> &d_vthre);
double find_min(vector<struct graypixel> &v);
double find_max(vector<struct graypixel> &v);
void normalization(int l, vector<struct graypixel> &v, int flag);
void ditherMatrix(int n, vector<struct graypixel> &v, vector<double> &d_vthre);
void errorDiffusion(vector<struct graypixel> &v);



struct graypixel{
    int x, y;
    unsigned char gray;
    double d_gray;
};



int height = 512;
int width = 512;
int T = 100;
int lumin = 255;
int flag_char = 1;
int flag_double = 0;
int n = 2;

int main()
{
    const char *r_fileName = "boat.raw";
    const char *fixed_fileName = "boat_fixedthr.raw";
    const char *random_fileName = "boat_randomthr.raw";
    const char *matrix_fileName = "boat_matrixthr.raw";
    const char *errdif_fileName = "boat_errdif.raw";
    vector<struct graypixel> v;
    vector<struct graypixel> v1;
    vector<double> d_v22;
    vector<double> d_v44;
    vector<double> d_vthre;
    //vector<double> d_v;
    
    ///// problem a(1) and a(2) //////
    
    readFile(r_fileName, v);
    //fixedThreshold(v, v1);
    //randomThreshold(v,v1);
    //writeFile(random_fileName, v1);
    
    
    /////// problem a(3) ///////
    
    //matrix22(d_v22);
    //matrix44(d_v22, d_v44);
    /*thre_matrix(n, d_v22, d_vthre);
    normalization(1, v, flag_char);
    ditherMatrix(n, v, d_vthre);
    normalization(255, v, flag_double);
    writeFile(matrix_fileName, v);*/
    
    ///// problem b ////////
    
    readFile(r_fileName, v);
    normalization(1, v, flag_char);
    errorDiffusion(v);
    normalization(255, v, flag_double);
    writeFile(errdif_fileName, v);
    
    
}

void readFile(const char *r_fileName, vector<struct graypixel> &v)
{
    
    
    FILE *file;
    unsigned char s_Data[height][width];
    graypixel p;
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    fread(s_Data, sizeof(unsigned char), width * height, file);
    fclose(file);
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p.gray = s_Data[i][j];
            v.push_back(p);
        }
    }
}



void fixedThreshold(vector<struct graypixel> &v, vector<struct graypixel> &v1)
{
    graypixel p;
    
    for(int i = 0; i < v.size(); i++)
    {
        if(v.at(i).gray <= T && v.at(i).gray >= 0)
        {
            p.gray = 0;
            v1.push_back(p);
        }
        else if(v.at(i).gray > T && v.at(i).gray <= 255)
        {
            p.gray = 255;
            v1.push_back(p);
        }
    }
}



void writeFile(const char *n_fileName, vector<struct graypixel> &v1)
{
    
    FILE *file;
    unsigned char out[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out[i][j] = v1.at(i * width + j).gray;
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(out, sizeof(unsigned char), width * height, file);
    fclose(file);
}


void randomThreshold(vector<struct graypixel> &v, vector<struct graypixel> &v1)
{
    graypixel p;
    srand((unsigned)time(NULL));
    
    for(int i = 0; i < v.size(); i++)
    {
        int n = rand()%lumin;
        
        if(v.at(i).gray <=  n)
        {
            p.gray = 255;
            v1.push_back(p);
        }
        else if(v.at(i).gray > n)
        {
            p.gray = 0;
            v1.push_back(p);
        }
    }
    
}


void matrix22(vector<double> &d_v22)
{
    d_v22.push_back(1);
    d_v22.push_back(2);
    d_v22.push_back(3);
    d_v22.push_back(0);
    
    /*for(int i = 0; i < 4; i++)
    {
        cout<< d_v.at(i) << endl;
    }*/
}


void matrix44(vector<double> &d_v22, vector<double> &d_v44)
{
    double matrix22[2][2];
    double matrix44[4][4];
    int i, j;
    
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            matrix22[i][j] = d_v22.at(i * 2 + j);
            //cout<< matrix22[i][j] << endl;
        }
    }
    
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            matrix44[i][j] = matrix22[i][j] * 4 + 1;
            matrix44[i][j + 2] = matrix22[i][j] * 4 + 2;
            matrix44[i + 2][j] = matrix22[i][j] * 4 + 3;
            matrix44[i + 2][j + 2] = matrix22[i][j] * 4;
            //cout<<  << endl
        }
    }
    
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            d_v44.push_back(matrix44[i][j]);
            //cout<< d_v1.at(i) << endl;
        }
    }
    
    /*for(i = 0; i < 16; i++)
    {
        cout<< d_v1.at(i) << endl;
    }*/
}


void thre_matrix(int n, vector<double> &d_vnn, vector<double> &d_vthre)
{
    double temp;
    
    for(int i = 0; i < n * n; i++)
    {
        temp = (d_vnn.at(i) + 0.5) / (n * n);
        d_vthre.push_back(temp);
        //cout << temp << endl;
    }
}


double find_max(vector<struct graypixel> &v, int flag)
{
    double max;
    if(flag == flag_char)
    {
        
        max = (double)v.at(0).gray;
    
        for(int i = 1; i < height * width; i++)
        {
            if(max < (double)v.at(i).gray)
            {
                max = (double)v.at(i).gray;
            }
        }
        //cout << max<<endl;
        //return max;
    }
    else if(flag == flag_double)
    {
        
        max = v.at(0).d_gray;
        
        for(int i = 1; i < height * width; i++)
        {
            if(max < v.at(i).d_gray)
            {
                max = v.at(i).d_gray;
            }
        }
        //cout << max<<endl;
        //return max;
    }
    return max;
}


double find_min(vector<struct graypixel> &v, int flag)
{
    double min;
    if(flag == flag_char)
    {
        
        min = (double)v.at(0).gray;
        
        for(int i = 1; i < height * width; i++)
        {
            if(min > (double)v.at(i).gray)
            {
                min = (double)v.at(i).gray;
            }
        }
        //cout << max<<endl;
        //return max;
    }
    else if(flag == flag_double)
    {
        
        min = v.at(0).d_gray;
        
        for(int i = 1; i < height * width; i++)
        {
            if(min > v.at(i).d_gray)
            {
                min = v.at(i).d_gray;
            }
        }
        //cout << max<<endl;
        //return max;
    }
    return min;

}


void normalization(int l, vector<struct graypixel> &v, int flag)
{
    double max, min;
    //graypixel p;
    
    
    if(flag == flag_char)
    {
        max = find_max(v, flag);
        min = find_min(v, flag);
        
        //cout<< max << " " << min << endl;
        for(int i = 0; i < height * width; i++)
        {
            v.at(i).d_gray = ((double)(v.at(i).gray - min) * l) / (max - min);
        }
    }
    else if(flag == flag_double)
    {
        max = find_max(v, flag);
        min = find_min(v, flag);
        
        //cout<< max << " " << min << endl;
        for(int i = 0; i < height * width; i++)
        {
            v.at(i).gray = (unsigned char)(((v.at(i).d_gray - min) * l) / (max - min));
        }

    }
    
}


void ditherMatrix(int n, vector<struct graypixel> &v, vector<double> &d_vthre)
{
    double input[height][width];
    //double output[height][width];
    double matrix[n][n];
    int i, j;
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            input[i][j] = v.at(i * width + j).d_gray;
        }
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            matrix[i][j] = d_vthre.at(i * n + j);
        }
    }
    
    for(i = 0; i < height; i += n)
    {
        for(j = 0; j < width; j += n)
        {
            for(int m = i; m < i + n; m++)
            {
                for(int f = j; f < j + n; f++)
                {
                    if(input[m][f] > matrix[m - i][f - j])
                    {
                        v.at(m * width + f).d_gray = 1;
                        //d_v.push_back(output[m][f]);
                    }
                    else
                    {
                        v.at(m * width + f).d_gray = 0;
                        //d_v.push_back(output[m][f]);
                    }
                }
            }
        }
    }

}


void errorDiffusion(vector<struct graypixel> &v)
{
    int i, j;
    double pixel[height][width];
    double output[height][width];
    double error;
    
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            pixel[i][j] = v.at(i * width + j).d_gray;
        }
    }
    
    
    //// even rows begins /////////
    
    for(i = 0; i < height; i += 2)
    {
        for(j = 0; j < width; j++)
        {
            if(j == 0)
            {
                if(pixel[i][j] <= 0.5)
                {
                    output[i][j] = 0;
                    error = pixel[i][j] - output[i][j];
                    pixel[i][j + 1] = pixel[i][j + 1] + error * 7 / 13;
                    pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 13;
                    pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 1 / 13;
                }
                else
                {
                    output[i][j] = 1;
                    error = pixel[i][j] - output[i][j];
                    pixel[i][j + 1] = pixel[i][j + 1] + error * 7 / 13;
                    pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 13;
                    pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 1 / 13;
                }
            }
            else if(j == (width - 1))
            {
                if(pixel[i][j] <= 0.5)
                {
                    output[i][j] = 0;
                    error = pixel[i][j] - output[i][j];
                    pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 8;
                    pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 3 / 8;
                }
                else
                {
                    output[i][j] = 1;
                    error = pixel[i][j] - output[i][j];
                    pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 8;
                    pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 3 / 8;
                }
            }
            else
            {
                if(pixel[i][j] <= 0.5)
                {
                    output[i][j] = 0;
                    error = pixel[i][j] - output[i][j];
                    pixel[i][j + 1] = pixel[i][j + 1] + error * 7 / 16;
                    pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 3 / 16;
                    pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 16;
                    pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 1 / 16;
                }
                else
                {
                    output[i][j] = 1;
                    error = pixel[i][j] - output[i][j];
                    pixel[i][j + 1] = pixel[i][j + 1] + error * 7 / 16;
                    pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 3 / 16;
                    pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 16;
                    pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 1 / 16;
                }

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
                    if(pixel[i][j] <= 0.5)
                    {
                        output[i][j] = 0;
                    }
                    else
                    {
                        output[i][j] = 1;
                    }
                }
                else
                {
                    if(pixel[i][j] <= 0.5)
                    {
                        output[i][j] = 0;
                        error = pixel[i][j] - output[i][j];
                        pixel[i][j - 1] = pixel[i][j - 1] + error;
                    }
                    else
                    {
                        output[i][j] = 1;
                        error = pixel[i][j] - output[i][j];
                        pixel[i][j - 1] = pixel[i][j - 1] + error;
                    }

                }
            }
            else
            {
            
                if(j == width - 1)
                {
                    if(pixel[i][j] <= 0.5)
                    {
                        output[i][j] = 0;
                        error = pixel[i][j] - output[i][j];
                        pixel[i][j - 1] = pixel[i][j - 1] + error * 7 / 13;
                        pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 13;
                        pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 1 / 13;
                    }
                    else
                    {
                        output[i][j] = 1;
                        error = pixel[i][j] - output[i][j];
                        pixel[i][j - 1] = pixel[i][j - 1] + error * 7 / 13;
                        pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 13;
                        pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 1 / 13;
                    }
                }
                else if(j == 0)
                {
                    if(pixel[i][j] <= 0.5)
                    {
                        output[i][j] = 0;
                        error = pixel[i][j] - output[i][j];
                        pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 8;
                        pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 3 / 8;
                    }
                    else
                    {
                        output[i][j] = 1;
                        error = pixel[i][j] - output[i][j];
                        pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 8;
                        pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 3 / 8;
                    }
                }
                else
                {
                    if(pixel[i][j] <= 0.5)
                    {
                        output[i][j] = 0;
                        error = pixel[i][j] - output[i][j];
                        pixel[i][j - 1] = pixel[i][j - 1] + error * 7 / 16;
                        pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 1 / 16;
                        pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 16;
                        pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 3 / 16;
                    }
                    else
                    {
                        output[i][j] = 1;
                        error = pixel[i][j] - output[i][j];
                        pixel[i][j - 1] = pixel[i][j - 1] + error * 7 / 16;
                        pixel[i + 1][j - 1] = pixel[i + 1][j - 1] + error * 1 / 16;
                        pixel[i + 1][j] = pixel[i + 1][j] + error * 5 / 16;
                        pixel[i + 1][j + 1] = pixel[i + 1][j + 1] + error * 3 / 16;
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
            v.at(i * width + j).d_gray = output[i][j];
        }
    }

}






