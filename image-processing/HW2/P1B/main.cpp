#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;


void readFile(const char *r_fileName, vector<struct pixel> &v);
void enlarge(vector<struct pixel> &v);
void writeFile(const char *n_fileName, vector<struct pixel> &v);
double find_max(vector<struct pixel> &v, int channel, int flag);
double find_min(vector<struct pixel> &v, int channel, int flag);
void normalization(int l, vector<struct pixel> &v, int channel, int flag);
void gaussian(double sigma, vector<double> &v1);
void DOG(vector<struct pixel> &v, vector<double> &v1);
void passValue(vector<struct pixel> &v, vector<struct pixel> &v2);
void XDOG(vector<struct pixel> &v, vector<struct pixel> &v2, vector<struct pixel> &v4);
void changeToGray(vector<struct pixel> &v);
double fmax(vector<struct pixel> &v, int flag);
double fmin(vector<struct pixel> &v, int flag);
void normal(int l, vector<struct pixel> &v, int flag);
void BilateralFilter(int channel, vector<struct pixel> &v);
void enlarge_color(vector<struct pixel> &v);
void writeFile1(const char *n_fileName, vector<struct pixel> &v);
void combine(vector<struct pixel> &v4, vector<struct pixel> &v6, vector<struct pixel> &v8);
void processDOG(vector<struct pixel> &v, vector<struct pixel> &v2, vector<struct pixel> &v4);




struct pixel
{
    unsigned char rgb[3];
    //double i_rgb[3];
    double d_rgb[3];
    double gray;
    unsigned char gray_char;
};






int height = 300;
int width = 400;
int bytes = 3;
int red = 0;
int green = 1;
int blue = 2;
int flag_char = 1;
int flag_double = 0;
int len = 5;
int n = (len - 1) / 2;
double PI = 3.13141;
double sigma = 1.0;
double k = sqrt(1.6);
double tao = 0.985;
double ibisi = 12;
double afa = 0.3;
int cc = 10;
int ss = 10;



int main()
{
    //cout << "1111111111" << endl;
    vector<struct pixel> v;
    vector<struct pixel> v2;
    vector<struct pixel> v4;
    vector<struct pixel> v6;
    vector<struct pixel> v8;
    vector<double> v1;
    vector<double> v3;
    
    const char *r_fileName = "Scarlett.raw";
    const char *n_fileName = "Scarlett111111111.raw";
    
    const char *n1_fileName = "Scarlett_banary.raw";
    const char *n2_fileName = "Scarlett_combine.raw";
    readFile(r_fileName, v);
    changeToGray(v);
    enlarge(v);
    //cout<< "1111111"<< endl;
    //normalization(1, v, red, flag_char);
    //normalization(1, v, green, flag_char);
    //normalization(1, v, blue, flag_char);
    
    passValue(v, v2);
    
    gaussian(sigma, v1);
    gaussian(k * sigma, v3);
    DOG(v, v1);
    DOG(v2, v3);
    //XDOG(v, v2, v4);
    cout<< "1111111"<< endl;
    processDOG(v, v2, v4);
    cout<< "1111111"<< endl;
    //normalization(255, v4, red, flag_double);
    //normalization(255, v4, green, flag_double);
    //normalization(255, v4, blue, flag_double);
    
    normal(255, v4, flag_double);
    
    normal(1, v4, flag_char);
    
    //writeFile(n_fileName, v4);
    
    
    readFile(r_fileName, v6);
    
    for(int i = 0; i < 10; i++)
    {
        
    BilateralFilter(0, v6);
       
    BilateralFilter(1, v6);
        
    BilateralFilter(2, v6);
    }
    combine(v4, v6, v8);
    
    writeFile1(n2_fileName, v8);
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
            for(int w = 0; w < bytes; w++)
            {
                p.rgb[w] = input[i][j][w];
            }
            v.push_back(p);
        }
    }
    
}


void passValue(vector<struct pixel> &v, vector<struct pixel> &v2)
{
    pixel p;
    
    for(int i = 0; i < v.size(); i++)
    {
        
        p.gray = v.at(i).gray;
        
        //cout << v.at(i).gray << " " ;
        
        v2.push_back(p);
    }
}

