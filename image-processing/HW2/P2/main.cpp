#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <unordered_set>
#include <array>
using namespace std;




void readFile(const char *r_fileName, vector<struct graypixel> &v);
void changeToBinary(vector<struct graypixel> &v, vector<struct graypixel> &v1, vector<struct graypixel> &v2);
void writeFile(const char *n_fileName, vector<struct graypixel> &v1);
double find_max(vector<struct graypixel> &v, int flag);
double find_min(vector<struct graypixel> &v, int flag);
void normalization(int l, vector<struct graypixel> &v, int flag);
void shrinking(vector<struct graypixel> &v1);
void tableNumber(vector<double> &vec);
void change(vector<struct graypixel> &v1);
//void binary(vector<struct graypixel> &v, vector<struct graypixel> &v1);
//void enlarge(vector<struct graypixel> &v);
int totalNumber(vector<struct graypixel> &v1);
int countDots(vector<struct graypixel> &v1);
void histogram(vector<struct graypixel> &v1);
void thinning(vector<struct graypixel> &v1);
void deleteIsolatedDots(vector<struct graypixel> &v1);
void connectRidges(vector<struct graypixel> &v1, vector<struct graypixel> &v2);
void colorWriteFile(const char *n_fileName, vector<struct colorpixel> &v3);
void determinePoints(vector<struct graypixel> &v1,vector<struct graypixel> &v2, vector<struct colorpixel> &v3);
void postConnection(vector<struct graypixel> &v1);




struct graypixel{
    int x, y;
    unsigned char gray;
    double d_gray;
};

struct colorpixel{
    unsigned char r, g, b;
    double d_r, d_g, d_b;
};


int height = 374;
int width = 388;
int T = 185;
int lumin = 255;
int flag_char = 1;
int flag_double = 0;
int len = 5;
int n = (len - 1)/2;



