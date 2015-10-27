#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;



void readFile(const char *fname, vector<unsigned char> &v);
void getTogether(vector<unsigned char> &v1, vector<unsigned char> &v2, vector<unsigned char> &v3, vector<unsigned char> &vsum);
void histogram(vector<unsigned char> &v, vector<struct cell> &number, const char *textFile);
int findMax(vector<unsigned char> &v);
int findMin(vector<unsigned char> &v);
void uniformInitialization(vector<unsigned char> &v, vector<double> &tk, vector<double> &rk);
int getTotalPixels(vector<struct cell> &number);
double getPSNR(double &MSE);
double getMSE(vector<struct cell> &number, int &totalPixels, vector<double> &tk, vector<double> &rk);
void updateRkTk(vector<struct cell> &number, int &totalPixels, vector<double> &tk, vector<double> &rk);
int iteration(vector<struct cell> &number, int &totalPixels, vector<double> &tk, vector<double> &rk);
void reportPSNR(double &PSNR, int &counter);







///// cell: means at this value, what the number of pixels this value has./////////
struct cell
{
    int count;
    int value;
};










int LUMIN = 256;
int L = 32;
int MAX = 255;
double EBIXILONG = 0.001;



int main()
{
    
    const char *fname1 = "chem.256";
    const char *fname2 = "house.256";
    const char *fname3 = "moon.256";
    const char *fname4 = "f16.256";
    const char *fname5 = "couple.256";
    const char *fname6 = "elaine.256";
    const char *textFile = "histogramSum.txt";
    
    vector<unsigned char> v1;
    vector<unsigned char> v2;
    vector<unsigned char> v3;
    vector<unsigned char> v4;
    vector<unsigned char> v5;
    vector<unsigned char> v6;
    vector<unsigned char> vsum;
    vector<struct cell> number;
    
    vector<double> tk;
    vector<double> rk;
    
    int totalPixels;
    
    
    
    
    //readFile(fname1, v1);
    //readFile(fname2, v2);
    //readFile(fname3, v3);
    //readFile(fname4, v4);
    //readFile(fname5, v5);
    //readFile(fname6, v6);
    //getTogether(v1, v2, v3, vsum);
    
    //histogram(v6, number, textFile);
    /*uniformInitialization(vsum, tk, rk);
    totalPixels = getTotalPixels(number);
    cout<< totalPixels << endl;
    iteration(number, totalPixels, tk, rk);*/
    
    cout<<endl;
    report();
    cout<<endl;
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


void getTogether(vector<unsigned char> &v1, vector<unsigned char> &v2, vector<unsigned char> &v3, vector<unsigned char> &vsum)
{
    int i;
    
    for(i = 0; i < v1.size(); i++)
    {
        vsum.push_back(v1.at(i));
    }
    
    for(i = 0; i < v2.size(); i++)
    {
        vsum.push_back(v2.at(i));
    }

    for(i = 0; i < v3.size(); i++)
    {
        vsum.push_back(v3.at(i));
    }

    
}


void histogram(vector<unsigned char> &v, vector<struct cell> &number, const char *textFile)
{
    int count[LUMIN];
    FILE *file;
    cell c;
    
    for(int i = 0; i < LUMIN; i++)
    {
        count[i] = 0;
    }
    
    
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < LUMIN; j++)
        {
            if(v.at(i) == j)
            {
                count[j]++;
            }
            
            
        }
    }
    
    for(int i = 0; i < LUMIN; i++)
    {
        c.value = i;
        c.count = count[i];
        number.push_back(c);
        
        
    }
    
    
    
    
    if((file = fopen(textFile, "wb")) != NULL)
    {
        for(int i = 0; i < LUMIN; i++)
        {
            fprintf(file, "%d ", count[i]);
        }
    }
    fclose(file);
    
}


/*void cumulativeEqualization(vector<unsigned char> &v, vector<int> &number)
{
    int integer[LUMIN];
    
    integer[0] = number.at(0);
    
    for(int i = 1; i < LUMIN; i++)
    {
        integer[i] = integer[i - 1] + number.at(i);
    }
    
    
}*/