void enlarge(vector<struct pixel> &v)
{
    
    unsigned char le_Data[height][width];
    unsigned char le1_Data[height + 2 * n][width];
    //const char *fName[3] = {"data1.txt", "data2.txt", "data3.txt"};
    //int lumin = 256;
    
    
    struct pixel p;
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            le_Data[i][j] = v.at(i * width + j).gray;
            
        }
    }
    
    v.clear();
    
    /* int count[lumin][BytesPerPixel];
     
     //////// let items in count array all equal to 0/////////
     
     for(int i = 0; i < lumin; i++)
     {
     for(int j = 0; j < BytesPerPixel; j++)
     {
     count[i][j] = 0;
     }
     }
     
     ////////////count the number of pixels in each scale//////////
     
     for(int i = 0; i < height * width; i++)
     {
     for(int j = 0; j < lumin; j++)
     {
     
     if(v0.at(i).r == j)
     {
     count[j][0]++;
     }
     if(v0.at(i).g == j)
     {
     count[j][1]++;
     }
     if(v0.at(i).b == j)
     {
     count[j][2]++;
     }
     
     }
     
     }
     
     /////////////write in txt file//////////////////////
     
     for(int j = 0; j < BytesPerPixel; j++)
     {
     if((file = fopen(fName[j], "wb")) != NULL)
     {
     for(int i = 0; i < lumin; i++)
     {
     fprintf(file, "%d ", count[i][j]);
     }
     }
     fclose(file);
     }*/
    
    
    ///////////////////copy in le1_Data array////////////////////////////
    ;
    
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            le1_Data[i][j] = le_Data[n-i][j];
            
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            le1_Data[i + n][j] = le_Data[i][j];
            
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            le1_Data[height - 1 + 2 * n - i][j] = le_Data[height - 1 - n + i][j];
            
        }
    }
    
    
    
    
    
    ///////////////////////////copy in s2_Data from s1_Data////////////////////////
    
    unsigned char le2_Data[height + 2 * n][width + 2 * n];
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            
            
            le2_Data[i][j] = le1_Data[i][n - j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width; j++)
        {
           
            
            le2_Data[i][j + n] = le1_Data[i][j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            
            
            le2_Data[i][width - 1 + 2 * n - j] = le1_Data[i][width - 1 - n + j];
            
        }
    }
    
    //////////////  test //////////////
    
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width + 2 * n; j++)
        {
            
            
            p.gray = le2_Data[i][j];
            
            v.push_back(p);
        }
    }
    
    
}



void writeFile(const char *n_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char output[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            output[i][j] = v.at(i * width + j).gray_char;
            
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), width * height, file);
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


void gaussian(double sigma, vector<double> &v1)
{
    int i, j;
    double temp, dis, g;
    
    for(i = 0; i < 2 * n + 1; i++)
    {
        for(j = 0; j < 2 * n + 1; j++)
        {
            dis = sqrt((n - i) * (n - i) + (n - j) * (n - j));
            temp = exp( - ((dis * dis) / (2 * sigma * sigma)));
            g = temp / (2 * PI * sigma * sigma);
            //cout << g << " ";
            v1.push_back(g);
        }
    }
}


void DOG(vector<struct pixel> &v, vector<double> &v1)
{
    double a[height + 2 * n][width + 2 * n];
    double b[2 * n + 1][2 * n + 1];
    int i, j, m, f;
    double sum;
    pixel p;
    
    for(i = 0; i < height + 2 * n; i++)
    {
        for(j = 0; j < width + 2 * n; j++)
        {
            
            a[i][j] = v.at(i * (width + 2 * n) + j).gray;
        }
    }
    
    v.clear();
    
    for(i = 0; i < 1 + 2 * n; i++)
    {
        for(j = 0; j < 1 + 2 * n; j++)
        {
            b[i][j] = v1.at(i * (1 + 2 * n) + j);
            //cout << b[i][j] << endl;
        }
    }

    v1.clear();
    
    for(m = 0; m < height; m++)
    {
        for(f = 0; f < width; f++)
        {
            
            
            sum = 0;
            
            for(i = m; i < m + 2 * n + 1; i++)
            {
                for(j = f; j < f + 2 * n + 1; j++)
                {
                    sum += a[i][j] * b[i - m][j - f];
                }
            }
            p.gray = sum;
            
            
            v.push_back(p);
            
        }
    }
    
    

}

