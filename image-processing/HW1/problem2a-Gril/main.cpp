#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;


struct pixel{
    int x, y;
    int r, g, b;
};



int main()
{
    
    
    FILE *file;
    int size1 = 256;
    int size2 = 256;
    int BytesPerPixel = 3;
    int lumin = 256;
    const char *r_fileName = "Girl.raw";
    const char *n_fileName = "Girl_equal.raw";
    const char *fName[3] = {"data1.txt", "data2.txt", "data3.txt"};
    const char *h_fName[3] = {"h_eqdata1.txt", "h_eqdata2.txt", "h_eqdata3.txt"};
    const char *h_tName[3] = {"h_intedata1.txt", "h_intedata2.txt", "h_intedata3.txt"};
    const char *h_iName[3] = {"h_idata1.txt", "h_idata2.txt", "h_idata3.txt"};
    unsigned char g_Data[size2][size1][BytesPerPixel];
    vector<struct pixel> v0;
    vector<struct pixel> v1;
    vector<struct pixel> v2;
    vector<struct pixel> v3;
    struct pixel p0, p1, p2, p3;
    
////////////////////////////////read file into a 3D array////////////////////////////
    
    if (!(file = fopen(r_fileName,"rb")))
    {
        cout << "Cannot open file: " << r_fileName << endl;
        exit(1);
    }
    fread(g_Data, sizeof(unsigned char), size1 * size2 * BytesPerPixel, file);
    fclose(file);
    
 ///////////////store in the struct array from g_Data////////////////////////////////
    
    for(int i = 0; i < size2; i++)
    {
        for(int j = 0; j < size1; j++)
        {
            p0.x = i;
            p0.y = j;
            p0.r = g_Data[i][j][0];
            p0.g = g_Data[i][j][1];
            p0.b = g_Data[i][j][2];
            v0.push_back(p0);
        }
    }
    
/////////////////////// write raw file histogram data////////////////////////////////
    
    int count[lumin][BytesPerPixel];
    
    //////// let items in count array all equal to 0/////////
    
    for(int i = 0; i < lumin; i++)
    {
        for(int j = 0; j < BytesPerPixel; j++)
        {
            count[i][j] = 0;
        }
    }

    ////////////count the number of pixels in each scale//////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(v0.at(i).r == j)
            {
                count[j][0]++;
            }
            if(v0.at(i).g == j)
            {
                count[j][1]++;
            }
            if(v0.at(i).b == j)
            {
                count[j][2]++;
            }

        }
        
    }

    /////////////write in txt file//////////////////////
    
    for(int j = 0; j < BytesPerPixel; j++)
    {
        if((file = fopen(fName[j], "wb")) != NULL)
        {
            for(int i = 0; i < lumin; i++)
            {
                fprintf(file, "%d ", count[i][j]);
            }
        }
        fclose(file);
    }


    


    
    
    
    
    
    
    
    
