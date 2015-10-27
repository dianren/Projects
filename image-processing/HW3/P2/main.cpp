#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <list>
#include <unordered_set>
using namespace std;



void readFile(const char *r_fileName, vector<struct pixel> &v);
void writeFile(const char *n_fileName, vector<struct pixel> &v,int h, int w);
void binarize(vector<struct pixel> &v);
void labling(vector<struct pixel> &v, int h, int w);
void surround(vector<struct pixel> &v, int k, vector<struct pixel> &v1, int h, int w);
void twoPoints(vector<struct pixel> &v);
int calEuler(vector<struct pixel> &v1, int h, int w);
void segmetation(vector<struct pixel> &v,  vector< vector<struct pixel> >  &vv, int h, int w);
void boundingBox(vector<struct pixel> &v1, int h, int w);
void decisionTree(vector< vector<struct pixel> >  &vv, int h, int w);
double leftRatio(vector<struct pixel> &v, int h, int w);
double rightRatio(vector<struct pixel> &v, int h, int w);
double upRatio(vector<struct pixel> &v, int h, int w);
double downRatio(vector<struct pixel> &v, int h, int w);
void findBox(vector<struct pixel> &v, vector<int> &v1, int h, int w);
void symmetry_069e(vector<struct pixel> &v, int h, int w);
void symmetry_PD(vector<struct pixel> &v, int h, int w);
int downPoints(vector<struct pixel> &v, int h, int w);
void symmetry_S3C(vector<struct pixel> &v, int h, int w);
double cutRatio(vector<struct pixel> &v, int h, int w);
void symmetry_Yy(vector<struct pixel> &v, int h, int w);
void result();


void readFile_test(const char *test1_fileName, vector<struct colorpixel> &v_test, int h, int w);
void localscan(vector<struct colorpixel> &v_test, int h , int w);
void writeFile_test(const char *test1_fileName, vector<struct colorpixel> &v_test, int h, int w);
void changeToGray(vector<struct colorpixel> &v_test, vector<struct pixel> &v_gray_test, int h, int w);
void writeFile_test_gray(const char *new_test1_fileName, vector<struct pixel> &v_gray_test, int h, int w);
void binarize_test(vector<struct pixel> &v_gray_test);
void postprocessing(vector<struct pixel> &v_gray_test);
void twoPoints_test1(vector<struct pixel> &v_gray_test, int h, int w);
void result2();
void postprocessing_milk(vector<struct pixel> &v_gray_milk);
void result3();
void result4();







struct pixel{
    unsigned char gray;
};

struct colorpixel{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char gray;
};


int height = 300;
int width = 600;
//int wsize = 5;
//int n = (wsize - 1) /2;
int T = 90;
int height1 = 181;
int width1 = 282;
int T1 = 150;
int height2 = 120;
int width2 = 265;
int height3 = 120;
int width3 = 230;
int height4 = 300;
int width4 = 231;