void processDOG(vector<struct pixel> &v, vector<struct pixel> &v2, vector<struct pixel> &v4)
{
    pixel p;
    double dif;
    
    for(int i = 0; i < v.size(); i++)
    {
        dif = v.at(i).gray - v2.at(i).gray;
        //cout << dif << " ";
        if(dif < 0)
        {
            p.gray = 0;
        }
        else
        {
            p.gray = 1;
        }
        v4.push_back(p);
    }
    
    
}



void XDOG(vector<struct pixel> &v, vector<struct pixel> &v2, vector<struct pixel> &v4)
{
    pixel p;
    double dx;
    
    for(int i = 0; i < v.size(); i++)
    {
        
        dx = v.at(i).gray - tao * v2.at(i).gray;
        //cout << dx << " ";
        if(dx < ibisi)
        {
            p.gray = 1;
        }
        else
        {
            p.gray = 1 + tanh(afa * dx);
        }
        
        v4.push_back(p);
    }
}


void changeToGray(vector<struct pixel> &v)
{
    for(int i = 0; i < v.size(); i++)
    {
        v.at(i).gray = v.at(i).rgb[0] * 0.21 + v.at(i).rgb[1] * 0.72 + v.at(i).rgb[2] * 0.07;
    }
}

void normal(int l, vector<struct pixel> &v, int flag)
{
    double max, min;
    
    if(flag == flag_char)
    {
        max = fmax(v, flag);
        min = fmin(v, flag);
        
        //cout<< max << " " << min << endl;
        for(int i = 0; i < height * width; i++)
        {
            v.at(i).gray = ((double)(v.at(i).gray_char - min) * l) / (max - min);
        }

    }
    else if(flag == flag_double)
    {
        max = fmax(v, flag);
        min = fmin(v, flag);
    
        //cout<< max << " " << min << endl;
        for(int i = 0; i < height * width; i++)
        {
        
            v.at(i).gray_char = (unsigned char)(((v.at(i).gray - min) * l) / (max - min));
        }
    }

}

double fmax(vector<struct pixel> &v, int flag)
{
    double max;
    
    if(flag == flag_char)
    {
        max = (double)v.at(0).gray_char;
        
        for(int i = 1; i < height * width; i++)
        {
            if(max < (double)v.at(i).gray_char)
            {
                max = (double)v.at(i).gray_char;
            }
        }
        
    }
    else if(flag == flag_double)
    {
        max = v.at(0).gray;
    
        for(int i = 1; i < height * width; i++)
        {
            if(max < v.at(i).gray)
            {
                max = v.at(i).gray;
            }
        }
    }
    
    return max;
}

double fmin(vector<struct pixel> &v, int flag)
{
    double min;
    
    if(flag == flag_char)
    {
        min = (double)v.at(0).gray_char;
        
        for(int i = 1; i < height * width; i++)
        {
            if(min > (double)v.at(i).gray_char)
            {
                min = (double)v.at(i).gray_char;
            }
        }

    }
    else if(flag == flag_double)
    {
        min = v.at(0).gray;
    
        for(int i = 1; i < height * width; i++)
        {
            if(min > v.at(i).gray)
            {
                min = v.at(i).gray;
            }
        }
    }
    
    return min;
}



void BilateralFilter(int channel, vector<struct pixel> &v)
{
    
     enlarge_color(v);
    
    
    
    //vector<int> v1;
    int temp;
    unsigned char a[height + 2 * n][width + 2 * n][bytes];
    unsigned char out[height][width][bytes];
    struct pixel p;
    
    
    
    ///////// vector transfer to an 3D array /////////
    
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width + 2 * n; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                a[i][j][w] = v.at(i * (width + 2 * n) + j).rgb[w];
            }
            
        }
    }
    
    
    v.clear();
    
    
    for(int m = 0; m < height; m++)
    {
        for(int f = 0; f < width; f++)
        {
            
            /////copy pixels in structure vector/////////
            
            double sum = 0;
            double sum1 = 0;
            
            for(int i = m; i < m + len; i++)
            {
                for(int j = f; j < f + len; j++)
                {
                    
                    double c = 0;
                    double s = 0;
                    float dis = 0;
                    int valdif = 0;
                    
                    
                    
                    dis = sqrt(((m + n) - i) * ((m + n) - i) + ((f + n) - j) * ((f + n) - j));/// distance
                    c = exp( - ((dis * dis) / (2 * cc * cc)));
                    
                    
                    valdif = a[m + n][f + n][channel] - a[i][j][channel];/// value difference
                    s = exp( - ((valdif * valdif) / (2 * ss * ss)));
                    
                    sum = sum + c * s * a[i][j][channel];
                    sum1 = sum1 + c * s;
                }
            }
            
            temp = (int)(sum / sum1);
            
            //pass the value to the middle of window//
            
            
            if(channel == 0)
            {
                out[m][f][channel] = temp;
                out[m][f][1] = a[m + n][f + n][1];
                out[m][f][2] = a[m + n][f + n][2];
            }
            else if(channel == 1)
            {
                out[m][f][channel] = temp;
                out[m][f][0] = a[m + n][f + n][0];
                out[m][f][2] = a[m + n][f + n][2];
            }
            else if(channel == 2)
            {
                out[m][f][channel] = temp;
                out[m][f][0] = a[m + n][f + n][0];
                out[m][f][1] = a[m + n][f + n][1];
            }
            
            
            
        }
    }
    
    
    
    
    /////////// pass data from array to a vector /////////
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                p.rgb[w] = out[i][j][w];
            }
            v.push_back(p);
            
        }
    }
    
    
    
}

