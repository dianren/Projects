#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;



void enlarge(int height, int width, int BytesPerPixel, int len, const char *r_fileName, vector<struct pixel> &v);

void BilateralFilter(int height, int width, int BytesPerPixel, int channel, int len, int cc, int ss, const char *r_fileName, const char *n_fileName, vector<struct pixel> &v);

void unlinerfilter(int height, int width, int BytesPerPixel, int channel, int len, const char *r_fileName, const char *n_fileName, vector<struct pixel> &v);




struct pixel{
    int x, y;
    int r, g, b;
};





int main()
{
    vector<struct pixel> v;
    int height = 512;
    int width = 512;
    int BytesPerPixel = 3;
    int len = 5;
    int cc = 1;
    int ss = 100;
    
    
    
    for(int channel = 0; channel <  BytesPerPixel; channel ++)
    {
        
        if(channel == 0)
        {
            unlinerfilter(height, width, BytesPerPixel, channel, len, "Lena_mixed.raw", "Lena_red_nonlinear.raw", v);
            BilateralFilter(height, width, BytesPerPixel, channel, len, cc, ss, "Lena_red_nonlinear.raw", "Lena_red_bilateral.raw", v);
        }
        
        if(channel == 1)
        {
            unlinerfilter(height, width, BytesPerPixel, channel, len, "Lena_red_bilateral.raw", "Lena_green_nonlinear.raw", v);
            BilateralFilter(height, width, BytesPerPixel, channel, len, cc, ss, "Lena_green_nonlinear.raw", "Lena_green_bilateral.raw", v);

        }
    
        if(channel == 2)
        {
            unlinerfilter(height, width, BytesPerPixel, channel, len, "Lena_green_bilateral.raw", "Lena_blue_nonlinear.raw", v);
            BilateralFilter(height, width, BytesPerPixel, channel, len, cc, ss, "Lena_blue_nonlinear.raw", "Lena_blue_bilateral.raw", v);
            
        }

    
    
    }

}





void enlarge(int height, int width, int BytesPerPixel, int len, const char *r_fileName, vector<struct pixel> &v)
{
    
    
    v.clear();// release the vector
    
    
    unsigned char le_Data[height][width][BytesPerPixel];
    //const char *fName[3] = {"data1.txt", "data2.txt", "data3.txt"};
    //int lumin = 256;
    int n = (len - 1) / 2;
    FILE *file;
    vector<struct pixel> v0;
    struct pixel p0, p1;
    
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    fread(le_Data, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);
    
    
    ///////////////store in the struct array from g_Data////////////////////////////////
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p0.x = i;
            p0.y = j;
            p0.r = le_Data[i][j][0];
            p0.g = le_Data[i][j][1];
            p0.b = le_Data[i][j][2];
            v0.push_back(p0);
        }
    }
    
    
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
    unsigned char le1_Data[height + 2 * n][width][BytesPerPixel];
    
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                le1_Data[i][j][k] = le_Data[n-i][j][k];
            }
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                le1_Data[i + n][j][k] = le_Data[i][j][k];
            }
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                le1_Data[height - 1 + 2 * n - i][j][k] = le_Data[height - 1 - n + i][j][k];
            }
        }
    }
    
    
    
    
    
    ///////////////////////////copy in s2_Data from s1_Data////////////////////////
    
    unsigned char le2_Data[height + 2 * n][width + 2 * n][BytesPerPixel];
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                le2_Data[i][j][k] = le1_Data[i][n - j][k];
            }
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                le2_Data[i][j + n][k] = le1_Data[i][j][k];
            }
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < BytesPerPixel; k++)
            {
                le2_Data[i][width - 1 + 2 * n - j][k] = le1_Data[i][width - 1 - n + j][k];
            }
        }
    }
    
    //////////////  test //////////////
    
    /*const char *tname = "text.raw";
     if (!(file = fopen(tname,"wb")))
     {
     cout << "Cannot open file: " << tname << endl;
     exit(1);
     }
     fwrite(le2_Data, sizeof(unsigned char), (height + 2 * n) * (width + 2 * n) * BytesPerPixel, file);
     fclose(file);*/
    
    
    /////////////// pass new data in the vector ////////////////
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width + 2 * n; j++)
        {
            p1.x = i;
            p1.y = j;
            p1.r = le2_Data[i][j][0];
            p1.g = le2_Data[i][j][1];
            p1.b = le2_Data[i][j][2];
            v.push_back(p1);
            
        }
    }
    
    
}




