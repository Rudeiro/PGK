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
    }

    
    return heights;
   
}