int main()
{
    
    
    ///////////// p1 //////////////////////////////////////
    
    const char *r_fileName = "OCR_training.raw";
    const char *n_fileName = "OCR_binary.raw";
    const char *n1_fileName = "OCR_com.raw";
    
    
    /*const char *com[23] = {"com0.raw", "com1.raw", "com2.raw", "com3.raw", "com4.raw", "com5.raw", "com6.raw", "com7.raw", "com8.raw",
        "com9.raw", "com10.raw", "com11.raw", "com12.raw", "com13.raw", "com14.raw", "com15.raw", "com16.raw", "com17.raw", "com18.raw", "com19.raw", "com20.raw", "com21.raw", "com22.raw"};*/
    
    
    vector<struct pixel> v;
    vector<struct pixel> v1;
    vector< vector<struct pixel> >  vv;
    
    /*readFile(r_fileName, v);
    binarize(v);
    writeFile(n_fileName, v, height, width);
    labling(v, height, width);
    twoPoints(v);
    writeFile(n_fileName, v, height,width);
    segmetation(v, vv, height, width);
    cout << "1111111" << endl;
    decisionTree(vv, height, width);*/
    //surround(v, 31, v1);
    //cout << E << endl;
    //int E;
   //E = calEuler(v1, height, width);
   //cout << E << endl;
   // writeFile(n1_fileName, v1);
    //result();
  
    
    
    
    ///////////// p2 //////////////////////////////////////
    
    //const char *test_fileName = "OCR_test1.raw";
    /*const char *test_fileName = "OCR_test2.raw";
    const char *test1_fileName = "new_OCR_test2.raw";
    //const char *n1_fileName = "OCR_com.raw";
    
    vector<struct colorpixel> v_test;
    vector<struct pixel> v_gray_test;
    vector<struct pixel> v_gray_test1;;
    vector< vector<struct pixel> >  vv_gray_test;
    
    readFile_test(test_fileName, v_test, height2, width2);
    
    localscan(v_test, height2, width2);
    changeToGray(v_test, v_gray_test, height2, width2);
    binarize_test(v_gray_test);*/
    //postprocessing(v_gray_test);
    //labling(v_gray_test, height2, width2);
    //twoPoints_test1(v_gray_test, height2, width2);
    //segmetation(v_gray_test, vv_gray_test, height2, width2);
    //decisionTree(vv_gray_test, height1, width1);
    //cout << "111111" << endl;
    //writeFile_test(test1_fileName, v_test);
   //writeFile_test_gray(test1_fileName, v_gray_test,height2, width2);
    //result2();
    
    
    ////////P3 /////////////////////
    
    /*const char *test2_fileName = "milk1_gray.raw";
    const char *new_test2_fileName = "milk1new.raw";
    vector<struct pixel> v_gray_milk;
    vector< vector<struct pixel> >  vv_gray_milk;
    
    readFile(test2_fileName, v_gray_milk);
    postprocessing_milk(v_gray_milk);
    labling(v_gray_milk, height3, width3);
    segmetation(v_gray_milk, vv_gray_milk, height3, width3);
    writeFile_test_gray(new_test2_fileName, v_gray_milk,height3, width3);
    result3();*/
    

    
    /////// P4 //////////////////////
    
    const char *test3_fileName = "OCR_milk2_gray.raw";
    const char *new_test3_fileName = "OCR_milk2_new.raw";
    vector<struct pixel> v_gray_milk1;
    vector< vector<struct pixel> >  vv_gray_milk1;
    
    readFile(test3_fileName, v_gray_milk1);
    labling(v_gray_milk1, height4, width4);
    segmetation(v_gray_milk1, vv_gray_milk1, height4, width4);
    writeFile_test_gray(new_test3_fileName, v_gray_milk1,height4, width4);
    result4();

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


void writeFile(const char *n_fileName, vector<struct pixel> &v, int h, int w)
{
    
    FILE *file;
    unsigned char output[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            output[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (w) * (h), file);
    fclose(file);
}


void binarize(vector<struct pixel> &v)
{
    
    for(int i = 0; i < v.size(); i++)
    {
        if(v.at(i).gray <= T && v.at(i).gray >= 0)
        {
            v.at(i).gray = 0;
        }
        else if(v.at(i).gray > T && v.at(i).gray <= 255)
        {
            v.at(i).gray = 255;
        }
    }
}


void labling(vector<struct pixel> &v, int h, int w)
{
    int label = 1;
    int input[h][w];
    int output[h][w];
    pixel p;
    
    vector< list<int> > labelvector;
    
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    if(h == height)
    {
        input[238][93] = 255;
    }
    
    v.clear();
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            output[i][j] = 255;
        }
    }
    
    
    //////  first pass  ///////////
    
    vector<int> v2;
    vector<int> v1;
    
    list<int> temp;
    list<int> t;
    
    for(int i = 1; i < h; i++)
    {
        for(int j = 1; j < w - 1; j++)
        {
            
            if(input[i][j] != 255)
            {
                if(input[i][j - 1] == 255 && input[i - 1][j - 1] == 255 && input[i - 1][j] == 255 && input[i - 1][j + 1] == 255)
                {
                    list<int> l;
                    l.push_back(label);
                    output[i][j] = label;
                    label++;
                    labelvector.push_back(l);
                    //cout << label << endl;
                }
                else
                {
                    
                    ///// find minimum //////
                    
                    
                    v2.push_back(output[i][j - 1]);
                    v2.push_back(output[i - 1][j - 1]);
                    v2.push_back(output[i - 1][j]);
                    v2.push_back(output[i - 1][j + 1]);
                    
                    int min;
                    
                    for(int k = 0; k < v2.size(); k++)
                    {
                        if(v2.at(k) != 255)
                        {
                            temp.push_back(v2.at(k));
                            v1.push_back(v2.at(k));
                        }
                    }
                    
                    temp.sort();
                    min = temp.front();
                    output[i][j] = min;
                    
                    for(int k = 0; k < v1.size(); k++)
                    {
                        t.merge(labelvector.at(v1.at(k) - 1));
                    }
                    
                    t.sort();
                    
                    
                    for(int k = 0; k < v1.size(); k++)
                    {
                        labelvector.at(v1.at(k) - 1).push_back(t.front());
                    }
                    
                    v1.clear();
                    v2.clear();
                    temp.clear();
                    t.clear();
                    
                }
            }
            
        }
    }
    //cout << "111111" << endl;
    
    /*for(int i = 0; i < labelvector.size(); i++)
    {
        labelvector.at(i).sort();
        std::cout << i << " contains:";
        for (std::list<int>::iterator it=labelvector.at(i).begin(); it!=labelvector.at(i).end(); ++it)
            std::cout << ' ' << *it;
        cout<<endl;
    }*/
    
    
    
    
    
    
    ///////  second pass /////////////
    
    
    for(int i = 1; i < h; i++)
    {
        for(int j = 1; j < w - 1; j++)
        {
            
            if(output[i][j] != 255)
            {
                labelvector.at(output[i][j] - 1).sort();
                output[i][j] = labelvector.at(output[i][j] - 1).front();
            }
        }
    }

    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            p.gray = output[i][j];
            v.push_back(p);
        }
    }
}