void enlarge_color(vector<struct pixel> &v)
{
    
    unsigned char le_Data[height][width][bytes];
    unsigned char le1_Data[height + 2 * n][width][bytes];
    //const char *fName[3] = {"data1.txt", "data2.txt", "data3.txt"};
    //int lumin = 256;
    
    
    struct pixel p;
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                le_Data[i][j][w] = v.at(i * width + j).rgb[w];
            }
        }
    }
    
    v.clear();
    
    /* int count[lumin][BytesPerPixel];
     
     //////// let items in count array all equal to 0/////////
     
     for(int i = 0; i < lumin; i++)
     {
     for(int j = 0; j < BytesPerPixel; j++)
     {
     count[i][j] = 0;
     }
     }
     
     ////////////count the number of pixels in each scale//////////
     
     for(int i = 0; i < height * width; i++)
     {
     for(int j = 0; j < lumin; j++)
     {
     
     if(v0.at(i).r == j)
     {
     count[j][0]++;
     }
     if(v0.at(i).g == j)
     {
     count[j][1]++;
     }
     if(v0.at(i).b == j)
     {
     count[j][2]++;
     }
     
     }
     
     }
     
     /////////////write in txt file//////////////////////
     
     for(int j = 0; j < BytesPerPixel; j++)
     {
     if((file = fopen(fName[j], "wb")) != NULL)
     {
     for(int i = 0; i < lumin; i++)
     {
     fprintf(file, "%d ", count[i][j]);
     }
     }
     fclose(file);
     }*/
    
    
    ///////////////////copy in le1_Data array////////////////////////////
    ;
    
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                le1_Data[i][j][w] = le_Data[n-i][j][w];
            }
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                le1_Data[i + n][j][w] = le_Data[i][j][w];
            }
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                le1_Data[height - 1 + 2 * n - i][j][w] = le_Data[height - 1 - n + i][j][w];
            }
        }
    }
    
    
    
    
    
    ///////////////////////////copy in s2_Data from s1_Data////////////////////////
    
    unsigned char le2_Data[height + 2 * n][width + 2 * n][bytes];
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                le2_Data[i][j][w] = le1_Data[i][n - j][w];
            }
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                le2_Data[i][j + n][w] = le1_Data[i][j][w];
            }
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                le2_Data[i][width - 1 + 2 * n - j][w] = le1_Data[i][width - 1 - n + j][w];
            }
        }
    }
    
    //////////////  test //////////////
    
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width + 2 * n; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                p.rgb[w] = le2_Data[i][j][w];
            }
            v.push_back(p);
        }
    }
    
    
}


void writeFile1(const char *n_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char output[height][width][bytes];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int w = 0; w < bytes; w++)
            {
                output[i][j][w] = v.at(i * (width) + j).rgb[w];
            }
            
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (width) * (height) * bytes, file);
    fclose(file);
}



void combine(vector<struct pixel> &v4, vector<struct pixel> &v6, vector<struct pixel> &v8)
{
    pixel p;
    
    for(int i = 0; i < height * width; i++)
    {
        
        for(int w = 0; w < bytes; w++)
        {
            p.rgb[w] = v4.at(i).gray * v6.at(i).rgb[w];
        }
        v8.push_back(p);
    }
}


