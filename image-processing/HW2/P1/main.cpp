#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;



void readFile(const char *r_fileName, vector<unsigned char> &v);
void enlarge(vector<unsigned char> &v);
void writeFile(const char *n_fileName, vector<unsigned char> &v);
void x_gradient(vector<unsigned char> &v);
void histogram(const char *fName, vector<unsigned char> &v);
void y_gradient(vector<unsigned char> &v);
int find_min(vector<int> &v);
int find_max(vector<unsigned char> &v);
void normalization(vector<int> &v);
void combi_gradient(vector<unsigned char> &v);
void threadhold(vector<unsigned char> &v, float t1, float t2);






int width = 256;
int height = 256;
int BytesPerPixel = 1;
int len = 3;
int n = (int)(len / 2);
int wsize = len * len;





int main()
{
    
    
    const char *r_fileName = "elaine.raw";
    const char *x_fileName = "elaine_x.raw";
    const char *y_fileName = "elaine_y.raw";
    const char *combi_fileName = "elaine_combi.raw"; 
    const char *edge_fileName = "elaine_edge.raw";
    const char *r1_fileName = "noisy_elaine.raw";
    const char *x1_fileName = "elaine_x1.raw";
    const char *y1_fileName = "elaine_y1.raw";
    const char *combi1_fileName = "elaine_combi1.raw";
    const char *edge1_fileName = "elaine_edge1.raw";
    vector<unsigned char> v;
    int i;
    
    
    
    readFile(r_fileName, v);
    enlarge(v);
    
    cout << " input you choise" << endl;
    cout << " 1. x_gradient." << endl;
    cout << " 2. y_gradient." << endl;
    cout << " 3. combination_gradient." << endl;
    cout << " 4. obtain a edge map." << endl;
    cin >> i;
    if(i == 1)
    {
        x_gradient(v);
        writeFile(x1_fileName, v);
        histogram("noisy_his_xxx.txt",v);
    }
    else if(i == 2)
    {
        y_gradient(v);
        writeFile(y1_fileName, v);
        histogram("noisy_his_yyy.txt",v);
    }
    else if(i == 3)
    {
        combi_gradient(v);
        writeFile(combi1_fileName, v);
        histogram("noisy_his_ccc.txt",v);
    }
    else if(i == 4)
    {
        combi_gradient(v);
        threadhold(v, 0.929, 0.93);
        writeFile(edge_fileName, v);
        histogram("noisy_his_edge.txt",v);
    }
    
}




void readFile(const char *r_fileName, vector<unsigned char> &v)
{
    
    
    FILE *file;
    unsigned char s_Data[height][width];
    unsigned char temp;
    
    
    
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
            
            temp = s_Data[i][j];
            v.push_back(temp);
        }
    }
}




void histogram(const char *fName, vector<unsigned char> &v)
{
    int count[256] = {0};
    
   
    
    ////////////count the number of pixels in each scale//////////
    
    for(int i = 0; i < height * width; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            
            if(v.at(i) == j)
            {
                count[j]++;
            }
        }
        
    }
    
    /////////////write in txt file//////////////////////
    FILE *file;
    for(int j = 0; j < BytesPerPixel; j++)
    {
        if((file = fopen(fName, "wb")) != NULL)
        {
            for(int i = 0; i < 256; i++)
            {
                fprintf(file, "%d ", count[i]);
            }
        }
        fclose(file);
    }
}




void writeFile(const char *n_fileName, vector<unsigned char> &v)
{
   
    FILE *file;
    unsigned char out[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out[i][j] = v.at(i * width + j);
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




void enlarge(vector<unsigned char> &v)
{
    
    unsigned char a[height][width];
    unsigned char c[height + 2 * n][width + 2 * n];
    unsigned char b[height + 2 * n][width];
    //pixel p;
    unsigned char temp;
    
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            a[i][j] = v.at(i * width + j);
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
           
            temp = c[i][j];
            v.push_back(temp);
        }
    }
    
    
}




void x_gradient(vector<unsigned char> &v)
{
    unsigned char a[height + 2 * n][width + 2 * n];
    int out[height + 2 * n][width + 2 * n];
    //int sobel[3][3] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int i, j;
    vector<int> v1;
    
    for(i = 0; i < height + 2 * n; i++)
    {
        for(j = 0; j < width + 2 * n; j++)
        {
            a[i][j]= v.at(i * (width + 2 * n) + j);
        }
    }

    
    v.clear();
    
    
    for(i = 1; i < height + 1; i++)
    {
        for(j = 1; j < width + 1; j++)
        {

            out[i][j] = (a[i - 1][j + 1] + 2 * a[i][j + 1] + a[i + 1][j + 1]) - (a[i - 1][j - 1] + 2 * a[i][j - 1] + a[i + 1][j - 1]);
            
            v1.push_back(out[i][j]);
        }
    }
    
    
    
    
    normalization(v1);
    
    
    for(i = 0; i < height * width; i++)
    {
        
        v.push_back(v1.at(i));
        
    }
    
    v1.clear();
}




