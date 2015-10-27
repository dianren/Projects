#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;


int find_wsize(double sigma);
void readFile(const char *r_fileName, vector<struct graypixel> &v);
void writeFile(const char *n_fileName, vector<struct graypixel> &v);
void enlarge1(int n, vector<struct graypixel> &v);
double find_max(vector<struct graypixel> &v, int flag);
double find_min(vector<struct graypixel> &v, int flag);
void normalization(int l, vector<struct graypixel> &v, int flag);
void LOG(double sigma, int n, vector<double> &v1);
void process_LOG(int n, vector<struct graypixel> &v, vector<double> &v1, vector<int> &v2);
void histogram(const char *fName, vector<struct graypixel> &v);
void histogram1(const char *fName, vector<struct graypixel> &v, vector<int> &v2);
void enlarge2(int n , vector<int> &v2);
void trimap(int k1, int k2, vector<struct graypixel> &v);
void zero_crossing(int n, vector<struct graypixel> &v);
void writeFile1(const char *n_fileName, vector<int> &v2);


struct graypixel{
    int x, y;
    unsigned char gray;
    double gray1;
    double d_gray;
};


int width = 256;
int height = 256;
const double PI = 3.1415;
int flag_char = 1;
int flag_double = 0;






int main()
{
    int n;
    double sigma = 1.4;
    const char *r_fileName = "elaine.raw";
    const char *r1_fileName = "noisy_elaine.raw";
    const char *LOG_fileName = "elaine_LOG.raw";
    const char *LOG1_fileName = "elaine_LOG1.raw";
    const char *tri_fileName = "elaine_tri.raw";
    vector<struct graypixel> v;
    vector<double>  v1;
    //vector<unsigned char> v3;
    vector<int> v2;
    
    
    
    
    n = find_wsize(sigma);
    //cout<< n << endl;
    readFile(r1_fileName, v);
    enlarge1(n, v);
    LOG(sigma, n, v1);
    process_LOG(n, v, v1, v2);
    //writeFile(LOG1_fileName, v);
    normalization(255, v, flag_double);
    //histogram("his_LOG11.txt",v);
    
    trimap(99, 157, v);
    zero_crossing(1, v);
    writeFile(tri_fileName, v);
}


int find_wsize(double sigma)
{
    int w, n;
    
    for(int i = 0; i < 100; i++)
    {
        if(i > (6 * sqrt(2) * sigma) && (i % 2) == 1)
        {
            w = i;
            break;
        }
    }
    cout << w << endl;
    n = (int)(w / 2);
    
    return n;
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


void writeFile(const char *n_fileName, vector<struct graypixel> &v)
{
    
    FILE *file;
    //int n = 6;
    unsigned char out[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out[i][j] = v.at(i * width + j).gray;
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

void writeFile1(const char *n_fileName, vector<int> &v2)
{
    
    FILE *file;
    //int n = 6;
    unsigned char out[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out[i][j] = v2.at(i * width + j);
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



void enlarge1(int n, vector<struct graypixel> &v)
{
    
    unsigned char a[height][width];
    unsigned char c[height + 2 * n][width + 2 * n];
    unsigned char b[height + 2 * n][width];
    graypixel p;
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            a[i][j] = v.at(i * width + j).gray;
        }
    }
    
    v.clear();
    
    
    ///////////////////////////copy in b from a////////////////////////
    
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            b[i][j] = a[n-i][j];
            
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            b[i + n][j] = a[i][j];
            
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            b[height - 1 + 2 * n - i][j] = a[height - 1 - n + i][j];
            
        }
    }
    
    ///////////////////////////copy in c from b////////////////////////
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            
            
            c[i][j] = b[i][n - j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            c[i][j + n] = b[i][j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            
            
            c[i][width - 1 + 2 * n - j] = b[i][width - 1 - n + j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width + 2 * n; j++)
        {
            p.gray = c[i][j];
            v.push_back(p);
        }
    }
}


void process_LOG(int n, vector<struct graypixel> &v, vector<double> &v1, vector<int> &v2)
{
    
    unsigned char a[height + 2 * n][width + 2 * n];
    double b[2 * n + 1][2 * n + 1];
    double out[height][width];
    int i, j, m, f;
    double sum;
    graypixel p;
    
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            out[i][j] = 0;
        }
    }
    
    for(i = 0; i < 1 + 2 * n; i++)
    {
        for(j = 0; j < 1 + 2 * n; j++)
        {
            b[i][j] = 0;
        }
    }
    
    /////change image vector to array////////
    
    for(i = 0; i < height + 2 * n; i++)
    {
        for(j = 0; j < width + 2 * n; j++)
        {
            a[i][j] = v.at(i * (width + 2 * n) + j).gray;
        }
    }
    
    v.clear();///release the vector
    
    
    ////change LOG vector to array///////
    
    for(i = 0; i < 1 + 2 * n; i++)
    {
        for(j = 0; j < 1 + 2 * n; j++)
        {
            b[i][j] = v1.at(i * (1 + 2 * n) + j);
            //cout << b[i][j] << endl;
        }
    }
    
    v1.clear();
    
    ///// process the LOG array/////////
    
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
            
            p.gray1 = sum;
            v.push_back(p);
        }
    }
    
    //histogram1("h_2222.txt", v, v2);
    
    
    
}


