#include "DataReader.hpp"

std::vector<short> DataReader::ReadBinaryFile(std::vector<short> heights)
{
    short x;
    std::ifstream infile;
    infile.open("N45E006.hgt", std::ios::binary | std::ios::in);
    while(infile.read(reinterpret_cast<char *>(&x), sizeof(short)) )
    {
        //std::cout << __builtin_bswap16 (x) << std::endl;
        heights.push_back(__builtin_bswap16 (x));
    }
    return heights;
    //std::cout << heights.size();
}