void uniformInitialization(vector<unsigned char> &v, vector<double> &tk, vector<double> &rk)
{
    int min, max, i;
    double dif;
    double r[L];
    double t[L + 1];
    
    min = findMin(v);
    max = findMax(v);
    
    //cout << min << " " << max << endl;
    
    t[0] = min;
    t[L] = max;
    
    dif = (double)(max - min) / L;
    
    for(i = 1; i < L; i++)
    {
        t[i] = t[i - 1] + dif;
    }
    
    for(i = 0; i < L; i++)
    {
        r[i] = (t[i] + t[i + 1]) / 2;
    }
    
    for(i = 0; i < L; i++)
    {
        rk.push_back(r[i]);
    }
    
    for(i = 0; i < L + 1; i++)
    {
        tk.push_back(t[i]);
        //cout << t[i] << endl;
    }
    
}


int findMax(vector<unsigned char> &v)
{
    int max = v.at(0);
    
    for(int i = 1; i < v.size(); i++)
    {
        if(max < v.at(i))
        {
            max = v.at(i);
        }
    }
    
    return max;
}



int findMin(vector<unsigned char> &v)
{
    int min = v.at(0);
    
    for(int i = 1; i < v.size(); i++)
    {
        if(min > v.at(i))
        {
            min = v.at(i);
        }
    }
    
    return min;
}



int getTotalPixels(vector<struct cell> &number)
{
    int total = 0;
    //cout << number.size() << endl;
    
    for(int i = 0; i < number.size(); i++)
    {
        total += number.at(i).count;
        
    }
    
    return total;
}






double getMSE(vector<struct cell> &number, int &totalPixels, vector<double> &tk, vector<double> &rk)
{
    double MSE;
    double mse;
    vector<struct cell> number1;
    int i, j;
    cell temp;
    
    for(i = 0; i < L; i++)
    {
        for(j = 0; j < LUMIN; j++)
        {
            if(number.at(j).value >= tk.at(i) && number.at(j).value <= tk.at(i + 1))
            {
                //p = (double)number.at(j).count / totalPixels;
                //mse += (number.at(j).value - rk.at(i)) * (number.at(j).value - rk.at(i)) * p;
                temp.value = (int)rk.at(i);
                temp.count = number.at((int)rk.at(i)).count;
                number1.push_back(temp);
            }
            
        }
    }
    
    for(int i = 0; i < LUMIN; i++)
    {
        MSE += pow(number1.at(i).count - number.at(i).count, 2);
    }
    
    return MSE / totalPixels;
    
}


double getPSNR(double &MSE)
{
    double PSNR;
    
    PSNR = 10 * log10 ((MAX * MAX) / MSE);
    
    return PSNR;
    
}



void updateRkTk(vector<struct cell> &number, int &totalPixels, vector<double> &tk, vector<double> &rk)
{
    
    int i, j;
    double p, a, b;
    
    
    
    for(i = 1; i < L; i++)
    {
        for(j = 0; j < LUMIN; j++)
        {
            if(number.at(j).value >= tk.at(i) && number.at(j).value <= tk.at(i + 1))
            {
                p = (double)number.at(j).count / totalPixels;
                a += number.at(j).value * p;
                b += p;
            }
        }
        
        rk.at(i) = a / b;
        
        tk.at(i) = (rk.at(i) + rk.at(i - 1)) / 2;
        
        
    }
    
    
}


int iteration(vector<struct cell> &number, int &totalPixels, vector<double> &tk, vector<double> &rk)
{
    double preMSE, MSE, PSNR;
    int counter = 1;
    
    

    /////// first iteration ////////////////////
    
    preMSE = getMSE(number, totalPixels, tk, rk);
    
    updateRkTk(number, totalPixels, tk, rk);
    
    MSE = getMSE(number, totalPixels, tk, rk);
    
    PSNR = getPSNR(MSE);
    
    reportPSNR(PSNR, counter);
    
    
    //cout << preMSE << " " << MSE << endl;
    
/////////////// second and further iteration //////////////////
    
    while(abs(((preMSE - MSE) / MSE)) >= EBIXILONG)
    {
        preMSE = MSE;
        
        updateRkTk(number, totalPixels, tk, rk);
        
        MSE = getMSE(number, totalPixels, tk, rk);
        
        PSNR = getPSNR(MSE);
        
        counter++;
        
        reportPSNR(PSNR, counter);
    }
    
    return counter;
}


void reportPSNR(double &PSNR, int &counter)
{
    cout << "Iteration: " << counter << ", PSNR: " << PSNR << endl;
}