int main()
{
    vector<struct graypixel> v;
    vector<struct graypixel> v1;
    vector<struct graypixel> v2;
    vector<struct colorpixel> v3;
    
    
    
    const char *r_fileName = "fingerprint_good.raw";
    const char *r1_fileName = "fingerprint_bad.raw";
    const char *n_fileName = "fingerprint_binary.raw";
    const char *n1_fileName = "fingerprint_binary1.raw";
    const char *shrink1_fileName = "fingerprint_shrink1.raw";
    const char *thinning_fileName = "fingerprint_thinning.raw";
    const char *color_fileName = "fingerprint_color.raw";
    
    const char *ffff = "fingerprint_bi.raw";
    
    
    readFile(r1_fileName, v);
    changeToBinary(v, v1, v2);
    normalization(1, v1, flag_char);
    normalization(1, v2, flag_char);
    change(v1);
    //deleteIsolatedDots(v1);
    //histogram(v1);
    
    /*for(int i = 0; i < 2; i++)
    {
        shrinking(v1);
        //thinning(v1);
    }*/
    
    deleteIsolatedDots(v1);
    for(int i = 0; i < 100; i++)
    {
        //shrinking(v1);
        thinning(v1);
    }

    //histogram(v1);
    for(int i = 0; i < 3; i++)
    {
        
        connectRidges(v1, v2);
    }
    
    

    //postConnection(v1);
    //normalization(255, v1, flag_double);
    //normalization(255, v2, flag_double);
    //int sum = totalNumber(v1);
    //cout<< sum << endl;
    //writeFile(thinning_fileName, v1);
    //writeFile(ffff, v2);
    
    determinePoints(v1,v2, v3);
    
    colorWriteFile(color_fileName, v3);
    
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



void changeToBinary(vector<struct graypixel> &v, vector<struct graypixel> &v1, vector<struct graypixel> &v2)
{
    graypixel p;
    
    for(int i = 0; i < v.size(); i++)
    {
        if(v.at(i).gray <= T && v.at(i).gray >= 0)
        {
            p.gray = 0;
            v1.push_back(p);
            v2.push_back(p);
        }
        else if(v.at(i).gray > T && v.at(i).gray <= 255)
        {
            p.gray = 255;
            v1.push_back(p);
            v2.push_back(p);
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


void shrinking(vector<struct graypixel> &v1)
{
    int i, j;
    double f[height][width];
    double m[height][width];
    double output[height][width];
    vector<double> vec;
    
    tableNumber(vec);
    array<double, 58> myArray = {32, 128, 4, 1, 8, 64, 16, 2, 40, 96, 192, 144, 20, 6, 3, 9, 41, 224, 148, 7, 200, 73, 112, 42, 104, 208, 22, 11, 201, 116, 232, 105, 240, 212, 150, 23, 15, 43, 233, 244, 151, 47, 107, 248, 214, 31, 235, 111, 252, 249, 246, 215, 159, 63, 239, 253, 247, 191};
    
    unordered_set<double> mySet;
    mySet.insert(myArray.begin(), myArray.end());
    
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            f[i][j] = v1.at(i * width + j).d_gray;
            //cout << v1.at(i * width + j).d_gray << endl;
        }
    }
    
    
    
    
    /////// stage one /////////////////
    
    for(i = 1; i < height - 1; i++)
    {
        for(j = 1; j < width - 1; j++)
        {
            if(f[i][j] == (double)0)
            {
                m[i][j] = (double)0;
                //count1++;
            }
            else if(f[i][j] == (double)1)
            {
                
                
                ////  stage one ///////
                
                
                double a[8] = {0};
                double s = 0;
                
                a[0] = f[i - 1][j - 1];
                a[1] = f[i - 1][j];
                a[2] = f[i - 1][j + 1];
                a[3] = f[i][j - 1];
                a[4] = f[i][j + 1];
                a[5] = f[i + 1][j - 1];
                a[6] = f[i + 1][j];
                a[7] = f[i + 1][j + 1];
                
                s = a[0] * 128 + a[1] * 64 + a[2] * 32 + a[3] * 16 + a[4] * 8 + a[5] * 4 + a[6] * 2 + a[7] * 1;
                
                unordered_set<double>::const_iterator got = mySet.find(s);
                
                if(!(got == mySet.end()))
                {
                    m[i][j] = (double)1;
                }
            }
        }
    }
    
    
    
    
                /////stage two ///////
    unordered_set<double> mySet1;

    for(i = 0; i < vec.size(); i++)
    {
        mySet1.insert(vec.at(i));
    }



    for(i = 1; i < height - 1; i++)
    {
        for(j = 1; j < width - 1; j++)
        {
            
            if(m[i][j] == (double)0)
            {
                output[i][j] = f[i][j];
            }
            else if(m[i][j] == (double)1)
            {
                double b[8] = {0};
                double s1 = 0;
                    
                b[0] = m[i - 1][j - 1];
                b[1] = m[i - 1][j];
                b[2] = m[i - 1][j + 1];
                b[3] = m[i][j - 1];
                b[4] = m[i][j + 1];
                b[5] = m[i + 1][j - 1];
                b[6] = m[i + 1][j];
                b[7] = m[i + 1][j + 1];
                    
                s1 = b[0] * 128 + b[1] * 64 + b[2] * 32 + b[3] * 16 + b[4] * 8 + b[5] * 4 + b[6] * 2 + b[7] * 1;
                    
                unordered_set<double>::const_iterator got1 = mySet1.find(s1);
                
                if(got1 == mySet.end())
                {
                    output[i][j] = (double)0;
                    
                    
                }
                else
                {
                    output[i][j] = f[i][j];
                }
            }
                
        }
    }

    //cout << count1 << endl;
    //cout << count2 << endl;
    //cout<< count3 << endl;
    
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            v1.at(i * width + j).d_gray = output[i][j];
        }
    }
    
}