void BilateralFilter(int height, int width, int BytesPerPixel, int channel, int len, int cc, int ss, const char *r_fileName, const char *n_fileName, vector<struct pixel> &v)
{
    enlarge(height, width, BytesPerPixel, len, r_fileName, v);
    
    
    int wsize = len * len;
    int n = (len - 1) / 2;
    vector<int> v1;
    int temp;
    unsigned char a[height + 2 * n][width + 2 * n][BytesPerPixel];
    unsigned char out[height][width][BytesPerPixel];
    FILE *file;
    struct pixel p1;
    
    
    
    ///////// vector transfer to an 3D array /////////
    
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < height + 2 * n; j++)
        {
            a[i][j][0] = v.at(i * (height + 2 * n) + j).r;
            a[i][j][1] = v.at(i * (height + 2 * n) + j).g;
            a[i][j][2] = v.at(i * (height + 2 * n) + j).b;
        }
    }
    
    
     v.clear();// release the vector
    
    
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
                    
                    
    
    
    /////////// output the image /////////////////
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(out, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);
    
    
    /////////// pass data from array to a vector /////////
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p1.x = i;
            p1.y = j;
            p1.r = out[i][j][0];
            p1.g = out[i][j][1];
            p1.b = out[i][j][2];
            v.push_back(p1);
            
        }
    }
    
                    
                    
}



//////////////////////  using unliner filter ////////////////////


void unlinerfilter(int height, int width, int BytesPerPixel, int channel, int len, const char *r_fileName, const char *n_fileName, vector<struct pixel> &v)
{
    
    enlarge(height, width, BytesPerPixel, len, r_fileName, v);
    
    
    int wsize = len * len;
    int n = (len - 1) / 2;
    vector<int> v1;
    int temp;
    unsigned char a[height + 2 * n][width + 2 * n][BytesPerPixel];
    unsigned char out[height][width][BytesPerPixel];
    FILE *file;
    struct pixel p1;
    
    
    ///////// vector transfer to an 3D array /////////
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < height + 2 * n; j++)
        {
            a[i][j][0] = v.at(i * (height + 2 * n) + j).r;
            a[i][j][1] = v.at(i * (height + 2 * n) + j).g;
            a[i][j][2] = v.at(i * (height + 2 * n) + j).b;
        }
    }
    
    
    
    v.clear();// release the vector
    
    
    //accroding analyse, using non-linear filter for Red channel//
    
    
    for(int m = 0; m < height; m++)
    {
        for(int f = 0; f < width; f++)
        {
            
            /////copy pixels in structure vector/////////
            
            for(int i = m; i < m + len; i++)
            {
                for(int j = f; j < f + len; j++)
                {
                    temp = a[i][j][channel];
                    v1.push_back(temp);
                }
            }
            
            
            /////////sort the pixels accroding R /////////
            
            
            sort(v1.begin(), v1.end());
            
            
            /// decide which channel and chose the middle one //
            
            if(channel == 0)
            {
                out[m][f][channel] = v1.at(int(wsize / 2));
                out[m][f][1] = a[m + n][f + n][1];
                out[m][f][2] = a[m + n][f + n][2];
            }
            else if(channel == 1)
            {
                out[m][f][channel] = v1.at(int(wsize / 2));
                out[m][f][0] = a[m + n][f + n][0];
                out[m][f][2] = a[m + n][f + n][2];
            }
            else if(channel == 2)
            {
                out[m][f][channel] = v1.at(int(wsize / 2));
                out[m][f][0] = a[m + n][f + n][0];
                out[m][f][1] = a[m + n][f + n][1];
            }
            
            ///////////  clear the int vector /////////
            
            v1.clear();
            
        }
    }
    
    
    /////////// output the image /////////////////
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(out, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);
    
    
    /////////// pass data from array to a vector /////////
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p1.x = i;
            p1.y = j;
            p1.r = out[i][j][0];
            p1.g = out[i][j][1];
            p1.b = out[i][j][2];
            v.push_back(p1);
        }
    }
    
}

