#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stack>
using namespace std;




void readFile(const char *fname, vector<int> &v);
void encode(vector<int> &v, vector<int> &temp);
void writeFile(const char *n_fname, vector<int> &temp);
void decode(vector<int> &temp, vector<int> &v);
void modifiedEncode(vector<int> &v, vector<int> &temp);




int main()
{
    const char *fname = "binary.dat.raw";
    const char *n_fname = "n_image.dat.raw";
    const char *nn_fname = "nnnnn_image.dat.raw";
    vector<int> v;
    vector<int> temp;
    
    /*for(int i = 0; i < 10; i++)
    {
        v.push_back(4);
        v.push_back(5);
    }*/
    v.push_back(7);
    v.push_back(7);
    v.push_back(7);
    v.push_back(5);
    v.push_back(4);
    v.push_back(158);
    v.push_back(3);
    v.push_back(3);
    v.push_back(2);
    
////////////p1  /////////////////
    
    /*readFile(fname, v);
    encode(v, temp);
    writeFile(n_fname, temp);
    temp.clear();
    readFile(n_fname, temp);
    decode(temp, v);
    writeFile(nn_fname, v);*/
    
//////////// p2 /////////////////
    
    modifiedEncode(v, temp);
    
}







void readFile(const char *fname, vector<int> &v)
{
    streampos size;
    unsigned char * memblock;
    
    ifstream file (fname, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new unsigned char [size];
        file.seekg (0, ios::beg);
        file.read ((char *)memblock, size);
        file.close();
    }
    
    for(int i = 0; i < size; i++)
    {
        //cout << (int)(memblock[i]) << " ";
        v.push_back((int)(memblock[i]));
    }
}


void encode(vector<int> &v, vector<int> &temp)
{
   
    int last = v.at(0);
    int count = 1;
    
    for(int i = 1; i < v.size(); i++)
    {
        if(v.at(i) == last && count <= 256)
        {
            count++;
        }
        else
        {
            temp.push_back(count);
            temp.push_back(last);
            last = v.at(i);
            count = 1;
        }
    }
    temp.push_back(count);
    temp.push_back(last);
    
    
    //cout << v.size() << " " << temp.size();
    
    v.clear();
    /*for(int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
    for(int i = 0; i < temp.size(); i++)
    {
        cout << temp.at(i)<< " ";
    }
    cout << endl;*/
}



void decode(vector<int> &temp, vector<int> &v)
{
    for(int i = 0; i < temp.size(); i++)
    {
        for(int j = 0; j < temp.at(i); j++)
        {
            v.push_back(temp.at(i + 1));
        }
        i++;
    }
    
    cout << temp.size() << " " << v.size() << endl;
    /*for(int i = 0; i < v.size(); i++)
     {
     cout << v.at(i) << " ";
     }
     cout << endl;
     for(int i = 0; i < temp.size(); i++)
     {
     cout << temp.at(i)<< " ";
     }
     cout << endl;*/
}

void writeFile(const char *n_fname, vector<int> &temp)
{
    FILE *file;
    unsigned char output[temp.size()];
    
    for(int i = 0; i < temp.size(); i++)
    {
        output[i] = (unsigned char)temp.at(i);
    }
    
    if (!(file = fopen(n_fname,"wb")))
    {
        cout << "Cannot open file: " << n_fname << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), temp.size(), file);
    fclose(file);
    
    
}




void modifiedEncode(vector<int> &v, vector<int> &temp)
{
    int last = v.at(0);
    int count = 129;
    
    for(int i = 1; i < v.size(); i++)
    {
        if(v.at(i) == last && count <= 256)
        {
            count++;
        }
        else
        {
            if(count > 129)
            {
                temp.push_back(count);
                temp.push_back(last);
            }
            
            if(i != (v.size() - 1) && v.at(i) != v.at(i + 1) && v.at(i) != last)
            {
                if(v.at(i) >= 128)
                {
                    temp.push_back(129);
                    temp.push_back(v.at(i));
                }
                else
                {
                    temp.push_back(v.at(i));
                }

            }
            if(i == (v.size() - 1) && v.at(i) != last)
            {
                if(v.at(i) >= 128)
                {
                    temp.push_back(129);
                    temp.push_back(v.at(i));
                }
                else
                {
                    temp.push_back(v.at(i));
                }
                
            }
            
            last = v.at(i);
            count = 129;
        }
        
    }
    if(count > 129)
    {
        temp.push_back(count);
        temp.push_back(last);
    }
    
    
    for(int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
    for(int i = 0; i < temp.size(); i++)
    {
        cout << temp.at(i)<< " ";
    }
    cout << endl;
}







