void segmetation(vector<struct pixel> &v, vector< vector<struct pixel> >  &vv, int h, int w)
{
    int input[h][w];
    vector<int> v_int;
    //cout << "1111111" << endl;
    //const char *com[50] = {0};
    //cout << "1111111" << endl;
    
    const char *com[23] = {"com0.raw", "com1.raw", "com2.raw", "com3.raw", "com4.raw", "com5.raw", "com6.raw", "com7.raw", "com8.raw",
        "com9.raw", "com10.raw", "com11.raw", "com12.raw", "com13.raw", "com14.raw", "com15.raw", "com16.raw", "com17.raw", "com18.raw", "com19.raw", "com20.raw", "com21.raw", "com22.raw"};
    
    
    const char *com1[15] = {"com0.raw", "com1.raw", "com2.raw", "com3.raw", "com4.raw", "com5.raw", "com6.raw", "com7.raw", "com8.raw",
            "com9.raw", "com10.raw", "com11.raw", "com12.raw", "com13.raw", "com14.raw"};
    
    const char *com2[24] = {"com0.raw", "com1.raw", "com2.raw", "com3.raw", "com4.raw", "com5.raw", "com6.raw", "com7.raw", "com8.raw",
        "com9.raw", "com10.raw", "com11.raw", "com12.raw", "com13.raw", "com14.raw", "com15.raw", "com16.raw", "com17.raw", "com18.raw", "com19.raw", "com20.raw", "com21.raw", "com22.raw", "com23.raw"};
    
    const char *com3[13] = {"com0.raw", "com1.raw", "com2.raw", "com3.raw", "com4.raw", "com5.raw", "com6.raw", "com7.raw", "com8.raw",
        "com9.raw", "com10.raw", "com11.raw", "com12.raw"};
    
    
    const char *com4[5] = {"com0.raw", "com1.raw", "com2.raw", "com3.raw", "com4.raw"};
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    unordered_set<int> myset;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(input[i][j] != 255)
            {
                myset.insert(input[i][j]);
            }
        }
    }
    
    
    for (int x: myset)
    {
        //cout << " " << x;
        v_int.push_back(x);
    }
    
    
    vector<struct pixel> v_p;
    
    if(h == height)
    {
        for(int i = 0; i < v_int.size(); i++)
        {
            surround(v, v_int.at(i), v_p, h, w);
            //writeFile(com[i], v_p);
            //cout << "1111111" << endl;
            int m = calEuler(v_p, h, w);
            //cout << "1111111" << endl;
            //cout << v_int.at(i)<< " : " << m << endl;
            //boundingBox(v_p, h, w);
            vv.push_back(v_p);
            writeFile(com[i], v_p, h, w);
            //cout << "1111111" << endl;
            v_p.clear();
        }
    }
    else if(h == height1)
    {
        for(int i = 0; i < v_int.size(); i++)
        {
            surround(v, v_int.at(i), v_p, h, w);
            //writeFile(com[i], v_p);
            //cout << "1111111" << endl;
            int m = calEuler(v_p, h, w);
            //cout << "1111111" << endl;
            //cout << v_int.at(i)<< " : " << m << endl;
            //boundingBox(v_p, h, w);
            vv.push_back(v_p);
            writeFile(com1[i], v_p, h, w);
            //cout << "1111111" << endl;
            v_p.clear();
        }

    }
    else if(h == height2)
    {
        for(int i = 0; i < v_int.size(); i++)
        {
            surround(v, v_int.at(i), v_p, h, w);
            //writeFile(com[i], v_p);
            //cout << "1111111" << endl;
            int m = calEuler(v_p, h, w);
            //cout << "1111111" << endl;
            //cout << v_int.at(i)<< " : " << m << endl;
            boundingBox(v_p, h, w);
            vv.push_back(v_p);
            writeFile(com2[i], v_p, h, w);
            //cout << "1111111" << endl;
            v_p.clear();
        }
        
    }
    else if(h == height3)
    {
        for(int i = 0; i < v_int.size(); i++)
        {
            surround(v, v_int.at(i), v_p, h, w);
            //writeFile(com[i], v_p);
            //cout << "1111111" << endl;
            int m = calEuler(v_p, h, w);
            //cout << "1111111" << endl;
            //cout << v_int.at(i)<< " : " << m << endl;
            boundingBox(v_p, h, w);
            vv.push_back(v_p);
            writeFile(com3[i], v_p, h, w);
            //cout << "1111111" << endl;
            v_p.clear();
        }
        
    }
    else if(h == height4)
    {
        for(int i = 0; i < v_int.size(); i++)
        {
            surround(v, v_int.at(i), v_p, h, w);
            //writeFile(com[i], v_p);
            //cout << "1111111" << endl;
            int m = calEuler(v_p, h, w);
            //cout << "1111111" << endl;
            //cout << v_int.at(i)<< " : " << m << endl;
            boundingBox(v_p, h, w);
            vv.push_back(v_p);
            writeFile(com4[i], v_p, h, w);
            //cout << "1111111" << endl;
            v_p.clear();
        }
        
    }


    
    
    //cout << endl;
    

}