void tableNumber(vector<double> &vec)
{
    double a[110][8] = {{0, 0, 1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0},
                    {0,0,0,0,0,0,1,0}, {0,0,0,0,1,0,0,0},
        {0,0,1,0,1,0,0,0}, {0,1,1,0,0,0,0,0}, {1,1,0,0,0,0,0,0}, {1,0,0,1,0,0,0,0},
        {0,0,0,1,0,1,0,0}, {0,0,0,0,0,1,1,0}, {0,0,0,0,0,0,1,1}, {0,0,0,0,1,0,0,1},
        {0,1,1,1,0,0,0,0}, {1,1,0,0,1,0,0,0}, {0,1,0,0,1,0,0,1}, {0,0,1,0,1,0,1,0},
        {0,1,1,0,1,1,0,0}, {0,1,1,0,0,1,0,0}, {0,0,1,0,1,1,0,0}, {1,1,0,1,0,0,0,1},
        {1,0,0,1,0,0,0,1}, {1,1,0,0,0,0,0,1}, {0,0,1,1,0,1,1,0}, {0,0,1,1,0,1,0,0},
        {0,0,1,0,0,1,1,0}, {1,0,0,0,1,0,1,1}, {1,0,0,0,0,0,1,1}, {1,0,0,0,1,0,0,1},
        {1,1,1,1,1,1,1,1}, {1,1,0,1,0,0,0,0}, {1,1,0,1,1,1,0,0}, {0,1,0,1,1,0,0,0},
        {0,1,1,1,1,0,0,1}, {0,1,0,1,1,0,0,0}, {0,0,1,1,1,0,1,1}, {0,0,0,1,1,0,1,0},
        {1,0,0,1,1,1,1,0}, {0,0,0,1,1,0,1,0}, {1,1,1,1,0,0,1,0}, {0,1,0,1,0,0,1,0},
        {0,1,0,1,0,1,1,1}, {0,1,0,1,0,0,1,0}, {0,1,0,0,1,1,1,1}, {0,1,0,0,1,0,1,0},// 10
        {1,1,1,0,1,0,1,0}, {0,1,0,0,1,0,1,0}, {1,1,1,1,1,1,1,1}, {1,0,1,0,0,1,1,1},
        {1,1,1,1,1,0,1,1}, {1,0,1,0,0,0,1,1}, {1,1,1,1,1,1,0,1}, {1,0,1,0,0,1,0,1},
        {1,1,1,1,1,1,1,0}, {1,0,1,0,0,1,1,0}, {1,1,1,1,1,1,0,0}, {1,0,1,0,0,1,0,0},
        {1,1,1,1,1,0,1,0}, {1,0,1,0,0,0,1,0}, {1,1,1,1,1,0,0,1}, {1,0,1,0,0,0,0,1},
        {1,1,1,1,1,1,1,1}, {1,0,1,0,1,1,0,1}, {1,1,1,1,1,1,1,0}, {1,0,1,0,1,1,0,0},
        {1,1,1,1,0,1,1,1}, {1,0,1,0,0,1,0,1}, {1,1,0,1,1,1,1,1}, {1,0,0,0,1,1,0,1},
        {1,1,0,1,0,1,1,1}, {1,0,0,0,0,1,0,1}, {1,1,0,1,1,1,1,0}, {1,0,0,0,1,1,0,0},
        {1,1,1,1,0,1,1,0}, {1,0,1,0,0,1,0,0}, {1,1,1,1,1,1,1,1}, {1,1,1,0,0,1,0,1},///
        {1,1,0,1,1,1,1,1}, {1,1,0,0,0,1,0,1}, {1,0,1,1,1,1,1,1}, {1,0,1,0,0,1,0,1},
        {0,1,1,1,1,1,1,1}, {0,1,1,0,0,1,0,1}, {0,0,1,1,1,1,1,1}, {0,0,1,0,0,1,0,1},
        {0,1,0,1,1,1,1,1}, {0,1,0,0,0,1,0,1}, {1,0,0,1,1,1,1,1}, {1,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1}, {1,0,1,1,0,1,0,1}, {0,1,1,1,1,1,1,1}, {0,0,1,1,0,1,0,1},//
        {1,1,1,0,1,1,1,1}, {1,0,1,0,0,1,0,1}, {1,1,1,1,1,0,1,1}, {1,0,1,1,0,0,0,1},
        {1,1,1,0,1,0,1,1}, {1,0,1,0,0,0,0,1}, {0,1,1,1,1,0,1,1}, {0,0,1,1,0,0,0,1},
        {0,1,1,0,1,1,1,1}, {0,0,1,0,0,1,0,1}, {1,1,0,0,1,1,0,1}, {0,1,0,0,1,1,0,0},
        {0,1,1,1,0,1,0,1}, {0,1,0,1,0,0,0,1}, {1,0,1,1,0,0,1,1}, {0,0,1,1,0,0,1,0},
        {1,0,1,0,1,1,1,0}, {1,0,0,0,1,0,1,0}};
   
    
    
    for(int i = 0; i < 110; i++)
    {
        double sum = 0;
        for(int j = 7; j >= 0; j--)
        {
            sum += a[i][7 - j] * pow(2, j);
        }
        vec.push_back(sum);
        //cout << sum << ", ";
    }
    //cout << endl;
}



