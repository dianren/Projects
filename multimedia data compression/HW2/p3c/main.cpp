#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;




void readFile(const char *r_fileName, vector<struct pixel> &v);
void subtraction(vector<struct pixel> &v);
double getC(int &i);
void DCT(vector<struct pixel> &v);
void matrixC(vector<struct pixel> &v);
void findMatrices();
void report();
void printMatrix(vector<struct pixel> &v);







struct pixel{
    int gray;
    double d;
    int quantizedC;
};



int height = 16;
int width = 16;
int N = 8;
double PI = 3.1413;



int Q50[8][8] = {{16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 62},
    {18, 22, 37, 56, 68, 109, 103, 77},
    {24, 35, 55, 64, 81, 104, 113, 92},
    {49, 64, 78, 87, 103, 121, 120, 101},
    {72, 92, 95, 98, 112, 100, 103, 99}};

int Q10[8][8] = {0};
int Q90[8][8] = {0};









int main()
{
    
    vector<struct pixel> v;
    
    const char *r_fileName = "Lena.raw";
    
    
    findMatrices();
    
    
    
    readFile(r_fileName, v);
    subtraction(v);
    DCT(v);
    matrixC(v);
    
    //report();
    printMatrix(v);
    
}





void readFile(const char *r_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char input[height][width];
    pixel p;
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    
    fread(input, sizeof(unsigned char), width * height, file);
    fclose(file);
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p.gray = input[i][j];
            v.push_back(p);
        }
    }
    
}



void subtraction(vector<struct pixel> &v)
{
    for(int i = 0; i < v.size(); i++)
    {
        v.at(i).gray = v.at(i).gray - 128;
        
        //cout << v.at(i).gray << " " ;
    }
}


double getC(int &i)
{
    double c;
    
    if(i == 0)
    {
        c = 1 / sqrt(2);

    }
    else
    {
        c = 1;
    }
    
    return c;
}







void DCT(vector<struct pixel> &v)
{
    int gray[16][16] = {0};
    double d[16][16] = {0};
    
    
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            gray[i][j] = v.at(i * width + j).gray;
        }
    }
    
   
    
    
    for(int m = 0; m < height; m += 8)
    {
        for(int k = 0; k < width; k += 8)
        {
            
            
            
            for(int i = m; i < m + 8; i++)
            {
                for(int j = k; j < k + 8; j++)
                {
                    
                    double sum = 0;
                    double ci = 0, cj = 0;
                    
                    for(int x = 0; x < 8; x++)
                    {
                        for(int y = 0; y < 8; y++)
                        {
                            
                            double f1 = 0, f2 = 0;
                            
                            
                            f1 = ((2 * x + 1) * i * PI) / (2 * 8);
                            
                            f2 = ((2 * y + 1) * j * PI) / (2 * 8);
                            
                            sum += gray[x][y] * cos(f1) * cos(f2);
                        }
                    }
                    
                    
                    ci = getC(i);
                    cj = getC(j);
                    
                    d[i][j] = (ci * cj * sum) / sqrt(2 * 8);
                    //cout << ci << " " ;
                }
            }
            
            
            
        }
    }
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            v.at(i * width + j).d = d[i][j];
        }
    }

}



void matrixC(vector<struct pixel> &v)
{
    double d[16][16] = {0};
    double c[16][16] = {0};
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            d[i][j] = v.at(i * width + j).d;
        }
    }
    
    for(int m = 0; m < height; m += N)
    {
        for(int k = 0; k < width; k = k + 8)
        {
            
            
            
            for(int i = m; i < m + N; i++)
            {
                for(int j = k; j < k + N; j++)
                {
                    c[i][j] = round(d[i][j] / Q90[i - m][j - k]);
                    
                }
            }
        }
    }
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            v.at(i * width + j).quantizedC = c[i][j];
        }
    }
    
}


void findMatrices()
{
    //int n1 = 10, n2 = 90;
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            Q10[i][j] = (50 * Q50[i][j]) / 10;
        }
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            
            Q90[i][j] = ((100 - 90) * Q50[i][j]) / 50;
        }
    }
}



void printMatrix(vector<struct pixel> &v)
{
    int c[16][16] = {0};
   
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            c[i][j] = v.at(i * width + j).quantizedC;
        }
    }
    
    cout << endl;
    for(int i = 0 ; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl;
    for(int i = 0 ; i < 8; i++)
    {
        for(int j = 8; j < 16; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for(int i = 8 ; i < 16; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for(int i = 8 ; i < 16; i++)
    {
        for(int j = 8; j < 16; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    
}

void report()
{
    cout<< endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << Q10[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl;
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << Q90[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
