void LOG(double sigma, int n, vector<double> &v1)
{
    int i, j;
    double t, temp;
    
    //cout << n << endl;
    /// process LOG formula ////////
    
    for(i = 0; i < 2 * n + 1; i++)
    {
        for(j = 0; j < 2 * n + 1; j++)
        {
            t = ((n - i) * (n - i) + (n - j) * (n - j)) / (2 * sigma * sigma);
            //cout << t << endl;
            temp = (exp(-t) * (t - 1)) / (PI * pow(sigma, 4));
            //cout << temp << endl;
            v1.push_back(temp);
        }
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
        
        max = v.at(0).gray1;
        
        for(int i = 1; i < height * width; i++)
        {
            if(max < v.at(i).gray1)
            {
                max = v.at(i).gray1;
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
        
        min = v.at(0).gray1;
        
        for(int i = 1; i < height * width; i++)
        {
            if(min > v.at(i).gray1)
            {
                min = v.at(i).gray1;
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
            v.at(i).gray = (unsigned char)(((v.at(i).gray1 - min) * l) / (max - min));
        }
        
    }
    
}


void histogram(const char *fName, vector<struct graypixel> &v)
{
    int count[256] = {0};
    
    
    
    ////////////count the number of pixels in each scale//////////
    
    for(int i = 0; i < height * width; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            
            if(v.at(i).gray == j)
            {
                count[j]++;
            }
        }
        
    }
    
    /////////////write in txt file//////////////////////
    FILE *file;
    
    if((file = fopen(fName, "wb")) != NULL)
    {
        for(int i = 0; i < 256; i++)
        {
            fprintf(file, "%d ", count[i]);
        }
    }
    fclose(file);
    
}



void histogram1(const char *fName, vector<struct graypixel> &v, vector<int> &v2)
{
    double max, min;
    max = find_max(v, flag_double);
    min = find_min(v, flag_double);
    
    //cout << max << " " << min << endl;
    
    int count[(int)max - (int)min + 1];
    
    ///initialize the array /////
    
    for(int j = 0; j < (int)max - (int)min + 1; j++)
    {
        count[j] = 0;
    }
    
    //// change double to int ////
    
    for(int i = 0; i < height * width; i++)
    {
        v2.push_back((int)(v.at(i).gray1));
    }
    
    //int sum = 0;
    
    /// count the number in value range/////
    
    for(int i = 0; i < height * width; i++)
    {
        for(int j = 0; j < (int)max - (int)min + 1; j++)
        {
            if(v2.at(i) == (j + (int)min))
            {
                count[j]++;
            }
        }
    }
    
    
    /*for(int j = 0; j < (int)max - (int)min + 1; j++)
    {
        sum += count[j];
    }
    cout << sum << endl;*/
    
    FILE *file;
    
    if((file = fopen(fName, "wb")) != NULL)
    {
        for(int i = 0; i < (int)max - (int)min + 1; i++)
        {
            fprintf(file, "%d ", count[i]);
        }
    }
    fclose(file);
    
    
}


void trimap(int k1, int k2, vector<struct graypixel> &v)
{
    for(int i = 0; i < height * width; i++)
    {
        if(v.at(i).gray <= k1)
        {
            v.at(i).gray = 64;
        }
        else if(v.at(i).gray > k1 && v.at(i).gray < k2)
        {
            v.at(i).gray = 128;
        }
        else if(v.at(i).gray >= k2)
        {
            v.at(i).gray = 192;
        }
    }
}


void zero_crossing(int n, vector<struct graypixel> &v)
{
    enlarge1(n, v);
    
    int a[height + 2 * n][width + 2 * n];
    //int out[height][width];
    int i, j, m, f;
    int len = 3;
    graypixel p;
    
    for(i = 0; i < height + 2 * n; i++)
    {
        for(j = 0; j < width + 2 * n; j++)
        {
            if(v.at(i * (width + 2 * n) + j).gray == 64)
            {
                a[i][j] = -1;
            }
            else if(v.at(i * (width + 2 * n) + j).gray == 128)
            {
                a[i][j] = 0;
            }
            else if(v.at(i * (width + 2 * n) + j).gray == 192)
            {
                a[i][j] = 1;
            }
            
            //cout << a[i][j] << " ";
        }
    }
    
    v.clear();
    
    
    for(m = 0; m < height; m++)
    {
        for(f = 0; f < width; f++)
        {
            if(a[m + 1][f + 1] == 0)
            {
                for(i = m; i < m + len; i++)
                {
                    for(j = f; j < f + len; j++)
                    {
                        if(a[i][j] * a[i + 2][j + 2] == -1 ||
                           a[i][j + 1] * a[i + 2][j + 1] == -1 ||
                           a[i][j + 2] * a[i + 2][j] == -1 ||
                           a[i + 1][j] * a[i + 1][j + 2] == -1)
                        {
                            //out[m][f] = 255;
                            p.gray = 255;
                        }
                        else
                        {
                            //out[m][f] = 0;
                            p.gray = 0;
                        }
                    }
                }
            }
            else
            {
                //out[m][f] = 0;
                p.gray = 0;
            }
            
            v.push_back(p);
        }
    }
    
}


void enlarge2(int n , vector<int> &v2)
{
    int a[height][width];
    int c[height + 2 * n][width + 2 * n];
    int b[height + 2 * n][width];
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            a[i][j] = v2.at(i * width + j);
        }
    }
    
    v2.clear();
    
    
    ///////////////////////////copy in b from a////////////////////////
    
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            b[i][j] = a[n-i][j];
            
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            b[i + n][j] = a[i][j];
            
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            b[height - 1 + 2 * n - i][j] = a[height - 1 - n + i][j];
            
        }
    }
    
    ///////////////////////////copy in c from b////////////////////////
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            
            
            c[i][j] = b[i][n - j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            
            c[i][j + n] = b[i][j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            
            
            c[i][width - 1 + 2 * n - j] = b[i][width - 1 - n + j];
            
        }
    }
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width + 2 * n; j++)
        {
            v2.push_back(c[i][j]);
        }
    }

}