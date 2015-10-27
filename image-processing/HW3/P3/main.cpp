#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;



void readFile(const char *r_fileName, vector<struct pixel> &v);
void writeFile(const char *n_fileName, vector<struct pixel> &v);
void kernel(vector< vector<double> > &vv);
void enlarge(vector<struct pixel> &v, int n);
void filtering(vector<struct pixel> &v, vector< vector<double> > &vv, vector< vector<double> > &vv_double);
void enlarge_double(vector< vector<double> > &vv_double, vector< vector<double> > &vv_double1, int x);
void calAveEnergy(vector< vector<double> > &vv_double1, int x);
void calEnergy(vector< vector<double> > &com_vv_double1, int x);
void readIndex(const char *index_fileName, vector<pixel> &v_int);
void display(vector<pixel> &v_int);




struct pixel{
    unsigned char gray;
};




int height = 450;
int width = 600;
int wsize = 5;
int n = (wsize - 1) /2;



int main()
{
    
    
    ///////////  (a) prat  ///////////////////////////////
    
    /*const char *r_fileName = "Sample12.raw";
    const char *n_fileName = "Sample1_sssssss.raw";
    vector<struct pixel> v;
    vector< vector<double> > vv;
    vector<double> v_double;
    vector< vector<double> > vv_double;
    vector< vector<double> > vv_double1;
    
    readFile(r_fileName, v);
    enlarge(v, n);
    //writeFile(n_fileName, v);
    kernel(vv);
    filtering(v, vv, vv_double);
    enlarge_double(vv_double, vv_double1, 7); ///  wsize = 13
    //cout<< "1111111"<<endl;
    calAveEnergy(vv_double1, 7);*/
    
    
    
    /////////// (b) part /////////////////////////////////////
    
    const char *r1_fileName = "com_2.raw";
    //const char *n1_fileName = "com_1_new.raw";
    //const char *index_fileName = "index.txt";
    
    
    vector<struct pixel> com_v;
    vector< vector<double> > com_vv;
    vector< vector<double> > com_vv_double;
    vector< vector<double> > com_vv_double1;
    vector<pixel> v_int;
    
    
    
    readFile(r1_fileName, com_v);
    enlarge(com_v, n);
    kernel(com_vv);
    filtering(com_v, com_vv, com_vv_double);
    enlarge_double(com_vv_double, com_vv_double1, 20);
    calEnergy(com_vv_double1, 20);
    /*readIndex(index_fileName, v_int);
    display(v_int);
    writeFile(n1_fileName, v_int);*/
    
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



void writeFile(const char *n_fileName, vector<struct pixel> &v)
{
    
    FILE *file;
    unsigned char output[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            output[i][j] = v.at(i * (width) + j).gray;
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (width) * (height), file);
    fclose(file);
}


void kernel(vector< vector<double> > &vv)
{
    vector<double> v1;
    
    double a[5][5] = {{1, 4, 6, 4, 1},
        {-1, -2, 0, 2, 1},
        {-1, 0, 2, 0, -1},
        {-1, 2, 0, -2, 1},
        {1, -4, 6, -4, 1}};
        
        
    double b[5][5] = {{1, -1, -1, -1, 1},
        {4, -2, 0, 2, -4},
        {6, 0, 2, 0, 6},
        {4, 2, 0, -2, -4},
        {1, 1, -1, 1, 1}};
        
    
    
    ///////// a[0][] * b[][0] //////////======= 1
    
    double c[5][5] = {0};
    double w = (double)1 / (16 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[0][j] * b[i][0] * w;
            //cout << c[i][j] << " ";
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[0][] * b[][1] //////////======= 2
    
    w = (double)1 / (16 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[0][j] * b[i][1] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[0][] * b[][2] //////////======= 3
    
    w = (double)1 / (16 * 4);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[0][j] * b[i][2] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[0][] * b[][3] //////////======= 4
    
    w = (double)1 / (16 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[0][j] * b[i][3] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[0][] * b[][4] //////////======= 5
    
    w = (double)1 / (16 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[0][j] * b[i][4] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[1][] * b[][0] //////////======= 6
    
    w = (double)1 / (6 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[1][j] * b[i][0] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[1][] * b[][1] //////////======= 7
    
    w = (double)1 / (6 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[1][j] * b[i][1] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[1][] * b[][2] //////////======= 8
    
    w = (double)1 / (6 * 4);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[1][j] * b[i][2] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[1][] * b[][3] //////////======= 9
    
    w = (double)1 / (6 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[1][j] * b[i][3] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[1][] * b[][4] //////////======= 10
    
    w = (double)1 / (6 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[1][j] * b[i][4] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[2][] * b[][0] //////////======= 11
    
    w = (double)1 / (4 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[2][j] * b[i][0] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[2][] * b[][1] //////////======= 12
    
    w = (double)1 / (4 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[2][j] * b[i][1] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[2][] * b[][2] //////////======= 13
    
    w = (double)1 / (4 * 4);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[2][j] * b[i][2] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[2][] * b[][3] //////////======= 14
    
    w = (double)1 / (4 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[2][j] * b[i][3] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[2][] * b[][4] //////////======= 15
    
    w = (double)1 / (4 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[2][j] * b[i][4] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[3][] * b[][0] //////////======= 16
    
    w = (double)1 / (6 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[3][j] * b[i][0] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[3][] * b[][1] //////////======= 17
    
    w = (double)1 / (6 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[3][j] * b[i][1] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[3][] * b[][2] //////////======= 18
    
    w = (double)1 / (6 * 4);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[3][j] * b[i][2] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[3][] * b[][3] //////////======= 19
    
    w = (double)1 / (6 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[3][j] * b[i][3] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[3][] * b[][4] //////////======= 20
    
    w = (double)1 / (6 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[3][j] * b[i][4] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[4][] * b[][0] //////////======= 21
    
    w = (double)1 / (16 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[4][j] * b[i][0] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[4][] * b[][1] //////////======= 22
    
    w = (double)1 / (16 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[4][j] * b[i][1] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[4][] * b[][2] //////////======= 23
    
    w = (double)1 / (16 * 4);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[4][j] * b[i][2] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[4][] * b[][3] //////////======= 24
    
    w = (double)1 / (16 * 6);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[4][j] * b[i][3] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
    
    
    ///////// a[4][] * b[][4] //////////======= 25
    
    w = (double)1 / (16 * 16);
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            c[i][j] = a[4][j] * b[i][4] * w;
            v1.push_back(c[i][j]);
        }
    }
    vv.push_back(v1);
    v1.clear();
}


void filtering(vector<struct pixel> &v, vector< vector<double> > &vv, vector< vector<double> > &vv_double)
{
    unsigned char input[height + 2 * n][width + 2 * n];
    double output[height][width];
    int i , j, k;
    vector<double> v_double;
    
    for(i = 0; i < height + 2 * n; i++)
    {
        for(j = 0; j < width + 2 * n; j++)
        {
            input[i][j]= v.at(i * (width + 2 * n) + j).gray;
        }
    }

    
    for(k = 0; k < 25; k++)
    {
        double mask[5][5] = {0};
        
        for(i = 0; i < 5; i++)
        {
            for(j = 0; j < 5; j++)
            {
                mask[i][j] = vv.at(k).at(i * 5 +j);
                //cout << mask[i][j] << " " ;
            }
        }
        
        
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                
                double sum = 0;
                
                for(int m = i; m < i + 5; m++)
                {
                    for(int f = j; f < j + 5; f++)
                    {
                        sum += (double)input[m][f] * mask[m - i][f - j];
                        //cout << (double)input[m][f] << "," << mask[m - i][f - j] << ";     ";
                    }
                }
                output[i][j] = sum;
                //cout << sum << endl;
                v_double.push_back(output[i][j]);
            }
        }
       
        vv_double.push_back(v_double);
        v_double.clear();
    }
    
}


void enlarge(vector<struct pixel> &v, int n)
{
    
    unsigned char a[height][width];
    unsigned char c[height + 2 * n][width + 2 * n];
    unsigned char b[height + 2 * n][width];
    pixel p;
    
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



void enlarge_double(vector< vector<double> > &vv_double, vector< vector<double> > &vv_double1, int x)
{
    
    double a[height][width];
    double c[height + 2 * x][width + 2 * x];
    double b[height + 2 * x][width];
    vector<double> v_double;
    
    for(int k = 0; k < 25; k++)
    {
        
    
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                a[i][j] = vv_double.at(k).at(i * width + j);
            }
        }
    
   
    ///////////////////////////copy in b from a////////////////////////
    
    
        for(int i = 0; i < x; i++)
        {
            for(int j = 0; j < width; j++)
            {
            
            
                b[i][j] = a[x - i][j];
            
            }
        }
    
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
            
            
                b[i + x][j] = a[i][j];
            
            }
        }
    
        for(int i = 0; i < x; i++)
        {
            for(int j = 0; j < width; j++)
            {
            
            
                b[height - 1 + 2 * x - i][j] = a[height - 1 - x + i][j];
            
            }
        }
    
    
    
    
    
    ///////////////////////////copy in c from b////////////////////////
    
    
    
        for(int i = 0; i < height + 2 * x; i++)
        {
            for(int j = 0; j < x; j++)
            {
            
            
                c[i][j] = b[i][x - j];
            
            }
        }
    
        for(int i = 0; i < height + 2 * x; i++)
        {
            for(int j = 0; j < width; j++)
            {
            
            
                c[i][j + x] = b[i][j];
                
            }
        }
    
        for(int i = 0; i < height + 2 * x; i++)
        {
            for(int j = 0; j < x; j++)
            {
            
            
                c[i][width - 1 + 2 * x - j] = b[i][width - 1 - x + j];
            
            }
        }
    
    
    
    
        for(int i = 0; i < height + 2 * x; i++)
        {
            for(int j = 0; j < width + 2 * x; j++)
            {
                v_double.push_back(c[i][j]);
            }
        }
        
        vv_double1.push_back(v_double);
        v_double.clear();
    
    }
    vv_double.clear();
}





void calAveEnergy(vector< vector<double> > &vv_double1, int x)
{
    
    double input[height + 2 * x][width + 2 * x];
    double output[height][width];
    int i, j, k;
    //cout << "11111111111"<< endl;
    for(k = 0; k < 25; k++)
    {
    
        for(i = 0; i < height + 2 * x; i++)
        {
            for(j = 0; j < width + 2 * x; j++)
            {
                //cout << "11111111111"<< endl;
                input[i][j]= vv_double1.at(k).at(i * (width + 2 * x) + j);
                //cout << "11111111111"<< endl;
            }
        }
        
        //cout << "11111111111"<< endl;
    
        double sum1 = 0;
        double average1 = 0;
        
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                
                double sum = 0;
                double average = 0;
                
                for(int m = i; m < i + 2 * x + 1; m++)
                {
                    for(int f = j; f < j + 2 * x + 1; f++)
                    {
                        sum += input[m][f] * input[m][f];
                    }
                }
                
                average = sum / ((2 * x + 1) * (2 * x + 1));
                sum1 += average;
            }
        }
        
        average1 = sum1 / (height * width);
        cout << average1 <<endl;
    }

    

}




void calEnergy(vector< vector<double> > &com_vv_double1, int x)
{
    
    double input[height + 2 * x][width + 2 * x];
    double output[height][width];
    int i, j, k;
    FILE *file;
    const char *eng_Name[25] = {"eng_Name1.txt", "eng_Name2.txt", "eng_Name3.txt", "eng_Name4.txt", "eng_Name5.txt", "eng_Name6.txt", "eng_Name7.txt", "eng_Name8.txt", "eng_Name9.txt", "eng_Name10.txt","eng_Name11.txt", "eng_Name12.txt", "eng_Name13.txt","eng_Name14.txt", "eng_Name15.txt", "eng_Name16.txt", "eng_Name17.txt", "eng_Name18.txt", "eng_Name19.txt", "eng_Name20.txt", "eng_Name21.txt", "eng_Name22.txt", "eng_Name23.txt", "eng_Name24.txt", "eng_Name25.txt"};
    
    //cout << "11111111111"<< endl;
    
    //vector< vector<double> > vvv;
    //vector<double> vss;
    double temp[height][width];
    
    for(k = 0; k < 25; k++)
    {
        
        for(i = 0; i < height + 2 * x; i++)
        {
            for(j = 0; j < width + 2 * x; j++)
            {
                //cout << "11111111111"<< endl;
                input[i][j]= com_vv_double1.at(k).at(i * (width + 2 * x) + j);
                
            }
        }
       
        
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                
                double sum = 0;
                double average = 0;
                
                for(int m = i; m < i + 2 * x + 1; m++)
                {
                    for(int f = j; f < j + 2 * x + 1; f++)
                    {
                        //sum += input[m][f] * input[m][f];
                        sum += fabs(input[m][f]);
                    }
                }
                
                average = sum / ((2 * x + 1) * (2 * x + 1));
                output[i][j] = average;
                //cout<< average<<",     ";
                //vss.push_back(average);
            }
        }
        
        /*if(k == 0)
        {
            for(i = 0; i < height; i++)
            {
                for(j = 0; j < width; j++)
                {
                    temp[i][j] = output[i][j];
                }
            }
        }
        
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                output[i][j] /= temp[i][j];
            }
        }*/
        
    
    
   /* double temp[height][width];
    
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            temp[i][j] = vvv.at(0).at(i * width + height);
        }
    }
    
    //cout << "11111111111"<< endl;
    
    for(k = 0; k < 25; k++)
    {
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                output[k][i][j] = vvv.at(k).at(i * width + height);
                output[k][i][j] = output[k][i][j] / temp[i][j];
            }
        }
    }*/
    
    
        if((file = fopen(eng_Name[k], "wb")) != NULL)
        {
            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    fprintf(file, "%f\n", output[i][j]);
                }
            }
        }
        fclose(file);
    }
    
    
    
}




void readIndex(const char *index_fileName, vector<pixel> &v_int)
{
    FILE *file;
    unsigned char input[height][width];
    pixel p;
    
    if (!(file = fopen(index_fileName,"rb")))
    {
        cout << "Cannot open file: " << index_fileName << endl;
        exit(1);
    }
    
    fread(input, sizeof(unsigned char), width * height, file);
    fclose(file);
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p.gray = input[i][j];
            cout << input[i][j] << endl;
            v_int.push_back(p);
        }
    }

}

void display(vector<pixel> &v_int)
{
    unsigned char input[height][width];
    unsigned char output[height][width];
    pixel p;
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            input[i][j] = v_int.at(i * width + j).gray;
        }
    }
    v_int.clear();
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(input[i][j] == 1)
            {
                output[i][j] = 51;
            }
            
            if(input[i][j] == 2)
            {
                output[i][j] = 102;
            }
            
            if(input[i][j] == 3)
            {
                output[i][j] = 153;
            }
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p.gray = output[i][j];
            v_int.push_back(p);
        }
    }
}





















        
        
        
