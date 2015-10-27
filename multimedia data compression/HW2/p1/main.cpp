#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stack>
#include <bitset>
using namespace std;


void readFile(const char *fname, vector<unsigned char> &v);
void writeFile(const char *n_fname, vector<unsigned char> &v1);
void preprocessing(vector<unsigned char> &v, vector<bool> &bitVector);
void QMCoder(vector<bool> &bitVector, vector<bool> &newBitVector);
void renormalize(bool &carry, unsigned int &A, unsigned short &C, vector<bool> &newBitVector);
void changeBitToByte(vector<bool> &newBitVector, vector<unsigned char> &v1);
void changeByteToBit(vector<unsigned char> &v, vector<bool> &bitVector);
void showResults(unsigned int &A, unsigned short &C, unsigned int &Qe, int &curState, int &MPS);
void show(vector<bool> &newBitVector);
double compressionRatio(vector<unsigned char> &v, vector<unsigned char> &v1);


struct line
{
    int state;
    
    int Qe;
    
    int increState;
    
    int decreState;
    
};


line table[50] = {
    
    0, 0x59eb, 1, -1,
    
    1, 0x5522, 1, 1,
    
    2, 0x504f, 1, 1,
    
    3, 0x4b85, 1, 1,
    
    4, 0x4639, 1, 1,
    
    5, 0x415e, 1, 1,
    
    6, 0x3c3d, 1, 1,
    
    7, 0x375e, 1, 1,
    
    8, 0x32b4, 1, 2,
    
    9, 0x2e17, 1, 1,
    
    10, 0x299a, 1, 2,
    
    11, 0x2516, 1, 1,
    
    12, 0x1edf, 1, 1,
    
    13, 0x1aa9, 1, 2,
    
    14, 0x174e, 1, 1,
    
    15, 0x1424, 1, 2,
    
    16, 0x119c, 1, 1,
    
    17, 0x0f6b, 1, 2,
    
    18, 0x0d51, 1, 2,
    
    19, 0x0bb6, 1, 1,
    
    20, 0x0a40, 1, 2,
    
    21, 0x0861, 1, 2,
    
    22, 0x0706, 1, 2,
    
    23, 0x05cd, 1, 2,
    
    24, 0x04de, 1, 1,
    
    25, 0x040f, 1, 2,
    
    26, 0x0363, 1, 2,
    
    27, 0x02d4, 1, 2,
    
    28, 0x025c, 1, 2,
    
    29, 0x01f8, 1, 2,
    
    30, 0x01a4, 1, 2,
    
    31, 0x0160, 1, 2,
    
    32, 0x0125, 1, 2,
    
    33, 0x00f6, 1, 2,
    
    34, 0x00cb, 1, 2,
    
    35, 0x00ab, 1, 1,
    
    36, 0x008f, 1, 2,
    
    37, 0x0068, 1, 2,
    
    38, 0x004e, 1, 2,
    
    39, 0x003b, 1, 2,
    
    40, 0x002c, 1, 2,
    
    41, 0x001a, 1, 3,
    
    42, 0x000d, 1, 2,
    
    43, 0x0006, 1, 2,
    
    44, 0x0003, 1, 2,
    
    45, 0x0001, 0, 1

};











int main()
{
    
    vector<bool> bitVector;
    vector<bool> newBitVector;
    vector<unsigned char> v;
    vector<unsigned char> v1;
    
    
    /*bitVector.push_back(1);
    bitVector.push_back(1);
    bitVector.push_back(0);
    bitVector.push_back(0);
    bitVector.push_back(0);
    bitVector.push_back(1);
    bitVector.push_back(0);
    bitVector.push_back(0);
    bitVector.push_back(1);
    bitVector.push_back(0);
    cout << endl;
    cout<< "vauleOfA  " << "valueOfC  " << "valueOfQe  " << "state  " << "MPS " << endl;
    
    QMCoder(bitVector, newBitVector);
    cout<< endl;
    cout << "bitstream : " << endl;
    show(newBitVector);
    cout << endl << endl;*/
    
    
    
    const char *fname = "text.dat";
    const char *n_fname = "n_text.dat";
    double ratio;
    
    readFile(fname, v);
    preprocessing(v, bitVector);
    //changeByteToBit(v, bitVector);
    QMCoder(bitVector, newBitVector);
    changeBitToByte(newBitVector, v1);
    writeFile(n_fname, v1);
    ratio = compressionRatio(v, v1);
    cout << v.size() << " " << v1.size() << endl;
    cout << ratio << endl;
}





