void change(vector<struct graypixel> &v1)
{
    for(int i = 0; i < v1.size(); i++)
    {
        if(v1.at(i).d_gray == 0)
        {
            v1.at(i).d_gray = 1;
        }
        else if(v1.at(i).d_gray == 1)
        {
            v1.at(i).d_gray = 0;
        }
    }
}



int totalNumber(vector<struct graypixel> &v1)
{
    int count = 0;
    
    for(int i = 0; i < v1.size(); i++)
    {
        if(v1.at(i).gray == 255)
        {
            count++;
        }
    }
    return count;
}



void histogram(vector<struct graypixel> &v1)
{
    int count_dots = 0;
    int count_short = 0;
    int count_long = 0;
    
    
    //// isolated dots ///////
    
    for(int i = 0; i < 1; i++)
    {
        shrinking(v1);
    }
    count_dots = countDots(v1);
    
    //// short ridges //////
    
    for(int i = 0; i < 4; i++)
    {
        shrinking(v1);
    }
    count_short = countDots(v1) - count_dots;
    
    
    ///// long ridges ///////
    
    for(int i = 0; i < 50; i++)
    {
        shrinking(v1);
    }
    count_long = countDots(v1) - count_dots - count_short;

    cout<< count_dots << endl;
    cout<< count_short << endl;
    cout<< count_long << endl;
    
}

int countDots(vector<struct graypixel> &v1)
{
    double f[height][width];
    int count = 0;
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            f[i][j] = v1.at(i * width + j).d_gray;
        }
    }
    
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            double a[9] = {0};
            double sum = 0;
            a[0] = f[i - 1][j - 1];
            a[1] = f[i - 1][j];
            a[2] = f[i - 1][j + 1];
            a[3] = f[i][j - 1];
            a[4] = f[i][j];
            a[5] = f[i][j + 1];
            a[6] = f[i + 1][j - 1];
            a[7] = f[i + 1][j];
            a[8] = f[i + 1][j + 1];
            
            sum = a[0] * pow(2, 8) + a[1] * pow(2, 7) + a[2] * pow(2, 6) + a[3] * pow(2, 5) + a[4] * pow(2, 4) + a[5] * pow(2, 3) + a[6] * pow(2, 2) + a[7] * pow(2, 1) + a[8] * pow(2, 0);
            
            
            if(sum == 16)
            {
                count++;
            }
        }
    }

    return count;
}



