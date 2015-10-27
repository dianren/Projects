#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;





void readFile_t(const char *r_fileName, vector<struct pixel> &v);
void readFile_c(const char *r_fileName, vector<struct pixel> &v1);
void writeFile(const char *n_fileName, vector<struct pixel> &v);
void enlarge(vector<struct pixel> &v1);
void detectTiffPoints(vector<double> &v2, int wsize, vector<struct point> &point);
void writeFile1(const char *n_fileName, vector<double> &v2);
void convertToGray(vector<struct pixel> &v, vector<double> &v2);
void convertToBinary(vector<double> &v2);
struct lenandhigh calLenAndHigh(vector<struct point> &point);
void detectComPoints(vector<double> &v2, int wsize, vector<struct point> &point1);
double getAngle(int flag, vector<struct point> &point1);
void rotation(int flag1, int flag2, vector<struct pixel> &v1, vector<struct point> &point1);
void scaling(vector<struct pixel> &v1);
void shifting(vector<struct pixel> &v1);
void combine(vector<struct pixel> &v, vector<struct pixel> &v1);






struct pixel
{
    unsigned char rgb[3];
    double d_rgb[3];
    double cmy[3];
    int x;
    int y;
};



struct point
{
    int x;
    int y;
};

struct lenandhigh
{
    int len1;
    int len2;
    int high1;
    int high2;
};



int height_t = 512;
int width_t = 512;
int bytes = 3;
int height_c = 350;
int width_c = 350;
int T = 244;
double PI = 3.1314;



int main()
{
    vector<struct pixel> v;
    vector<struct pixel> v1;
    vector<double> v2;
    vector<double> v3;
    
    vector<struct point> point;
    vector<struct point> point1;
    
    const char *r1_fileName = "Components.raw";
    const char *r_fileName = "Tiffany.raw";
    const char *n_fileName = "Components_512.raw";
    const char *n1_fileName = "Components_rotate.raw";
    const char *n2_fileName = "Components_enlarge.raw";
    /*readFile_t(r_fileName, v);
    convertToGray(v, v2);
    convertToBinary(v2);
    detectTiffPoints(v2, 15, point);
    struct lenandhigh a = calLenAndHigh(point);
    writeFile1(n_fileName, v2);*/
    
    
    readFile_c(r1_fileName, v1);
    enlarge(v1);
    writeFile(n2_fileName, v1);
    convertToGray(v1, v2);
    convertToBinary(v2);
    detectComPoints(v2, 15, point1);
    rotation(1, 2, v1, point1);
    scaling(v1);
    shifting(v1);
    readFile_t(r_fileName, v);
    combine(v, v1);
    writeFile(n1_fileName, v1);
    //writeFile1(n_fileName, v2);
    
    
    //convertToGray(v1, v3);
    //convertToBinary(v3);
    //writeFile1(n_fileName, v3);
    
    return 0;
}










void readFile_t(const char *r_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char input[height_t][width_t][bytes];
    pixel p;
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    
    fread(input, sizeof(unsigned char), width_t * height_t * bytes, file);
    fclose(file);
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = input[i][j][k];
            }
            v.push_back(p);
        }
    }
    
}


void readFile_c(const char *r_fileName, vector<struct pixel> &v1)
{
    
    FILE *file;
    unsigned char input[height_c][width_c][bytes];
    pixel p;
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    
    fread(input, sizeof(unsigned char), width_c * height_c * bytes, file);
    fclose(file);
    
    
    for(int i = 0; i < height_c; i++)
    {
        for(int j = 0; j < width_c; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = input[i][j][k];
            }
            v1.push_back(p);
        }
    }
    
}


void enlarge(vector<struct pixel> &v1)
{
    
    unsigned char input[height_c][width_c][bytes];
    unsigned char output[height_t][width_t][bytes];
    int i, j, k;
    struct pixel p;
    
    for(i = 0; i < height_c; i++)
    {
        for(j = 0; j < width_c; j++)
        {
            for(k = 0; k < bytes; k++)
            {
                input[i][j][k] = v1.at(i * width_c + j).rgb[k];
            }
        }
    }
    
    v1.clear();

    
    for(i = 0; i < height_t; i++)
    {
        for(j = 0; j < width_t; j++)
        {
            for(k = 0; k < bytes; k++)
            {
                output[i][j][k] = 255;
            }
        }
    }
    
    int n1 = (height_t - height_c) / 2;
    int n2 = (width_t - width_c) / 2;
    
    for(i = n1; i < n1 + height_c; i++)
    {
        for(j = n2; j < n2 + width_c; j++)
        {
            for(k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[i - n1][j - n2][k];
            }
        }
    }
    
    
    
    for(i = 0; i < height_t; i++)
    {
        for(j = 0; j < width_t; j++)
        {
            for(k = 0; k < bytes; k++)
            {
                p.rgb[k] = output[i][j][k];
            }
            v1.push_back(p);
        }
    }
}

