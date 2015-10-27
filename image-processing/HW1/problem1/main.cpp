#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    FILE *file;
    int BytesPerPixel = 3;
    int Size = 512;
    const char *fileName1 = "Pepper.raw";
    const char *fileName2 = "PepperGray.raw";
    const char *fileName3 = "mandril.raw";
    const char *fileName4 = "mandrilResize.raw";
    
    unsigned char pe_Data[Size][Size][BytesPerPixel];
    unsigned char pe_Gray[512][512][1];
    unsigned char ma_Data[Size][Size][BytesPerPixel];
    unsigned char ma_Resize[700][700][3];
    
    
/////////////////Read file////////////////////////////////////////
    if (!(file = fopen(fileName1,"rb")))
    {
        cout << "Cannot open file: " << fileName1 << endl;
        exit(1);
    }
    fread(pe_Data, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    
	
////////////////Problem1(a)///////////////////////////////////////
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            pe_Gray[i][j][0] = pe_Data[i][j][0] * 0.21 + pe_Data[i][j][1] * 0.72 + pe_Data[i][j][2] * 0.07;
        }
    }
    
///////////////////Write file/////////////////////////////////////
    
	if (!(file = fopen(fileName2,"wb")))
    {
        cout << "Cannot open file: " << fileName2 << endl;
        exit(1);
    }
    fwrite(pe_Gray, sizeof(unsigned char), 512 * 512 * 1, file);
    fclose(file);
    
///////////////////////////Problem1(b)////////////////////////////
    
    if (!(file = fopen(fileName3,"rb")))
    {
        cout << "Cannot open file: " << fileName3 << endl;
        exit(1);
    }
    fread(ma_Data, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
    fclose(file);
    
/////////////////////////////////////////////////////
    float nx, ny, a, b;
    int nx1, ny1;
    for(int i = 0; i < 3; i++)
    {
        for(int mx = 0; mx < 700; mx++)
        {
            for(int my = 0; my < 700; my++)
            {
                nx = (511 * mx) / 699 ;
                ny = (511 * my) / 699 ;
                nx1 = (int)nx;
                ny1 = (int)ny;
                a = nx - nx1;
                b = ny - ny1;
                ma_Resize[mx][my][i] = (1 - a) * (1 - b) * ma_Data[nx1][ny1][i] + a * (1 - b) * ma_Data[nx1 + 1][ny1][i] + (1 - a) * b * ma_Data[nx1][ny1 + 1][i] + a * b * ma_Data[nx1 + 1][ny1 + 1][i];
            }
        }
    }
    
///////////////////////Wirte file///////////////////////////////////
    if (!(file = fopen(fileName4,"wb")))
    {
        cout << "Cannot open file: " << fileName4 << endl;
        exit(1);
    }
    fwrite(ma_Resize, sizeof(unsigned char), 700 * 700 * 3, file);
    fclose(file);
    
}