void thinning(vector<struct graypixel> &v1)
{
    int i, j;
    double f[height][width];
    double m[height][width];
    double output[height][width];
    vector<double> vec;
    
    tableNumber(vec);
    
    array<double, 46> myArray = {72, 80, 18, 10, 41, 224, 148, 7, 200, 73, 112, 42, 104, 208, 22, 11, 201, 116, 232, 105, 240, 212, 150, 23, 15, 43, 233, 244, 151, 47, 107, 248, 214, 31, 235, 111, 252, 249, 246, 215, 159, 63, 239, 253, 247, 191};
    
    unordered_set<double> mySet;
    mySet.insert(myArray.begin(), myArray.end());

    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            f[i][j] = v1.at(i * width + j).d_gray;
        }
    }
    
    
    
    
    /////// stage one /////////////////
    
    for(i = 1; i < height - 1; i++)
    {
        for(j = 1; j < width - 1; j++)
        {
            if(f[i][j] == 0)
            {
                m[i][j] = 0;
                //count1++;
            }
            else if(f[i][j] == 1)
            {
                
                
                ////  stage one ///////
                
                
                double a[8] = {0};
                double s = 0;
                
                a[0] = f[i - 1][j - 1];
                a[1] = f[i - 1][j];
                a[2] = f[i - 1][j + 1];
                a[3] = f[i][j - 1];
                a[4] = f[i][j + 1];
                a[5] = f[i + 1][j - 1];
                a[6] = f[i + 1][j];
                a[7] = f[i + 1][j + 1];
                
                s = a[0] * pow(2, 7) + a[1] * pow(2, 6) + a[2] * pow(2, 5) + a[3] * pow(2, 4) + a[4] * pow(2, 3) + a[5] * pow(2, 2) + a[6] * pow(2, 1) + a[7] * pow(2, 0);
                
                unordered_set<double>::const_iterator got = mySet.find(s);
                
                if(!(got == mySet.end()))
                {
                    m[i][j] = 1;
                }
                
            }
        }
    }

    /////stage two ///////
    
    unordered_set<double> mySet1;
    
    for(i = 0; i < vec.size(); i++)
    {
        mySet1.insert(vec.at(i));
    }

    
    for(i = 1; i < height - 1; i++)
    {
        for(j = 1; j < width - 1; j++)
        {
            
            if(m[i][j] == 0)
            {
                output[i][j] = f[i][j];
            }
            else if(m[i][j] == 1)
            {
                double b[8] = {0};
                double s1 = 0;
                
                b[0] = m[i - 1][j - 1];
                b[1] = m[i - 1][j];
                b[2] = m[i - 1][j + 1];
                b[3] = m[i][j - 1];
                b[4] = m[i][j + 1];
                b[5] = m[i + 1][j - 1];
                b[6] = m[i + 1][j];
                b[7] = m[i + 1][j + 1];
                
                s1 = b[0] * pow(2, 7) + b[1] * pow(2, 6) + b[2] * pow(2, 5) + b[3] * pow(2, 4) + b[4] * pow(2, 3) + b[5] * pow(2, 2) + b[6] * pow(2, 1) + b[7] * pow(2, 0);
                
                
                unordered_set<double>::const_iterator got1 = mySet1.find (s1);
                
                if(got1 == mySet.end())
                {
                    output[i][j] = (double)0;
                    
                    
                }
                else
                {
                    output[i][j] = f[i][j];
                }

                
            }
            
            
        }
    }

    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            v1.at(i * width + j).d_gray = output[i][j];
        }
    }

    
}