void writeFile(const char *n_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char output[height_t][width_t][bytes];
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = v.at(i * (width_t) + j).rgb[k];
            }
            
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (width_t) * (height_t) * bytes, file);
    fclose(file);
}


void detectTiffPoints(vector<double> &v2, int wsize, vector<struct point> &point)
{
    unsigned char input[height_t][width_t];
    struct point p;
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
           
            input[i][j] = v2.at(i * width_t + j);
            
        }
    }
    
    int n = (wsize - 1) / 2;
    
    vector<int> v_int;
    
    ////////////  up point ///////////////////
    
    for(int i = n; i < height_t - n; i++)
    {
        for(int j = n; j < width_t - n; j++)
        {
            
            for(int m = i - n; m < i - n + wsize; m++)
            {
                for(int f = j - n; f < j - n + wsize; f++)
                {
                    v_int.push_back(input[m][f]);
                }
            }
            
            int sum1 = 0, sum2 = 0;
            
            for(int g = 0; g < wsize * (n + 1); g++)
            {
                sum1 += v_int.at(g);
            }
            
            for(int g = wsize * (n + 1); g < wsize * wsize; g++)
            {
                sum2 += v_int.at(g);
            }
            
            v_int.clear();
            
            if(sum1 == 0 && sum2 == 255 * wsize * (wsize - n - 1) && input[i + 1][j - n - 1] == 0)
            {
                p.x = i + 1;
                p.y = j - n;
                point.push_back(p);
                cout << p.x << " " << p.y << endl;
            }
            
            if(sum1 == 0 && sum2 == 255 * wsize * (wsize - n - 1) && input[i + 1][j + n + 1] == 0)
            {
                p.x = i + 1;
                p.y = j + n;
                point.push_back(p);
                cout << p.x << " " << p.y << endl;
            }

        }
    }
    
    
    //////////// down point //////////////////////////
    
    
    for(int i = n; i < height_t - n; i++)
    {
        for(int j = n; j < width_t - n; j++)
        {
            
            for(int m = i - n; m < i - n + wsize; m++)
            {
                for(int f = j - n; f < j - n + wsize; f++)
                {
                    v_int.push_back(input[m][f]);
                }
            }
            
            int sum1 = 0, sum2 = 0;
            
            for(int g = 0; g < wsize * (n + 1); g++)
            {
                sum1 += v_int.at(g);
            }
            
            for(int g = wsize * (n + 1); g < wsize * wsize; g++)
            {
                sum2 += v_int.at(g);
            }
            
            v_int.clear();
            
            if(sum1 == 255 * wsize * (wsize - n) && sum2 == 0 && input[i][j - n - 1] == 0)
            {
                p.x = i;
                p.y = j - n;
                point.push_back(p);
                cout << p.x << " " << p.y << endl;
            }
            
            if(sum1 == 255 * wsize * (wsize - n) && sum2 == 0 && input[i][j + n + 1] == 0)
            {
                p.x = i;
                p.y = j + n;
                point.push_back(p);
                cout << p.x << " " << p.y << endl;
            }
            
        }
    }

}


lenandhigh calLenAndHigh(vector<struct point> &point)
{
    struct lenandhigh a;
    
    a.len1 = point.at(1).y - point.at(0).y;
    a.len2 = point.at(3).y - point.at(2).y;
    a.high1 = point.at(4).x - point.at(0).x;
    a.high2 = point.at(6).x - point.at(2).x;
    
    cout << a.len1 << " " << a.len2 << endl;
    cout << a.high1 << " " << a.high2 << endl;
    
    return a;
}


void convertToGray(vector<struct pixel> &v, vector<double> &v2)
{
    unsigned char input[height_t][width_t][bytes];
    unsigned char output[height_t][width_t];
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = v.at(i * width_t + j).rgb[k];
            }
        }
    }
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            output[i][j] = input[i][j][0] * 0.21 + input[i][j][1] * 0.72 + input[i][j][2] * 0.07;
            v2.push_back(output[i][j]);
        }
    }
}


void convertToBinary(vector<double> &v2)
{
    for(int i = 0; i < v2.size(); i++)
    {
        if(v2.at(i) < T)
        {
            v2.at(i) = 0;
        }
        else
            v2.at(i) = 255;
    }
}

void writeFile1(const char *n_fileName, vector<double> &v2)
{
    
    FILE *file;
    unsigned char output[height_t][width_t];
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            
            output[i][j] = v2.at(i * (width_t) + j);
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (width_t) * (height_t), file);
    fclose(file);
}


