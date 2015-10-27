#include <stdio.h>
#include <math.h>





int main()
{
    int width = 512;
    int height = 512;
    int n = 2;
    
    
    const char *r_fileName1 = "chem.256";
    const char *r_fileName2 = "house.256";
    const char *r_fileName3 = "moon.256";
    const char *r_fileName4 = "boat.raw";
    const char *n_fileName = "outputFile4X4.raw";
    
    FILE *file;
    unsigned char input1[height][width];
    unsigned char input2[height][width];
    unsigned char input3[height][width];
    unsigned char output1[height * width];
    unsigned char output2[height * width];
    unsigned char output3[height * width];
    
    unsigned char input[height][width];
    unsigned char output[height * width];
    
    
    /*if (!(file = fopen(r_fileName1,"rb")))
    {
        printf("Cannot open file: ", r_fileName1);
        exit(1);
    }
    fread(input1, sizeof(unsigned char), width * height, file);
    fclose(file);
    
    
    if (!(file = fopen(r_fileName2,"rb")))
    {
        printf("Cannot open file: ", r_fileName2);
        exit(1);
    }
    fread(input2, sizeof(unsigned char), width * height, file);
    fclose(file);
    
    
    
    if (!(file = fopen(r_fileName3,"rb")))
    {
        printf("Cannot open file: ", r_fileName3);
        exit(1);
    }
    fread(input3, sizeof(unsigned char), width * height, file);
    fclose(file);*/
    
    
    
    if (!(file = fopen(r_fileName4,"rb")))
    {
        printf("Cannot open file: ", r_fileName1);
        exit(1);
    }
    fread(input, sizeof(unsigned char), width * height, file);
    fclose(file);
    
    
    

    
    for(int i = 0; i < height; i += (int)pow(2, n))
    {
        for(int j = 0; j < width; j += (int)pow(2, n))
        {
            
            for(int m = i; m < i + (int)pow(2, n); m++)
            {
                for(int k = j; k < j + (int)pow(2, n); k++)
                {
                    /*output1[i * width + j * (int)pow(2, n) + (m - i) * (int)pow(2, n) + (k - j)] = input1[m][k];
                    output2[i * width + j * (int)pow(2, n) + (m - i) * (int)pow(2, n) + (k - j)] = input2[m][k];
                    output3[i * width + j * (int)pow(2, n) + (m - i) * (int)pow(2, n) + (k - j)] = input3[m][k];*/
                    
                    output[i * width + j * (int)pow(2, n) + (m - i) * (int)pow(2, n) + (k - j)] = input[m][k];
                }
            }
        }
    }


    
    /*for(int i = 0; i < height * width; i++)
    {
        output[i] = output1[i];
    }
    
    for(int i = height * width; i < 2 * height * width; i++)
    {
        output[i] = output2[i];
    }
    
    for(int i = 2 * height * width; i < 3 * height * width; i++)
    {
        output[i] = output3[i];
    }*/
    
    
    
    
    if (!(file = fopen(n_fileName,"wb")))
    {
        printf("Cannot open file: ", n_fileName);
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), width * height, file);
    fclose(file);

    
}