void deleteIsolatedDots(vector<struct graypixel> &v1)
{
    
    /*for(int i = 0; i < 2; i++)
    {
        shrinking(v1);
    }*/
    
    double f[height][width];
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            f[i][j] = v1.at(i * width + j).d_gray;
        }
    }
    
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            double a[9] = {0};
            double sum = 0;
            a[0] = f[i - 1][j - 1];
            a[1] = f[i - 1][j];
            a[2] = f[i - 1][j + 1];
            a[3] = f[i][j - 1];
            a[4] = f[i][j];
            a[5] = f[i][j + 1];
            a[6] = f[i + 1][j - 1];
            a[7] = f[i + 1][j];
            a[8] = f[i + 1][j + 1];
            
            sum = a[0] * pow(2, 8) + a[1] * pow(2, 7) + a[2] * pow(2, 6) + a[3] * pow(2, 5) + a[4] * pow(2, 4) + a[5] * pow(2, 3) + a[6] * pow(2, 2) + a[7] * pow(2, 1) + a[8] * pow(2, 0);
            
            
            if(sum == 16)
            {
                f[i][j] = 0;
            }
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            v1.at(i * width + j).d_gray = f[i][j];
        }
    }

}




void connectRidges(vector<struct graypixel> &v1, vector<struct graypixel> &v2)
{
    
    int i, j;
    double f[height][width];
    double m[height][width];
    double output[height][width];
    
    
    //double myArray[8] = {8, 32, 64, 128, 16, 4, 2, 1};
    
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            f[i][j] = v1.at(i * width + j).d_gray;
            m[i][j] = v1.at(i * width + j).d_gray;
            output[i][j] = v2.at(i * width + j).d_gray;
        }
    }
    
    
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            double a[8] = {0};
            double s = 0;
            
            if(f[i][j] == 1)
            {
            
            a[0] = f[i - 1][j - 1];
            a[1] = f[i - 1][j];
            a[2] = f[i - 1][j + 1];
            a[3] = f[i][j - 1];
            a[4] = f[i][j + 1];
            a[5] = f[i + 1][j - 1];
            a[6] = f[i + 1][j];
            a[7] = f[i + 1][j + 1];
            
            s = a[0] * 128 + a[1] * 64 + a[2] * 32 + a[3] * 16 + a[4] * 8 + a[5] * 4 + a[6] * 2 + a[7] * 1;
            
            if(s == 8)
            {
                output[i][j - 1] = 0;
                output[i - 1][j - 1] = 0;
                output[i - 1][j] = 0;
                output[i - 1][j + 1] = 0;
                output[i + 1][j - 1] = 0;
                output[i + 1][j] = 0;
                output[i + 1][j + 1] = 0;
                m[i][j - 1] = 1;
            }
            else if(s == 32)
            {
                output[i + 1][j - 1] = 0;
                output[i - 1][j] = 0;
                output[i][j - 1] = 0;
                output[i][j + 1] = 0;
                output[i + 1][j] = 0;
                m[i + 1][j - 1] = 1;
            }
            else if(s == 64)
            {
                output[i + 1][j] = 0;
                output[i - 1][j - 1] = 0;
                output[i - 1][j + 1] = 0;
                output[i][j - 1] = 0;
                output[i][j + 1] = 0;
                output[i + 1][j - 1] = 0;
                output[i + 1][j + 1] = 0;
                m[i + 1][j] = 1;
            }
            else if(s == 128)
            {
                output[i + 1][j + 1] = 0;
                output[i - 1][j] = 0;
                output[i][j - 1] = 0;
                output[i][j + 1] = 0;
                output[i + 1][j] = 0;
                m[i + 1][j + 1] = 1;
            }
            else if(s == 16)
            {
                output[i][j + 1] = 0;
                output[i - 1][j - 1] = 0;
                output[i - 1][j] = 0;
                output[i - 1][j + 1] = 0;
                output[i + 1][j - 1] = 0;
                output[i + 1][j] = 0;
                output[i + 1][j + 1] = 0;
                m[i][j + 1] = 1;
            }
            else if(s == 4)
            {
                output[i - 1][j + 1] = 0;
                output[i - 1][j] = 0;
                output[i][j - 1] = 0;
                output[i][j + 1] = 0;
                output[i + 1][j] = 0;
                m[i - 1][j + 1] = 1;
            }
            else if(s == 2)
            {
                output[i - 1][j] = 0;
                output[i - 1][j - 1] = 0;
                output[i - 1][j + 1] = 0;
                output[i][j - 1] = 0;
                output[i][j + 1] = 0;
                output[i + 1][j - 1] = 0;
                output[i + 1][j + 1] = 0;
                m[i - 1][j] = 1;
            }
            else if(s == 1)
            {
                output[i - 1][j - 1] = 0;
                output[i - 1][j] = 0;
                output[i][j - 1] = 0;
                output[i][j + 1] = 0;
                output[i + 1][j] = 0;
                m[i - 1][j - 1] = 1;
            }
            }
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            v2.at(i * width + j).d_gray = output[i][j];
            v1.at(i * width + j).d_gray = m[i][j];
        }
    }
}