//////////////////////////histogram equalization//////////////////////////////////
    
    int r[256] = {0};
    int g[256] = {0};
    int b[256] = {0};
    
    ////////////sort the pixels accroding to R scale////////
    for(int j = 0; j < lumin; j++)
    {
        for(int i = 0; i < size1 * size2 ; i++)
        {
            if(v0.at(i).r == j)
            {
                p1.r = v0.at(i).r;
                p1.g = v0.at(i).g;
                p1.b = v0.at(i).b;
                p1.x = v0.at(i).x;
                p1.y = v0.at(i).y;
                v1.push_back(p1);
            }
        }
    }
    
    //////////first 256 pixels equal to 0, and so on///////
    
    for(int i = 0; i < size2; i++)
    {
        for(int j = 0; j < size1; j++)
        {
            v1.at(i * size1 + j).r = i;
        }
    }
    
    /////////each value has 256 pixels/////////////////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(v1.at(i).r == j)
            {
                r[j]++;
            }
        }
    }
    
    ////////write into a txt file/////////////////////////
    
    if((file = fopen(h_fName[0], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", r[i]);
        }
    }
    fclose(file);
    
////////////////sort the pixels accroding to G scale//////////////////////////
    
    for(int j = 0; j < lumin; j++)
    {
        for(int i = 0; i < size1 * size2 ; i++)
        {
            if(v1.at(i).g == j)
            {
                p2.r = v1.at(i).r;
                p2.g = v1.at(i).g;
                p2.b = v1.at(i).b;
                p2.x = v1.at(i).x;
                p2.y = v1.at(i).y;
                v2.push_back(p2);
            }

        }
    }
    
    
    //////////first 256 pixels equal to 0, and so on///////
    
    for(int i = 0; i < size2; i++)
    {
        for(int j = 0; j < size1; j++)
        {
            v2.at(i * size2 + j).g = i;
        }
    }
    
    /////////each value has 256 pixels/////////////////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(v2.at(i).g == j)
            {
                g[j]++;
            }
        }
    }
    
    
    ////////write into a txt file/////////////////////////
    
    if((file = fopen(h_fName[1], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", g[i]);
        }
    }
    fclose(file);
    

////////////////////////sort the pixels accroding to B scale//////////////////////////
    
    for(int j = 0; j < lumin; j++)
    {
        for(int i = 0; i < size1 * size2; i++)
        {
            if(v2.at(i).b == j)
            {
                p3.r = v2.at(i).r;
                p3.g = v2.at(i).g;
                p3.b = v2.at(i).b;
                p3.x = v2.at(i).x;
                p3.y = v2.at(i).y;
                v3.push_back(p3);
            }
        }
    }
    
    //////////first 256 pixels equal to 0, and so on///////
    
    for(int i = 0; i < size2; i++)
    {
        for(int j = 0; j < size1; j++)
        {
            v3.at(i * size1 + j).b = i;
        }
    }
    
    /////////each value has 256 pixels/////////////////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(v3.at(i).b == j)
            {
                b[j]++;
            }
        }
    }
    
    
    ////////write into a txt file/////////////////////////
    if((file = fopen(h_fName[2], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", b[i]);
        }
    }
    fclose(file);
    

/////////store changed pixels into a new 3D array/////////////////////////////////
    
    unsigned char eq_g_Data[size2][size1][BytesPerPixel];
    for(int i = 0; i < size1 * size2; i++)
    {
        eq_g_Data[v3.at(i).x][v3.at(i).y][0] = v3.at(i).r;
        eq_g_Data[v3.at(i).x][v3.at(i).y][1] = v3.at(i).g;
        eq_g_Data[v3.at(i).x][v3.at(i).y][2] = v3.at(i).b;
    }
    
    
    ///////wirte to a new picture //////////////////
    if (!(file = fopen(n_fileName,"wb")))
    {
        cout << "Cannot open file: " << n_fileName << endl;
        exit(1);
    }
    fwrite(eq_g_Data, sizeof(unsigned char), size1 * size2 * BytesPerPixel, file);
    fclose(file);
    
    

    /*//////// let items in count array all equal to 0/////////
    int count1[lumin][BytesPerPixel];
    const char *eqName[3] = {"eqdata1.txt", "eqdata2.txt", "eqdata3.txt"};
    for(int i = 0; i < lumin; i++)
    {
        for(int j = 0; j < BytesPerPixel; j++)
        {
            count1[i][j] = 0;
        }
    }
    
    ////////////count the number of pixels in each scale//////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(v3.at(i).r == j)
            {
                count1[j][0]++;
            }
            if(v3.at(i).g == j)
            {
                count1[j][1]++;
            }
            if(v3.at(i).b == j)
            {
                count1[j][2]++;
            }
            
        }
        
    }
    
    /////////////write in txt file//////////////////////
    
    for(int j = 0; j < BytesPerPixel; j++)
    {
        if((file = fopen(eqName[j], "wb")) != NULL)
        {
            for(int i = 0; i < lumin; i++)
            {
                fprintf(file, "%d ", count1[i][j]);
            }
        }
        fclose(file);
    }*/

    
    
    
    
    
    
    
    
    
    
///////////////////////////////CUMULATIVE EQUALIZATION/////////////////////////////
    
    int integer[lumin][BytesPerPixel];
    vector<struct pixel> cumu0;
    vector<struct pixel> cumu1;
    vector<struct pixel> cumu2;
    vector<struct pixel> cumu3;
    struct pixel c0, c1, c2, c3;
    int c_Red[256] = {0};
    int c_Green[256] = {0};
    int c_Blue[256] = {0};
    const char *h_cumuName[3] = {"h_cumudata1.txt", "h_cumudata2.txt", "h_cumudata3.txt"};
    const char *n1_fileName = "Girl_cumu.raw";
    
    /////////// calculate the integer ////////////////////
    
    
    for(int j = 0; j < BytesPerPixel; j++)
    {
        integer[0][j] = count[0][j];
        for(int i = 1; i < lumin; i++)
        {
            integer[i][j] = integer[i - 1][j] + count[i][j];
        }
    }
    
    for(int j = 0; j < BytesPerPixel; j++)
    {
        if((file = fopen(h_tName[j], "wb")) != NULL)
        {
            for(int i = 0; i < lumin; i++)
            {
                fprintf(file, "%d ", integer[i][j]);
            }
        }
        fclose(file);
    }
    ///// store in the struct vector from g_Data /////////
    
    
    for(int i = 0; i < size2; i++)
    {
        for(int j = 0; j < size1; j++)
        {
            c0.x = i;
            c0.y = j;
            c0.r = g_Data[i][j][0];
            c0.g = g_Data[i][j][1];
            c0.b = g_Data[i][j][2];
            cumu0.push_back(c0);
        }
    }
    


/////////////////////////  PROCESS THE RED COLOR  ////////////////////////////////////
    ////////////sort the pixels accroding to R scale////////
    
    
    for(int j = 0; j < lumin; j++)
    {
        for(int i = 0; i < size1 * size2 ; i++)
        {
            if(cumu0.at(i).r == j)
            {
                c1.r = cumu0.at(i).r;
                c1.g = cumu0.at(i).g;
                c1.b = cumu0.at(i).b;
                c1.x = cumu0.at(i).x;
                c1.y = cumu0.at(i).y;
                cumu1.push_back(c1);
            }

        }
    }

    
    ////////////////  cumulative ////////////////////
    
    
    for(int j = 0; j < lumin; j++)
    {
        if((int)((integer[0][0] * 256) / ( size1 * size2)) == j)
        {
            for(int k = 0; k < integer[0][0]; k++)
            {
                cumu1.at(k).r = j;
            }
        }
    }
    
    for(int i = 1; i < lumin; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            if((int)((integer[i][0] * 256) / ( size1 * size2)) == j)
            {
                for(int k = integer[i - 1][0]; k < integer[i][0]; k++)
                {
                    cumu1.at(k).r = j;
                }
            }
        }
    }
    
    
    //////////// new number of each value ///////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            if(cumu1.at(i).r == j)
            {
                c_Red[j]++;
            }

        }
    }

    ////////write into a txt file////////////////////
    
    if((file = fopen(h_cumuName[0], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", c_Red[i]);
        }
    }
    fclose(file);


    int integer1[256][3] = {0};
    integer[0][0] = c_Red[0];
    for(int i = 1; i < lumin; i++)
    {
        integer[i][0] = integer[i - 1][0] + c_Red[i];
    }
    if((file = fopen(h_iName[0], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", integer[i][0]);
        }
    }
    fclose(file);
////////////////////////  PROCESS THE GREEN COLOR  ///////////////////////////////////
////////////sort the pixels accroding to G scale////////
   
    for(int j = 0; j < lumin; j++)
    {
        for(int i = 0; i < size1 * size2 ; i++)
        {
            if(cumu1.at(i).g == j)
            {
                c2.r = cumu1.at(i).r;
                c2.g = cumu1.at(i).g;
                c2.b = cumu1.at(i).b;
                c2.x = cumu1.at(i).x;
                c2.y = cumu1.at(i).y;
                cumu2.push_back(c2);
            }

        }
    }
    
    
    ////////////////  cumulative ////////////////////
    
    for(int j = 0; j < lumin; j++)
    {
        if((int)((integer[0][1] * 256) / ( size1 * size2)) == j)
        {
            for(int k = 0; k < integer[0][1]; k++)
            {
                cumu2.at(k).g = j;
            }
        }
    }
    
    for(int i = 1; i < lumin; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            if((int)((integer[i][1] * 256) / ( size1 * size2)) == j)
            {
                for(int k = integer[i - 1][1]; k < integer[i][1]; k++)
                {
                    cumu2.at(k).g = j;
                }
            }
        }
    }
    
    
    //////////// new number of each value ///////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(cumu2.at(i).g == j)
            {
                c_Green[j]++;
            }
        }
    }
    
    ////////write into a txt file////////////////////
   
    if((file = fopen(h_cumuName[1], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", c_Green[i]);
        }
    }
    fclose(file);

    integer[0][1] = c_Green[0];
    for(int i = 1; i < lumin; i++)
    {
        integer[i][1] = integer[i - 1][1] + c_Green[i];
    }
    if((file = fopen(h_iName[1], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", integer[i][1]);
        }
    }
    fclose(file);
////////////////////////  PROCESS THE BLUE COLOR  ///////////////////////////////////
    ////////////sort the pixels accroding to G scale////////
    
    for(int j = 0; j < lumin; j++)
    {
        for(int i = 0; i < size1 * size2 ; i++)
        {
            if(cumu2.at(i).b == j)
            {
                c3.r = cumu2.at(i).r;
                c3.g = cumu2.at(i).g;
                c3.b = cumu2.at(i).b;
                c3.x = cumu2.at(i).x;
                c3.y = cumu2.at(i).y;
                cumu3.push_back(c3);
            }
        }
    }
    
    
    ////////////////  cumulative ////////////////////
    
    for(int j = 0; j < lumin; j++)
    {
        if((int)((integer[0][2] * 256) / ( size1 * size2)) == j)
        {
            for(int k = 0; k < integer[0][2]; k++)
            {
                cumu3.at(k).b = j;
            }
        }
    }
    
    for(int i = 1; i < lumin; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            if((int)((integer[i][2] * 256) / ( size1 * size2)) == j)
            {
                for(int k = integer[i - 1][2]; k < integer[i][2]; k++)
                {
                    cumu3.at(k).b = j;
                }
            }
        }
    }
    
    
    //////////// new number of each value ///////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(cumu3.at(i).b == j)
            {
                c_Blue[j]++;
            }
        }
    }
    
    ////////write into a txt file////////////////////
    
    if((file = fopen(h_cumuName[2], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", c_Blue[i]);
        }
    }
    fclose(file);
    
    integer[0][2] = c_Blue[0];
    for(int i = 1; i < lumin; i++)
    {
        integer[i][2] = integer[i - 1][2] + c_Blue[i];
    }
    if((file = fopen(h_iName[2], "wb")) != NULL)
    {
        for(int i = 0; i < lumin; i++)
        {
            fprintf(file, "%d ", integer[i][2]);
        }
    }
    fclose(file);
    
    /////////////output the image ///////////////////////
    
    unsigned char cumu_g_Data[size2][size1][BytesPerPixel];
    for(int i = 0; i < size1 * size2; i++)
    {
        cumu_g_Data[cumu3.at(i).x][cumu3.at(i).y][0] = cumu3.at(i).r;
        cumu_g_Data[cumu3.at(i).x][cumu3.at(i).y][1] = cumu3.at(i).g;
        cumu_g_Data[cumu3.at(i).x][cumu3.at(i).y][2] = cumu3.at(i).b;
    }
    
    
    if (!(file = fopen(n1_fileName,"wb")))
    {
        cout << "Cannot open file: " << n1_fileName << endl;
        exit(1);
    }
    fwrite(cumu_g_Data, sizeof(unsigned char), size1 * size2 * BytesPerPixel, file);
    fclose(file);
    
    
    
    
    /*//////// let items in count array all equal to 0/////////
    
    const char *cuName[3] = {"cudata1.txt", "cudata2.txt", "cudata3.txt"};
    int count2[lumin][BytesPerPixel];
    for(int i = 0; i < lumin; i++)
    {
        for(int j = 0; j < BytesPerPixel; j++)
        {
            count2[i][j] = 0;
        }
    }
    
    ////////////count the number of pixels in each scale//////////
    
    for(int i = 0; i < size1 * size2; i++)
    {
        for(int j = 0; j < lumin; j++)
        {
            
            if(cumu3.at(i).r == j)
            {
                count2[j][0]++;
            }
            if(cumu3.at(i).g == j)
            {
                count2[j][1]++;
            }
            if(cumu3.at(i).b == j)
            {
                count2[j][2]++;
            }
            
        }
        
    }
    
    /////////////write in txt file//////////////////////
    
    for(int j = 0; j < BytesPerPixel; j++)
    {
        if((file = fopen(cuName[j], "wb")) != NULL)
        {
            for(int i = 0; i < lumin; i++)
            {
                fprintf(file, "%d ", count2[i][j]);
            }
        }
        fclose(file);
    }*/
    


}