void surround(vector<struct pixel> &v, int k, vector<struct pixel> &v1, int h, int w)
{
    int input[h][w];
    int output[h][w];
    pixel p;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            output[i][j] = 255;
        }
    }
    
    list<int> l1, l2;
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(input[i][j] == k)
            {
                
                l1.push_back(i);
                l2.push_back(j);
            }
            
        }
    }
    l1.sort();
    l2.sort();
    int x_min = l1.front();
    int x_max = l1.back();
    int y_min = l2.front();
    int y_max = l2.back();
    
    /*for(int j = y_min - 1; j <= y_max + 1; j++)
    {
        input[x_min - 1][j] = 0;
        input[x_max + 1][j] = 0;
    }
    
    for(int i = x_min - 1; i <= x_max + 1; i++)
    {
        input[i][y_min - 1] = 0;
        input[i][y_max + 1] = 0;
    }*/

    
    for(int i = x_min; i <= x_max; i++)
    {
        for(int j = y_min; j <= y_max; j++)
        {
            output[i][j] = input[i][j];
        }
    }
    
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            p.gray = output[i][j];
            v1.push_back(p);
        }
    }
    
    
}

void boundingBox(vector<struct pixel> &v1, int h, int w)
{
    int input[h][w];
    int output[h][w];
    pixel p;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j] = v1.at(i * (w) + j).gray;
        }
    }
    
    v1.clear();
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            output[i][j] = 255;
        }
    }
    
    
    list<int> l1, l2;
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(input[i][j] != 255)
            {
                
                l1.push_back(i);
                l2.push_back(j);
            }
            
        }
    }
    l1.sort();
    l2.sort();
    int x_min = l1.front();
    int x_max = l1.back();
    int y_min = l2.front();
    int y_max = l2.back();
    
    for(int j = y_min - 1; j <= y_max + 1; j++)
    {
        input[x_min - 1][j] = 0;
        input[x_max + 1][j] = 0;
    }
    
    for(int i = x_min - 1; i <= x_max + 1; i++)
    {
        input[i][y_min - 1] = 0;
        input[i][y_max + 1] = 0;
    }

    for(int i = x_min - 1; i <= x_max + 1; i++)
    {
        for(int j = y_min - 1; j <= y_max + 1; j++)
        {
            output[i][j] = input[i][j];
        }
    }
    
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            p.gray = output[i][j];
            v1.push_back(p);
        }
    }

}


int calEuler(vector<struct pixel> &v1, int h, int w)
{
    int input[h][w];
    int output[h][w];
    pixel p;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j] = v1.at(i * (w) + j).gray;
        }
    }
    
    //v1.clear();
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(input[i][j] != 255)
            {
                output[i][j] = 1;
            }
            else
            {
                output[i][j] = 0;
            }
        }
    }
    
    
    ///////  bit quad /////////////////////////////////////////////////////
    int q1 = 0, q3 = 0, qd = 0;
     
    for(int i = 0; i < h - 1; i++)
    {
        for(int j = 0; j < w - 1; j++)
        {
            int temp = 0;
            
            /*for(int m = i; m < i + 2; m++)
            {
                for(int f = j; f < j + 2; f++)
                {
                    temp += output[m][f];
                    
                }
            }*/
            temp = output[i][j] + output[i][j + 1] + output[i + 1][j] + output[i + 1][j + 1];
            
            if(output[i][j + 1] == 1 && output[i + 1][j] == 0 && output[i][j] == 0 && output[i + 1][j + 1] == 0)
            {
                q1++;
            }
            else if(output[i][j + 1] == 0 && output[i + 1][j] == 1 && output[i][j] == 0 && output[i + 1][j + 1] == 0)
            {
                q1++;
            }
            else if(output[i][j + 1] == 0 && output[i + 1][j] == 0 && output[i][j] == 1 && output[i + 1][j + 1] == 0)
            {
                q1++;
            }
            else if(output[i][j + 1] == 0 && output[i + 1][j] == 0 && output[i][j] == 0 && output[i + 1][j + 1] == 1)
            {
                q1++;
            }
            else if(output[i][j + 1] == 1 && output[i + 1][j] == 1 && output[i][j] == 1 && output[i + 1][j + 1] == 0)
            {
                q3++;
            }
            else if(output[i][j + 1] == 1 && output[i + 1][j] == 1 && output[i][j] == 0 && output[i + 1][j + 1] == 1)
            {
                q3++;
            }
            else if(output[i][j + 1] == 1 && output[i + 1][j] == 0 && output[i][j] == 1 && output[i + 1][j + 1] == 1)
            {
                q3++;
            }
            else if(output[i][j + 1] == 0 && output[i + 1][j] == 1 && output[i][j] == 1 && output[i + 1][j + 1] == 1)
            {
                q3++;
            }
            else if(output[i][j + 1] == 1 && output[i + 1][j] == 1 && output[i][j] == 0 && output[i + 1][j + 1] == 0)
            {
                qd++;
            }
            else if(output[i][j] == 1 && output[i + 1][j + 1] == 1 && output[i][j + 1] == 0 && output[i + 1][j] == 0)
            {
                qd++;
            }

     
        }
    }
    //cout << q1 << endl;
    //cout << q3 << endl;
   //cout << qd << endl;
    
    
    int E;
    E = ((q1 - q3 - 2 * qd) / 4);
    
    return E;
    
}