void y_gradient(vector<unsigned char> &v)
{
    unsigned char a[height + 2 * n][width + 2 * n];
    int out[height + 2 * n][width + 2 * n];
    //int sobel[3][3] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int i, j;
    vector<int> v1;
    
    
    
    for(i = 0; i < height + 2 * n; i++)
    {
        for(j = 0; j < width + 2 * n; j++)
        {
            a[i][j]= v.at(i * (width + 2 * n) + j);
        }
    }
    
    v.clear();
    
    for(i = 1; i < height + 1; i++)
    {
        for(j = 1; j < width + 1; j++)
        {
            
            out[i][j] = (a[i - 1][j - 1]+ a[i - 1][j] * 2 + a[i - 1][j + 1]) - (a[i + 1][j - 1] + a[i + 1][j] * 2 + a[i + 1][j + 1]);
            
            v1.push_back(out[i][j]);
        }
    }
    
    normalization(v1);
    
    
    for(i = 0; i < height * width; i++)
    {
        
        v.push_back(v1.at(i));
        
    }
    
    v1.clear();
}




void combi_gradient(vector<unsigned char> &v)
{
    
    
    unsigned char a[height + 2 * n][width + 2 * n];
    int x[height + 2 * n][width + 2 * n];
    int y[height + 2 * n][width + 2 * n];
    int combi[height + 2 * n][width + 2 * n];
    int i, j;
    vector<int> v1;
    
    
    
    for(i = 0; i < height + 2 * n; i++)
    {
        for(j = 0; j < width + 2 * n; j++)
        {
            a[i][j]= v.at(i * (width + 2 * n) + j);
        }
    }
    
    v.clear();
    
    for(i = 1; i < height + 1; i++)
    {
        for(j = 1; j < width + 1; j++)
        {
            
            x[i][j] = (a[i - 1][j + 1] + 2 * a[i][j + 1] + a[i + 1][j + 1]) - (a[i - 1][j - 1] + 2 * a[i][j - 1] + a[i + 1][j - 1]);
            
            y[i][j] = (a[i - 1][j - 1]+ a[i - 1][j] * 2 + a[i - 1][j + 1]) - (a[i + 1][j - 1] + a[i + 1][j] * 2 + a[i + 1][j + 1]);
            
            combi[i][j] = sqrt(x[i][j] * x[i][j] + y[i][j] * y[i][j]);
            
            v1.push_back(combi[i][j]);
        }
    }
    
    
    normalization(v1);
    
    
    for(i = 0; i < height * width; i++)
    {
        
        v.push_back(v1.at(i));
        
    }
    
    v1.clear();
}




int find_max(vector<int> &v)
{
    int max;
    max = v.at(0);
    
    for(int i = 1; i < height * width; i++)
    {
        if(max < v.at(i))
        {
            max = v.at(i);
        }
    }
    
    return max;
}




int find_min(vector<int> &v)
{
    int min;
    min = v.at(0);
    
    for(int i = 1; i < height * width; i++)
    {
        if(min > v.at(i))
        {
            min = v.at(i);
        }
    }
    
    return min;
}




void normalization(vector<int> &v)
{
    int max, min;
    max = find_max(v);
    min = find_min(v);
   
    for(int i = 0; i < height * width; i++)
    {
        v.at(i) = ((v.at(i) - min) * 255) / (max - min);
    }
    
}




void threadhold(vector<unsigned char> &v, float t1, float t2)
{
    
    
    int count[256] = {0};
    int integer[256] = {0};
    int thread = 0, i;
    ////////////count the number of pixels in each scale//////////
    
    for(i = 0; i < height * width; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            if(v.at(i) == j)
            {
                count[j]++;
            }
        }
        
    }
    
    integer[0] = count[0];
    
    ///////cumulative //////////
    
    for(i = 1; i < 256; i++)
    {
        integer[i] = integer[i - 1] + count[i];
    }
    
    ///////find a threadhold ////////
    
    for(i = 1; i < 256; i++)
    {
        if( integer[i] >= (int)(height * width * t1) && integer[i] <= (int)(height * width * t2))
        {
            cout << " find a threadhold!!!!!" << endl;
            thread = i;
            cout << i << endl;
        }
    }
    
    ////process////////
    
    for(i = 0; i < height * width; i++)
    {
        if(v.at(i) <= thread)
        {
            v.at(i) = 0;
        }
        else
        {
            v.at(i) = 255;
        }
    }

}