void detectComPoints(vector<double> &v2, int wsize, vector<struct point> &point1)
{
    unsigned char input[height_t][width_t];
    struct point p;
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            
            input[i][j] = v2.at(i * width_t + j);
            
        }
    }
    
    
    int n = (wsize - 1) / 2;
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = n; j < width_t - n; j++)
        {
            int sum1 = 0, sum2 = 0;
            
            for(int m = j - n; m < j; m++)
            {
                sum1 += input[i][m];
            }
            
            for(int m = j + 1; m < j - n + wsize; m++)
            {
                sum2 += input[i][m];
            }
            
            if(sum1 == 255 * n && input[i][j] == 0 && sum2 == 255 * n)
            {
                p.x = i;
                p.y = j;
                point1.push_back(p);
                cout << p.x << " " << p.y << endl;
            }
        }
    }
    
    
    
    for(int j = 0; j < width_t; j++)
    {
        for(int i = n; i < height_t - n; i++)
        {
            int sum1 = 0, sum2 = 0;
            
            for(int m = i - n; m < i; m++)
            {
                sum1 += input[m][j];
            }
            
            for(int m = i + 1; m < i - n + wsize; m++)
            {
                sum2 += input[m][j];
            }
            
            if(sum1 == 255 * n && input[i][j] == 0 && sum2 == 255 * n)
            {
                p.x = i;
                p.y = j;
                point1.push_back(p);
                cout << p.x << " " << p.y << endl;
            }
            else if(sum1 == 255 * n && input[i][j] == 0 && sum2 == 255 * (n - 1))
            {
                p.x = i;
                p.y = j;
                point1.push_back(p);
                cout << p.x << " " << p.y << endl;
            }
        }
    }

    
    ////////// identify the center point ///////////////
    
    //int len1 = sqrt((point1.at(2).x * point1.at(2).x - point1.at(4).x * point1.at(4).x) + (point1.at(2).y * point1.at(2).y - point1.at(4).y * point1.at(4).y));
    
    p.x = (point1.at(2).x + point1.at(4).x) / 2;
    p.y = (point1.at(2).y + point1.at(4).y) / 2;
    point1.push_back(p);
    cout << p.x << " " << p.y << endl;
    
    p.x = (point1.at(3).x + point1.at(5).x) / 2;
    p.y = (point1.at(3).y + point1.at(5).y) / 2;
    point1.push_back(p);
    cout << p.x << " " << p.y << endl;
    
    int len1 = (int)(sqrt((point1.at(1).x - point1.at(5).x) * (point1.at(1).x - point1.at(5).x) + (point1.at(1).y - point1.at(5).y) * (point1.at(1).y - point1.at(5).y)));
    int height1 = (int)(sqrt((point1.at(1).x - point1.at(3).x) * (point1.at(1).x - point1.at(3).x) + (point1.at(1).y - point1.at(3).y) * (point1.at(1).y - point1.at(3).y)));
    int len2 = (int)(sqrt((point1.at(0).x - point1.at(2).x) * (point1.at(0).x - point1.at(2).x) + (point1.at(0).y - point1.at(2).y) * (point1.at(0).y - point1.at(2).y)));
    int height2 = (int)(sqrt((point1.at(0).x - point1.at(4).x) * (point1.at(0).x - point1.at(4).x) + (point1.at(0).y - point1.at(4).y) * (point1.at(0).y - point1.at(4).y)));
    
    cout << len1 << " " << height1 << endl;
    cout << len2 << " " << height2 << endl;
    
}


double getAngle(int flag, vector<struct point> &point1)
{
    double angle;
    
    if(flag == 1)
    {
        angle = -atan2(point1.at(2).x - point1.at(0).x, point1.at(2).y - point1.at(0).y);
        //double a = sin(angle);
        //cout << angle << " " << a << endl;
    }
    else if(flag == 2)
    {
        angle = atan2(point1.at(5).x - point1.at(1).x, point1.at(1).y - point1.at(5).y);
        //double a = sin(angle);
        //cout << angle << " " << a << endl;
    }
    
    return angle;
}