void determinePoints(vector<struct graypixel> &v1, vector<struct graypixel> &v2, vector<struct colorpixel> &v3)
{
    
    int i, j;
    double f[height][width];
    double color[height][width][3];
    double color1[height][width][3];
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            f[i][j] = v1.at(i * width + j).d_gray;
            color[i][j][0] = v1.at(i * width + j).d_gray;
            color[i][j][1] = v1.at(i * width + j).d_gray;
            color[i][j][2] = v1.at(i * width + j).d_gray;
            color1[i][j][0] = v2.at(i * width + j).d_gray;
            color1[i][j][1] = v2.at(i * width + j).d_gray;
            color1[i][j][2] = v2.at(i * width + j).d_gray;
        }
        
    }
    
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            
            if(f[i][j] == 1)
            {
                
                double a[8] = {0};
                double s = 0;
                
                a[0] = f[i - 1][j - 1];
                a[1] = f[i - 1][j];
                a[2] = f[i - 1][j + 1];
                a[3] = f[i][j + 1];
                a[4] = f[i + 1][j + 1];
                a[5] = f[i + 1][j];
                a[6] = f[i + 1][j - 1];
                a[7] = f[i][j - 1];
            
                s = (abs(a[0] - a[7]) + abs(a[1] - a[0]) + abs(a[2] - a[1]) + abs(a[3] - a[2]) + abs(a[4] - a[3]) + abs(a[5] - a[4]) + abs(a[6] - a[5]) + abs(a[7] - a[6])) / 2;
                
                if(s == 1)
                {
                    color[i][j][0] = 1;
                    color[i][j][1] = 0;
                    color[i][j][2] = 0;
                    color1[i][j][0] = 1;
                    color1[i][j][1] = 0;
                    color1[i][j][2] = 0;
                }
                else if(s == 3)
                {
                    color[i][j][0] = 0;
                    color[i][j][1] = 0;
                    color[i][j][2] = 1;
                    color1[i][j][0] = 0;
                    color1[i][j][1] = 0;
                    color1[i][j][2] = 1;

                }
            }
        }
    }
    
    
    colorpixel p;
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            p.r = color1[i][j][0] * 255;
            p.g = color1[i][j][1] * 255;
            p.b = color1[i][j][2] * 255;
            v3.push_back(p);
        }
    }
}



void colorWriteFile(const char *n_fileName, vector<struct colorpixel> &v3)
{
    
    FILE *file;
    unsigned char out[height][width][3];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out[i][j][0] = v3.at(i * width + j).r;
            out[i][j][1] = v3.at(i * width + j).g;
            out[i][j][2] = v3.at(i * width + j).b;
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(out, sizeof(unsigned char), width * height * 3, file);
    fclose(file);
}