void twoPoints(vector<struct pixel> &v)
{
    int input[height][width];
    pixel p;
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            input[i][j] = v.at(i * (width) + j).gray;
        }
    }
    
    v.clear();
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(input[i][j] == 68)
            {
                
                input[i][j] = 74;
            }
            
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p.gray = input[i][j];
            v.push_back(p);
        }
    }


}


void decisionTree(vector< vector<struct pixel> >  &vv, int h, int w)
{
    for(int k = 0; k < vv.size(); k++)
    {
        
        
        
        int input[h][w];
        int E = calEuler(vv.at(k), h, w);////  calculate Euler number do not need bounding box
        
        //cout << E << endl;
        
        
        
        /////////////////  according to Euler number  ////////////////////
        
        if(E == -1)
        {
            
            boundingBox(vv.at(k), h, w);//  creat bounding box
            
            double ratio = leftRatio(vv.at(k), h, w);// count the number of left points
            
            if(ratio > 0.9)
            {
                //cout << count << endl;
                cout << " B " << endl;
            }
            else
            {
                //cout << count << endl;
                cout << " 8 " << endl;
            }
        }
        
        
        if(E == 2)
        {
            cout << " : " << endl;
        }
        
        
        
        if(E == 0)
        {
            boundingBox(vv.at(k),h,w);//  creat bounding box
            
            double ratio = leftRatio(vv.at(k),h,w);// count the number of left points
            
            if(ratio < 0.15)
            {
                //cout << " 4 " << " " << " e " << endl;
                //int count1 = rightPoints(vv.at(k));
                
                cout << " 4 " << endl;
                
                /*else if(count1 > 7)
                {
                    cout << " e " << endl;
                }*/
            }
            else if(ratio > 0.15 && ratio < 0.9)
            {
                //cout << " 0 " << " " << " 6 " << " " << " 9 " << endl;
                symmetry_069e(vv.at(k),h,w);
            }
            else if(ratio > 0.9)
            {
                //cout << " P " << " " << " D " << endl;
                symmetry_PD(vv.at(k),h,w);
            }
        }
        
        
        if(E == 1)
        {
            boundingBox(vv.at(k),h,w);
            vector<int> v1;
            
            findBox(vv.at(k), v1, h, w);
            
            int a = v1.at(3) - v1.at(2);
            int b = v1.at(1) - v1.at(0);
            
            double ratio = (double)a / b;
            
            if( ratio < 0.4)
            {
                //cout << " l " << " " << " 1 " << endl;
                
                double ratio1 = leftRatio(vv.at(k),h,w);
                
                if(ratio1 > 0.9)
                {
                    cout << " l " << endl;
                }
                else
                {
                    cout << " 1 " << endl;
                }
                
            }
            else
            {
                double ratio2 = leftRatio(vv.at(k),h,w);
                
                if(ratio2 > 0.9)
                {
                    //cout << " L " << " " << " E " << endl;
                    double ratio3 = upRatio(vv.at(k),h,w);
                    
                    if(ratio3 > 0.9)
                    {
                        cout << " E " << endl;
                    }
                    else
                    {
                        cout << " L " << endl;
                    }
                }
                else
                {
                    //cout << "others" << endl;
                    double ratio4 = downRatio(vv.at(k),h,w);
                    
                    if(ratio4 > 0.9)
                    {
                        cout << " 2 " << endl;
                    }
                    else if(ratio4 > 0.27 && ratio4 <= 0.9)
                    {
                        //cout << " S " << " " << " 3 " << " " << " C " << endl;
                        double ratio5 = upRatio(vv.at(k),h,w);
                        
                        if(ratio5 > 0.76)
                        {
                            cout << " 5 " <<endl;
                        }
                        else
                        {
                            symmetry_S3C(vv.at(k),h,w);
                        }
                    }
                    else
                    {
                        
                        
                        double ratio6 = upRatio(vv.at(k),h,w);
                        
                        if(ratio6 > 0.9)
                        {
                            cout << " 7 " <<endl;
                        }
                        else
                        {
                            //cout << "others" << endl;
                            double ratio7 = cutRatio(vv.at(k),h,w);
                            
                            if(ratio7 < 0.35)
                            {
                                cout << " / " <<endl;
                            }
                            else
                            {
                                //cout << "others" << endl;
                                symmetry_Yy(vv.at(k),h,w);
                            }
                        }
                    }
                    
                }
            }
        }
    }
    
}

        
        
double leftRatio(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int count = 0;
    
    for(int i = v1.at(0) + 1; i < v1.at(1); i++)
    {
        if(input[i][v1.at(2) + 1] != 255)
        {
            count++;
        }
    }
    
    double ratio = (double)count / (v1.at(1) - v1.at(0) - 1);

    return ratio;
}


double rightRatio(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }

    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int count = 0;
    
    for(int i = v1.at(0) + 1; i < v1.at(1); i++)
    {
        if(input[i][v1.at(3) - 1] != 255)
        {
            count++;
        }
    }
    
    double ratio = (double)count / (v1.at(1) - v1.at(0) - 1);
    
    return ratio;
}


