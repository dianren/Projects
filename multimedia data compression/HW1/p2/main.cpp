#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stack>
using namespace std;




typedef struct node
{
    double frequency;
    int count;
    int value;
    int parent;
    int leftchild;
    int rightchild;
    string code;
}treenode;



struct symbol{
    double frequency;
    int value;
    int count;
    string code;
};






void cal_frequency(vector<int> &v, vector<struct symbol> &v1);
void readFile(const char *fname, vector<int> &v);
double cal_entropy(vector<struct symbol> &v1);
void sorting(vector<struct symbol> &v1);
void encodeShannon(vector<struct symbol> &v1);
void printSymbol(vector<struct symbol> &v1);
void findTwoMin(treenode *huffmanTree, int size, int *node1, int *node2);
void sortingAsending(vector<struct symbol> &v1);
void genCode(vector<struct symbol> &v1, treenode *huffmanTree);
void makeHuffmanTree(vector<struct symbol> &v1, treenode *huffmanTree);
void showHuffmanCode(vector<struct symbol> &v1, treenode *huffmanTree);






#define TOTALSIZE 256
#define NODESIZE 511




treenode huffmanTree[NODESIZE];
//int frequency[TOTALSIZE];

int main()
{
    
    const char *fname = "text.dat";
    vector<int> v;
    vector<struct symbol> v1;
    double entropy;
    
    readFile(fname, v);
    cal_frequency(v,v1);
    entropy = cal_entropy(v1);
    cout<<entropy<<endl;
    
    ////// shannon-fano coding //////////
    
    //sorting(v1);
    //encodeShannon(v1);
    //printSymbol(v1);
    
    
    //////// huffman coding /////////////
    /*sortingAsending(v1);
    printSymbol(v1);
    makeHuffmanTree(v1, huffmanTree);
    genCode(v1, huffmanTree);
    showHuffmanCode(v1, huffmanTree);*/
    
    
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


void cal_frequency(vector<int> &v, vector<struct symbol> &v1)
{
    struct symbol s;
    
    for(int i = 0; i < 256; i++)
    {
        int count = 0;
        
        for(int j = 0; j < v.size(); j++)
        {
            if(v.at(j) == i)
            {
                count++;
            }
        }
        
        if(count != 0)
        {
            double fre = (double)count / v.size();
            
            s.count = count;
            s.frequency = fre;
            s.value = i;
        
            v1.push_back(s);
        }
        
    }

}


double cal_entropy(vector<struct symbol> &v1)
{
    double entropy = 0;
    
    for(int i = 0; i < v1.size(); i++)
    {
        entropy += v1.at(i).frequency * log2(v1.at(i).frequency);
    }
    
    return (-entropy);
}


void sorting(vector<struct symbol> &v1)
{
    double temp1;
    int temp2;
    
    for(int i = 0; i < v1.size(); i++)
    {
        for(int j = 1; j < v1.size() - i; j++)
        {
            if(v1.at(j - 1).frequency < v1.at(j).frequency)
            {
                temp1 = v1.at(j - 1).frequency;
                temp2 = v1.at(j - 1).value;
                v1.at(j - 1).frequency = v1.at(j).frequency;
                v1.at(j - 1).value = v1.at(j).value;
                v1.at(j).frequency = temp1;
                v1.at(j).value = temp2;
            }
        }
    }
}


void encodeShannon(vector<struct symbol> &v1)
{
    
    vector<struct symbol> leftv1;
    vector<struct symbol> rightv1;
    
    //// if only one symbol, it is the leaf//////
    
    if(v1.size() <= 1)
    {
        printSymbol(v1);
        return;
    }
    else if(v1.size() == 2)///if only two, one to left, one to right.
    {
        v1.at(0).code += '0';
        v1.at(1).code += '1';
        
        leftv1.push_back(v1.at(0));
        rightv1.push_back(v1.at(1));
        v1.clear();
        encodeShannon(leftv1);
        encodeShannon(rightv1);
    }
    else
    {
        double fresum = 0;
        
        ////calculate the totally frequency.
        
        for(int i = 0; i < v1.size(); i++)
        {
            fresum += v1.at(i).frequency;
        }
        
        /// find the center ////
        
        double fre = 0;
        double frehalf = fresum * 0.5;
        int splitpoint = -1;// index of split position
        
        for(int i = 0; i < v1.size(); i++)
        {
            fre += v1.at(i).frequency;
            if(fre <= frehalf)
            {
                v1.at(i).code += '0';
            }
            else
            {
                ///special case, if A = 0.7 > 0.5, then all should be '1'.
                
                if(i == 0)
                {
                    v1.at(i).code += '0';
                    i = i + 1;
                }
                
                v1.at(i).code += '1';
                
                if(splitpoint < 0)
                {
                    splitpoint = i;
                }
            }
        }
        
        ///split this vector to two vectors/////
        
        
        for(int i = 0; i < splitpoint; i++)
        {
            leftv1.push_back(v1.at(i));
        }
        
        for(int i = splitpoint; i < v1.size(); i++)
        {
            rightv1.push_back(v1.at(i));
        }
        
        v1.clear();// release the original vector
        
        ////  Next, just need to recursive.  ///////
        
        encodeShannon(leftv1);
        encodeShannon(rightv1);
        
    }
        
}


void printSymbol(vector<struct symbol> &v1)
{
    for(int i = 0; i < v1.size(); i++)
    {
        cout << "Symbol: " << v1.at(i).value << "   frequency: " << v1.at(i).frequency << "     code: " << v1.at(i).code << endl;
    }
}


void sortingAsending(vector<struct symbol> &v1)
{
    double temp1;
    int temp2, temp3;
    
    for(int i = 0; i < v1.size(); i++)
    {
        for(int j = 1; j < v1.size() - i; j++)
        {
            if(v1.at(j - 1).frequency > v1.at(j).frequency)
            {
                temp1 = v1.at(j).frequency;
                temp2 = v1.at(j).value;
                temp3 = v1.at(j).count;
                v1.at(j).frequency = v1.at(j - 1).frequency;
                v1.at(j).value = v1.at(j - 1).value;
                v1.at(j).count = v1.at(j - 1).count;
                v1.at(j - 1).frequency = temp1;
                v1.at(j - 1).value = temp2;
                v1.at(j - 1).count = temp3;
            }
        }
    }
}


void makeHuffmanTree(vector<struct symbol> &v1, treenode *huffmanTree)
{
    
    
    for(int i = 0; i < v1.size(); i++)
    {
        huffmanTree[i].value = v1.at(i).value;
        huffmanTree[i].frequency = v1.at(i).frequency;
        huffmanTree[i].count = v1.at(i).count;
    }
    
    
    
    
    int node1 = 0, node2 = 1;
    
    for(int i = v1.size(); i < NODESIZE; i++)
    {
        findTwoMin(huffmanTree, i, &node1, &node2);
        
        //cout << i << " " << node1 << " " << node2 << endl;
        huffmanTree[i].count = huffmanTree[node1].count + huffmanTree[node2].count;
        huffmanTree[i].frequency = huffmanTree[node1].frequency + huffmanTree[node2].frequency;
        huffmanTree[node1].parent = i;
        huffmanTree[node2].parent = i;
        huffmanTree[i].leftchild = node1;
        huffmanTree[i].rightchild = node2;
        
    }
}


void findTwoMin(treenode *huffmanTree, int size, int *node1, int *node2)
{
    int min1 = INT_MAX, min2 = INT_MAX;
    
    /*if(huffmanTree[0].frequency < huffmanTree[1].frequency)
    {
        min1 = huffmanTree[0].frequency;
        min2 = huffmanTree[1].frequency;
        *node1 = 0;
        *node2 = 1;
    }
    else
    {
        min1 = huffmanTree[1].frequency;
        min2 = huffmanTree[0].frequency;
        *node1 = 1;
        *node2 = 0;
    }*/
    
    for(int i = 0; i < size; i++)
    {
        //cout << "wwwwwwwwwwwwwwwww" << endl;
        if(huffmanTree[i].count < min2 && huffmanTree[i].count != 0 && huffmanTree[i].parent == 0)
        {
            if(huffmanTree[i].count < min1)
            {
                
                min2 = min1;
                min1 = huffmanTree[i].count;
                *node2 = *node1;
                *node1 = i;
            }
            else
            {
                min2 = huffmanTree[i].count;
                *node2 = i;
            }
            //cout << "wwwwwwwwwwwwwwwww" << endl;
        }
        
    }
    
    //cout << "wwwwwwwwwwwwwwwww" << endl;
    //cout << *node1 << " " << *node2<< endl;
}



void genCode(vector<struct symbol> &v1, treenode *huffmanTree)
{
    
    /*for(int i = v1.size(); i < NODESIZE; i++)
    {
        //cout << huffmanTree[i].frequency << endl;
    }*/
    
    
    int parent_position, child_position;
    stack<char> s_code;
    
    for(int i = 0; i < v1.size(); i++)
    {
        parent_position = huffmanTree[i].parent;
        child_position = i;
        
        while(parent_position != 0)
        {
            if(child_position == huffmanTree[parent_position].leftchild)
            {
                s_code.push('0');
            }
            else
            {
                s_code.push('1');
            }
            
            
            //cout << "wwwwwwwwwwwwwwww"<<endl;
            child_position = parent_position;
            parent_position = huffmanTree[parent_position].parent;
        }
        
        while(!s_code.empty())
        {
            huffmanTree[i].code += s_code.top();
            //cout<< s_code.top()<<endl;;
            s_code.pop();
        }
        
        //cout << "wwwwwwwwwwwwwwww"<<endl;
    }
}



void showHuffmanCode(vector<struct symbol> &v1, treenode *huffmanTree)
{
    for(int i = 0; i < v1.size(); i++)
    {
        cout << "Symbol: " << huffmanTree[i].value;
        cout << "   frequency: " << huffmanTree[i].frequency;
        cout << "     code: " << huffmanTree[i].code << endl;
    }
}






