void postConnection(vector<struct graypixel> &v1)
{
    int i, j;
    double f[height][width];
    double m[height][width];
    double output[height][width];
    
    array<double, 14> myArray = {231, 189, 68, 24, 36, 129, 130, 34, 68, 65, 136, 12, 48, 17};
    unordered_set<double> mySet;
    mySet.insert(myArray.begin(), myArray.end());
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            f[i][j] = v1.at(i * width + j).d_gray;
            m[i][j] = v1.at(i * width + j).d_gray;
            //output[i][j] = v2.at(i * width + j).d_gray;
        }
    }

    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            double a[8] = {0};
            double s = 0;
            
            if(f[i][j] == 0)
            {
                
                a[0] = f[i - 1][j - 1];
                a[1] = f[i - 1][j];
                a[2] = f[i - 1][j + 1];
                a[3] = f[i][j - 1];
                a[4] = f[i][j + 1];
                a[5] = f[i + 1][j - 1];
                a[6] = f[i + 1][j];
                a[7] = f[i + 1][j + 1];
                
                s = a[0] * 128 + a[1] * 64 + a[2] * 32 + a[3] * 16 + a[4] * 8 + a[5] * 4 + a[6] * 2 + a[7] * 1;
                
                unordered_set<double>::const_iterator got = mySet.find(s);
                if(!(got == mySet.end()))
                {
                    m[i][j] = 1;
                }
            }
        }
    }
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            v1.at(i * width + j).d_gray = m[i][j];
        }
    }

}



/*void dete(vector<struct colorpixel> &v3)
{
    double f[height][width][3];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            f[i][j][0] = (double)v3.at(i * width + j).r;
            f[i][j][1] = (double)v3.at(i * width + j).g;
            f[i][j][2] = (double)v3.at(i * width + j).b;
        }
    }
    
    
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width- 1; j++)
        {
            if(f[i][j][0] == 255 && f[i][j][2] != 0)
            {
                double a[8] = {0};
                double s = 0;
                
                if(f[i][j] == 1)
                {
                    
                    a[0] = f[i - 1][j - 1];
                    a[1] = f[i - 1][j];
                    a[2] = f[i - 1][j + 1];
                    a[3] = f[i][j - 1];
                    a[4] = f[i][j + 1];
                    a[5] = f[i + 1][j - 1];
                    a[6] = f[i + 1][j];
                    a[7] = f[i + 1][j + 1];
                    
                    s = a[0] * 128 + a[1] * 64 + a[2] * 32 + a[3] * 16 + a[4] * 8 + a[5] * 4 + a[6] * 2 + a[7] * 1;
            }

}*/

/*void binary(vector<struct graypixel> &v, vector<struct graypixel> &v1)
{
    int a[height + 2 * n][width + 2 * n];
    int input[height][width];
    graypixel p;
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            a[i][j] = v.at(i * (width + 2 * n) + j).gray;
        }
    }
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            input[i][j] = a[i + n][j + n];
        }
    }
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            int sum = 0;
            
            for(int k = i; k < i + len; k++)
            {
                for(int m = j; m < j + len; m++)
                {
                    sum += a[k][m];
                }
            }
            
            double t = sum / (len * len);
            
            if(input[i][j] <= t)
            {
                input[i][j] = 255;
            }
            else
            {
                input[i][j] = 0;
            }
        }
    }
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p.gray = input[i][j];
            v1.push_back(p);
        }
    }
}*/




/*void enlarge(vector<struct graypixel> &v)
{
    unsigned char le_Data[height][width];
    unsigned char le1_Data[height + 2 * n][width];
    unsigned char le2_Data[height + 2 * n][width + 2 * n];
    struct graypixel p;
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            le_Data[i][j] = v.at(i * width + j).gray;
        }
    }
    
    v.clear();// release the vector
    
    
    int count[lumin][BytesPerPixel];
     
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
     }
    
    
    ///////////////////copy in le1_Data array////////////////////////////
    
    
    
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
    
    
    /////////////// pass new data in the vector ////////////////
    
    for(int i = 0; i < height + 2 * n; i++)
    {
        for(int j = 0; j < width + 2 * n; j++)
        {
            
            p.gray = le2_Data[i][j];
            v.push_back(p);
        }
    }
}*/