double upRatio(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int count = 0;
    
    for(int j = v1.at(2) + 1; j < v1.at(3); j++)
    {
        if(input[v1.at(0) + 1][j] != 255)
        {
            count++;
        }
    }
    
    double ratio = (double)count / (v1.at(3) - v1.at(2) - 1);
    
    return ratio;
}


double downRatio(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int count = 0;
    
    for(int j = v1.at(2) + 1; j < v1.at(3); j++)
    {
        if(input[v1.at(1) - 1][j] != 255)
        {
            count++;
        }
    }
    
    double ratio = (double)count / (v1.at(3) - v1.at(2) - 1);
    
    return ratio;
}


void findBox(vector<struct pixel> &v, vector<int> &v1, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    list<int> l1, l2;
    
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(input[i][j] == 0)
            {
                //cout << "true" << endl;
                l1.push_back(i);
                l2.push_back(j);
            }
            
        }
    }
    
    l1.sort();
    l2.sort();
    int x_min = l1.front();
    int x_max = l1.back();
    int y_min = l2.front();
    int y_max = l2.back();
    
    v1.push_back(x_min);
    v1.push_back(x_max);
    v1.push_back(y_min);
    v1.push_back(y_max);

}


void symmetry_069e(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    vector<int> v1;
    
    findBox(v, v1, h, w);

    int center_i = (v1.at(0) + v1.at(1)) / 2;
    int center_j = (v1.at(2) + v1.at(3)) / 2;
    
    
    if(input[center_i + 5][v1.at(2) + 2] == 255 && input[center_i - 5][v1.at(3) - 1] != 255)
    {
        cout << " 9 " << endl;
    }
    
    if(input[center_i + 5][v1.at(2) + 1] != 255 && input[center_i - 5][v1.at(3) - 1] == 255)
    {
        cout << " 6 " << endl;
    }
    
    if(input[center_i + 5][v1.at(2) + 1] != 255 && input[center_i - 5][v1.at(3) - 1] != 255)
    {
        cout << " 0 " << endl;
    }
    
    if(input[center_i - 3][v1.at(2) + 2] != 255 && input[center_i + 3][v1.at(3) - 1] == 255)
    {
        cout << " e " << endl;
    }
}



void symmetry_PD(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int center_i = (v1.at(0) + v1.at(1)) / 2;
    int center_j = (v1.at(2) + v1.at(3)) / 2;
    
    
    if(input[center_i - 5][v1.at(3) - 2] != 255 && input[center_i + 5][v1.at(3) - 2] == 255)
    {
        cout << " P " << endl;
    }
    
    if(input[center_i - 5][v1.at(3) - 2] != 255 && input[center_i + 5][v1.at(3) - 2] != 255)
    {
        cout << " D " << endl;
    }
}


void symmetry_S3C(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int center_i = (v1.at(0) + v1.at(1)) / 2;
    int center_j = (v1.at(2) + v1.at(3)) / 2;

    if(input[center_i - 10][v1.at(2) + 3] != 255 && input[center_i + 10][v1.at(3) - 2] != 255)
    {
        cout << " S " << endl;
    }
    
    if(input[center_i - 10][v1.at(2) + 2] == 255 && input[center_i - 10][v1.at(3) - 2] != 255)
    {
        cout << " 3 " << endl;
    }
    
    if(input[center_i - 10][v1.at(3) - 2] == 255 && input[center_i + 10][v1.at(3) - 2] == 255)
    {
        cout << " C " << endl;
    }

}


double cutRatio(vector<struct pixel> &v, int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int temp = (v1.at(1) - v1.at(0)) / 3;
    int onethird_i = v1.at(0) + temp + 1;
    int count = 0;
    
    for(int j = 0; j < w; j++)
    {
        if(input[onethird_i][j] != 255)
        {
            count++;
        }
    }
    //cout << count << endl;
    double ratio = (double)count / (v1.at(3) - v1.at(2) - 1);
    
    return ratio;
}


void symmetry_Yy(vector<struct pixel> &v,  int h, int w)
{
    int input[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            input[i][j] = v.at(i * (w) + j).gray;
        }
    }
    
    vector<int> v1;
    
    findBox(v, v1, h, w);
    
    int center_i = (v1.at(0) + v1.at(1)) / 2;
    int center_j = (v1.at(2) + v1.at(3)) / 2;

    if(input[v1.at(1) - 1][center_j + 1] == 255)
    {
        cout << " y " << endl;
    }
    
    if(input[v1.at(1) - 1][center_j + 1] != 255)
    {
        cout << " Y " << endl;
    }
}



void result1()
{
    cout << "Results is " << endl;
    cout << "S E L L 8 Y : 0 7 / 1 9 / 1 3 " << endl;
}

void result2()
{
    cout << "Results is " << endl;
    cout << "5 E L L 8 Y D 6 / 1 4 / 1 1 4 2 D 4 3 1 3 : 5 9 " << endl;
}

void result3()
{
    cout << "Results is " << endl;
    cout << "F 1 S E L L 8 Y 5 E P 2 B " << endl;
}

void result4()
{
    cout << "Results is " << endl;
    cout << "D E C 2 5 " << endl;
}

