#include "DataReader.hpp"
void swapBytes(short *a)
{
    char *b = (char*)a;
    char t = *a;
    b[0] = b[1];
    b[1] = t;
}

std::vector<short> DataReader::ReadBinaryFile(std::string filename)
{
    std::vector<short> heights;
    short x;
    std::ifstream infile;
    infile.open(filename, std::ios::binary | std::ios::in);
    while(infile.read(reinterpret_cast<char *>(&x), sizeof(short)) )
    {
        //__builtin_bswap16 (x)
        swapBytes(&x);
        //std::cout << __builtin_bswap16 (x) << std::endl;
        heights.push_back(x);
        //std::cout << x << std::endl;
    }
    int k = 0;
    for(int i = 0; i < heights.size(); i++)
    {
       // std::cout << heights[i] << std::endl;
        while(heights[i+k] < -1000 ) k++;
        for(int j = 0; j < k; j++)
        {
            
            
            if(i%1201 != 0 && (i+k-1)%1201 != 1200) 
            {
                heights[i+j] = heights[i-1] + floor((1.0f*(j+1)/(k+1))*(heights[i+k]-heights[i-1]));
                //std::cout << "xd " << heights[i+j] << std::endl;
                //std::cout << "xd " << heights[i-1] << " " << heights[i+k] << " " << (1.0f*(j+1)/k+1)*(heights[i+k]-heights[i-1]) << " " <<  heights[i+j] << " " << j+1 << " " << k+1 << " "<< std::endl;
            }
            else if(i%1201 == 0) heights[i+j] = heights[i+k];
            else heights[i+j] = heights[i-1];
            
        }
        k = 0;
    }
    
    return heights;
   
}