void rotation(int flag1, int flag2, vector<struct pixel> &v1, vector<struct point> &point1)
{
    unsigned char input[height_t][width_t][bytes];
    unsigned char output[height_t][width_t][bytes];
    double angle1 = getAngle(flag1, point1);
    double angle2 = getAngle(flag2, point1);
    int x1, y1, x, y;
    pixel p;
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = 255;
            }
        }
    }
        
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = v1.at(i * width_t + j).rgb[k];
            }
        }
    }

    v1.clear();
    
    
    /////  scan first rectangle //////////
    
    for(int i = 115; i < 261; i++)
    {
        for(int j = 100; j < 265; j++)
        {
            
            int a, b;
            int i1 = i - 189;
            int j1 = j - 187;
            
            x1 = -(int)(i1 * sin(angle1) + j1 * cos(angle1));
            y1 = -(int)(i1 * cos(angle1) - j1 * sin(angle1));
            y = y1 + 189;
            x = x1 + 187;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
        }
    }
    
    
    ///////// scan second rectangle ///////////
    
    for(int i = 285; i < 380; i++)
    {
        for(int j = 240; j < 375; j++)
        {
            int i1 = i - 333;
            int j1 = j - 308;
            x1 = (int)(i1 * sin(angle2) + j1 * cos(angle2));
            y1 = (int)(i1 * cos(angle2) - j1 * sin(angle2));
            y = y1 + 333;
            x = x1 + 308;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }

        }
    }
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = output[i][j][k];
            }
            v1.push_back(p);
        }
    }
}



void scaling(vector<struct pixel> &v1)
{
    //cout << "111111111";
    //int ori_len1 = 79, ori_height1 = 34;
    //int ori_len2 = 109, ori_height2 = 59;
    //int com_len1 = 117, com_height1 = 51;
    //int com_len2 = 127, com_height2 = 67;
    unsigned char input[height_t][width_t][bytes];
    unsigned char output[height_t][width_t][bytes];
    pixel p;
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = 255;
            }
        }
    }

    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = v1.at(i * width_t + j).rgb[k];
            }
        }
    }
    
    v1.clear();
    
    int y, x;
    
    
    /// eyes scaling /////////////
    
    for(int i = 285; i < 380; i++)
    {
        for(int j = 240; j < 375; j++)
        {
            int i1 = i - 333;
            int j1 = j - 308;
            
            int x1 = (112 * j1) / 85;
            int y1 = (50 * i1) / 38;
            
            y = y1 + 333;
            x = x1 + 308;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
        }
    }

    
    ///// mouth scaling ////////////
    
    for(int i = 115; i < 261; i++)
    {
        for(int j = 100; j < 265; j++)
        {
            
            
            int i1 = i - 189;
            int j1 = j - 187;
            
            int x1 = (129 * j1) / 116;
            int y1 = (65 * i1) / 60;
            
            y = y1 + 189;
            x = x1 + 187;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
        }
    }

    
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = output[i][j][k];
            }
            v1.push_back(p);
        }
    }

}


void shifting(vector<struct pixel> &v1)
{
    unsigned char input[height_t][width_t][bytes];
    unsigned char output[height_t][width_t][bytes];
    pixel p;
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = 255;
            }
        }
    }
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = v1.at(i * width_t + j).rgb[k];
            }
        }
    }
    
    v1.clear();
    
    int x, y;
    ///// eye shift //////////
    
    int a = 333 - 212;
    int b = 308 - 259;
    
    for(int i = 285 - a - 1; i < 380 - a + 1; i++)
    {
        for(int j = 240 - b; j < 375 - b; j++)
        {
            y = i + a;
            x = j + b;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
        }
    }


    ///// mouth shift //////////
    
    int c = 339 - 189 - 1;
    int d = 321 - 187 - 1;
    
    for(int i = 115 + c -2; i < 261 + c + 2; i++)
    {
        for(int j = 100 + d - 3; j < 265 + d + 3; j++)
        {
            y = i - c;
            x = j - d;
            
            for(int k = 0; k < bytes; k++)
            {
                output[i][j][k] = input[y][x][k];
            }
        }
    }

    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = output[i][j][k];
            }
            v1.push_back(p);
        }
    }

}


void combine(vector<struct pixel> &v, vector<struct pixel> &v1)
{
    unsigned char input[height_t][width_t][bytes];
    unsigned char input1[height_t][width_t][bytes];
    pixel p;
   
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = v.at(i * width_t + j).rgb[k];
            }
        }
    }

    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input1[i][j][k] = v1.at(i * width_t + j).rgb[k];
            }
        }
    }

    v.clear();
    v1.clear();
    
    for(int i = 193; i < 231; i++)
    {
        for(int j = 217; j < 300; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = input1[i][j][k];
            }
        }
    }
    
    for(int i = 307; i < 370; i++)
    {
        for(int j = 264; j < 377; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                input[i][j][k] = input1[i][j][k];
            }
        }
    }
    
    
    for(int i = 0; i < height_t; i++)
    {
        for(int j = 0; j < width_t; j++)
        {
            for(int k = 0; k < bytes; k++)
            {
                p.rgb[k] = input[i][j][k];
            }
            v1.push_back(p);
        }
    }
}