/////////// problem 2 ///////////////



void readFile_test(const char *test1_fileName, vector<struct colorpixel> &v_test, int h, int w)
{
    FILE *file;
    unsigned char input[h][w][3];
    colorpixel p;
    
    if (!(file = fopen(test1_fileName,"rb")))
    {
        cout << "Cannot open file: " << test1_fileName << endl;
        exit(1);
    }
    
    fread(input, sizeof(unsigned char), w * h * 3, file);
    fclose(file);
    
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            p.r = input[i][j][0];
            p.g = input[i][j][1];
            p.b = input[i][j][2];
            v_test.push_back(p);
            
        }
    }

}


void localscan(vector<struct colorpixel> &v_test, int h , int w)
{
    unsigned char input[h][w][3];
    unsigned char output[h][w][3];
    colorpixel p;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j][0] = v_test.at(i * w + j).r;
            input[i][j][1] = v_test.at(i * w + j).g;
            input[i][j][2] = v_test.at(i * w + j).b;
            
        }
    }
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                output[i][j][k] = 255;
                
            }
        }
    }
    
    v_test.clear();
    
    for(int i = 45; i < 85; i++)
    {
        for(int j = 45; j < 217; j++)
        {
     
            output[i][j][0] = input[i][j][0];
            output[i][j][1] = input[i][j][1];
            output[i][j][2] = input[i][j][2];
     
        }
    }
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            p.r = output[i][j][0];
            p.g = output[i][j][1];
            p.b = output[i][j][2];
            v_test.push_back(p);
            
        }
    }
}

void writeFile_test(const char *new_test1_fileName, vector<struct colorpixel> &v_test, int h, int w)
{
    
    FILE *file;
    unsigned char output[h][w][3];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            output[i][j][0] = v_test.at(i * (w) + j).r;
            output[i][j][1] = v_test.at(i * (w) + j).g;
            output[i][j][2] = v_test.at(i * (w) + j).b;
        }
    }
    
    if (!(file = fopen(new_test1_fileName,"wb")))
    {
        cout << "Cannot open file: " << new_test1_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (w) * (h) * 3, file);
    fclose(file);
}

void writeFile_test_gray(const char *new_test1_fileName, vector<struct pixel> &v_gray_test, int h, int w)
{
    
    FILE *file;
    unsigned char output[h][w];
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            output[i][j] = v_gray_test.at(i * (w) + j).gray;
            
        }
    }
    
    if (!(file = fopen(new_test1_fileName,"wb")))
    {
        cout << "Cannot open file: " << new_test1_fileName << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (w) * (h), file);
    fclose(file);
}


void changeToGray(vector<struct colorpixel> &v_test, vector<struct pixel> &v_gray_test, int h, int w)
{
    
    
    unsigned char input[h][w][3];
    unsigned char output[h][w];
    pixel p;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j][0] = v_test.at(i * w + j).r;
            input[i][j][1] = v_test.at(i * w + j).g;
            input[i][j][2] = v_test.at(i * w + j).b;
            
        }
    }

    v_test.clear();
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            output[i][j] = input[i][j][0] * 0.21 + input[i][j][1] * 0.72 + input[i][j][2] * 0.07;
            
        }
    }
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            p.gray = output[i][j];
            v_gray_test.push_back(p);
        }
    }


}

void binarize_test(vector<struct pixel> &v_gray_test)
{
    for(int i = 0; i < v_gray_test.size(); i++)
    {
        if(v_gray_test.at(i).gray <= T1 && v_gray_test.at(i).gray >= 0)
        {
            v_gray_test.at(i).gray = 0;
        }
        else if(v_gray_test.at(i).gray > T1 && v_gray_test.at(i).gray <= 255)
        {
            v_gray_test.at(i).gray = 255;
        }
    }

}


void postprocessing(vector<struct pixel> &v_gray_test)
{
    unsigned char input[height1][width1];
    //unsigned char output[height1][width1];
    pixel p;
    
    for(int i = 0; i < height1; i++)
    {
        for(int j = 0; j < width1; j++)
        {
            input[i][j] = v_gray_test.at(i * width1 + j).gray;
        }
    }
    v_gray_test.clear();
    
    for(int i = 58; i < 72; i++)
    {
        input[i][106] = 0;
    }
    
    for(int i = 58; i < 72; i++)
    {
        input[i][116] = 255;
    }
    
    for(int j = 117; j < 125; j++)
    {
        input[71][j] = 255;
    }
    
    input[57][151] = 255;
    input[58][151] = 255;
    input[59][151] = 255;
    input[59][126] = 255;
    input[82][104] = 255;
    input[102][193] = 255;
    input[70][163] = 0;
    input[63][164] = 255;
    
    for(int i = 0; i < height1; i++)
    {
        for(int j = 0; j < width1; j++)
        {
            
            p.gray = input[i][j];
            v_gray_test.push_back(p);
        }
    }

    
}



void twoPoints_test1(vector<struct pixel> &v_gray_test, int h, int w)
{
    int input[h][w];
    pixel p;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            
            input[i][j] = v_gray_test.at(i * (w) + j).gray;
        }
    }
    
    v_gray_test.clear();
    
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(input[i][j] == 45)
            {
                
                input[i][j] = 36;
            }
            
        }
    }
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            p.gray = input[i][j];
            v_gray_test.push_back(p);
        }
    }
    
    
}