void readFile(const char *fname, vector<unsigned char> &v)
{
    streampos size;
    unsigned char * memory;
    
    ifstream file (fname, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memory = new unsigned char [size];
        file.seekg (0, ios::beg);
        file.read ((char *)memory, size);
        file.close();
    }
    
    for(int i = 0; i < size; i++)
    {
        //cout << (int)(memblock[i]) << " ";
        v.push_back((memory[i]));
    }
}



void changeByteToBit(vector<unsigned char> &v, vector<bool> &bitVector)
{
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 7; j >= 0; j--)
        {
            bool b = v.at(i) & (1 << j);
            
            if(b == 0)
            {
                bitVector.push_back(0);
            }
            else
            {
                bitVector.push_back(1);
            }

        }
    }
}

void preprocessing(vector<unsigned char> &v, vector<bool> &bitVector)
{
    
    for(int j = 7; j >= 0; j--)
    {
        for(int i = 0; i < v.size(); i++)
        {
            bool b = v.at(i) & (1 << j);
                      
            if(b == 0)
            {
                bitVector.push_back(0);
            }
            else
            {
                bitVector.push_back(1);
            }
        }
    }
}




void QMCoder(vector<bool> &bitVector, vector<bool> &newBitVector)
{
    int MPS = 0;
    int LPS = 1;
    
    unsigned int A = 0x10000;
    unsigned short C = 0x0000;
    int curState = 10;
    bool carry = false;
    unsigned int Qe = table[curState].Qe;
    int temp;
    
    
    
    for(int i = 0; i < bitVector.size(); i++)
    {
        
        
        
        if(bitVector.at(i) == MPS)
        {
            
            A = A - Qe;
            
            if(A < 0x8000)
            {
                
                if(A < Qe)
                {
                    
                    if((C + A) > 0xFFFF)
                    {
                        carry = true;
                    }
                    
                    C += A;
                    
                    A = Qe;
                }
                
                curState += table[curState].increState;
                
                Qe = table[curState].Qe;
                
                renormalize(carry, A, C, newBitVector);
                
                
            }
            
            //showResults(A, C, Qe, curState, MPS);
        }
        else if(bitVector.at(i) == LPS)
        {
            
            
            A = A - Qe;
            
            if(A >= Qe)
            {
                if((C + A) > 0xFFFF)
                {
                    carry = true;
                }
                
                C += A;
                
                A = Qe;
            }
            
            
            if(curState == 0)
            {
                temp = MPS;
                MPS = LPS;
                LPS = temp;
            }
            else
            {
                curState -= table[curState].decreState;
                Qe = table[curState].Qe;
            }
            
            
            
            renormalize(carry, A, C, newBitVector);
            
            
            
            //showResults(A, C, Qe, curState, MPS);
        }
    }
}





void renormalize(bool &carry, unsigned int &A, unsigned short &C, vector<bool> &newBitVector)
{
    if(carry == true)
    {
        newBitVector.push_back(1);
        carry = false;
    }
    
    
    while(A < 0x8000)
    {
        A <<= 1;
        
        //cout << "111111111111111" << endl;
        bool b = C & (1 << 15);
        
        if(b == 0)
        {
            newBitVector.push_back(0);
        }
        else
        {
            newBitVector.push_back(1);
        }
        
        C <<= 1;
        
    }
}



void changeBitToByte(vector<bool> &newBitVector, vector<unsigned char> &v1)
{
    int h = newBitVector.size() / 8;
    
    bool arr[h][8];
    
    unsigned char b;
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            arr[i][j] = newBitVector.at(i * 8 + j);
        }
    }
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            b += arr[i][j] * (1 << (7 - j));
            
            if(j == 7)
            {
                v1.push_back(b);
                b = 0;
            }
        }
    }
}



void writeFile(const char *n_fname, vector<unsigned char> &v1)
{
    FILE *file;
    unsigned char output[v1.size()];
    
    for(int i = 0; i < v1.size(); i++)
    {
        output[i] = v1.at(i);
    }
    
    if (!(file = fopen(n_fname,"wb")))
    {
        cout << "Cannot open file: " << n_fname << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), v1.size(), file);
    fclose(file);
    
    
}



void showResults(unsigned int &A, unsigned short &C, unsigned int &Qe, int &curState, int &MPS)
{
    cout << hex << A << "       " << hex << C << "      " << hex << Qe << "       " << curState << "      " << MPS << endl;
}


void show(vector<bool> &newBitVector)
{
    for(int i = 0; i < newBitVector.size(); i++)
    {
        cout << newBitVector.at(i);
    }
}


double compressionRatio(vector<unsigned char> &v, vector<unsigned char> &v1)
{
    double ratio;
    
    ratio = ((double)v1.size()) / v.size();
    
    return ratio;
}