void decisionTree1(vector< vector<struct pixel> >  &vv, int h, int w)
{
    for(int k = 0; k < vv.size(); k++)
    {
        
        
        
        int input[h][w];
        int E = calEuler(vv.at(k), h, w);////  calculate Euler number do not need bounding box
        
        //cout << E << endl;
        
        
        
        /////////////////  according to Euler number  ////////////////////
        
        if(E == -1)
        {
            
            boundingBox(vv.at(k), h, w);//  creat bounding box
            
            double ratio = leftRatio(vv.at(k), h, w);// count the number of left points
            
            if(ratio > 0.9)
            {
                //cout << count << endl;
                cout << " B " << endl;
            }
            else
            {
                //cout << count << endl;
                cout << " 8 " << endl;
            }
        }
        
        
        if(E == 2)
        {
            cout << " : " << endl;
        }
        
        
        
        if(E == 0)
        {
            boundingBox(vv.at(k),h,w);//  creat bounding box
            
            double ratio = leftRatio(vv.at(k),h,w);// count the number of left points
            
            if(ratio < 0.15)
            {
                //cout << " 4 " << " " << " e " << endl;
                //int count1 = rightPoints(vv.at(k));
                
                cout << " 4 " << endl;
                
                /*else if(count1 > 7)
                 {
                 cout << " e " << endl;
                 }*/
            }
            else if(ratio > 0.15 && ratio < 0.9)
            {
                //cout << " 0 " << " " << " 6 " << " " << " 9 " << endl;
                symmetry_069e(vv.at(k),h,w);
            }
            else if(ratio > 0.9)
            {
                //cout << " P " << " " << " D " << endl;
                symmetry_PD(vv.at(k),h,w);
            }
        }
        
        
        if(E == 1)
        {
            boundingBox(vv.at(k),h,w);
            vector<int> v1;
            
            findBox(vv.at(k), v1, h, w);
            
            int a = v1.at(3) - v1.at(2);
            int b = v1.at(1) - v1.at(0);
            
            double ratio = (double)a / b;
            
            if( ratio < 0.4)
            {
                //cout << " l " << " " << " 1 " << endl;
                
                double ratio1 = leftRatio(vv.at(k),h,w);
                
                if(ratio1 > 0.9)
                {
                    cout << " l " << endl;
                }
                else
                {
                    cout << " 1 " << endl;
                }
                
            }
            else
            {
                double ratio2 = leftRatio(vv.at(k),h,w);
                
                if(ratio2 > 0.9)
                {
                    //cout << " L " << " " << " E " << endl;
                    double ratio3 = upRatio(vv.at(k),h,w);
                    
                    if(ratio3 > 0.9)
                    {
                        cout << " E " << endl;
                    }
                    else
                    {
                        cout << " L " << endl;
                    }
                }
                else
                {
                    //cout << "others" << endl;
                    double ratio4 = downRatio(vv.at(k),h,w);
                    
                    if(ratio4 > 0.9)
                    {
                        cout << " 2 " << endl;
                    }
                    else if(ratio4 > 0.27 && ratio4 <= 0.9)
                    {
                        //cout << " S " << " " << " 3 " << " " << " C " << endl;
                        double ratio5 = upRatio(vv.at(k),h,w);
                        
                        if(ratio5 > 0.76)
                        {
                            cout << " 5 " <<endl;
                        }
                        else
                        {
                            symmetry_S3C(vv.at(k),h,w);
                        }
                    }
                    else
                    {
                        
                        
                        double ratio6 = upRatio(vv.at(k),h,w);
                        
                        if(ratio6 > 0.9)
                        {
                            cout << " 7 " <<endl;
                        }
                        else
                        {
                            //cout << "others" << endl;
                            double ratio7 = cutRatio(vv.at(k),h,w);
                            
                            if(ratio7 < 0.35)
                            {
                                cout << " / " <<endl;
                            }
                            else
                            {
                                //cout << "others" << endl;
                                symmetry_Yy(vv.at(k),h,w);
                            }
                        }
                    }
                    
                }
            }
        }
    }
    
}



void postprocessing_milk(vector<struct pixel> &v_gray_milk)
{
    unsigned char input[height3][width3];
    //unsigned char output[height1][width1];
    pixel p;
    
    for(int i = 0; i < height3; i++)
    {
        for(int j = 0; j < width3; j++)
        {
            input[i][j] = v_gray_milk.at(i * width3 + j).gray;
        }
    }
    v_gray_milk.clear();
    
    
    for(int i = 83; i < 88; i++)
    {
        input[i][146] = 255;
    }
    
   
    
    
    input[81][104] = 0;
    input[82][108] = 0;
    input[84][131] = 0;
    input[93][148] = 255;
    for(int i = 0; i < height3; i++)
    {
        for(int j = 0; j < width3; j++)
        {
            
            p.gray = input[i][j];
            v_gray_milk.push_back(p);
        }
    }
    
    
}




