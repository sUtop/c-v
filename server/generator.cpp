#include "generator.h"

Generator::Generator(std::int8_t seed, std::int8_t min, std::int8_t max)
{
    generator = new std::mt19937(seed);
    dis = new std::uniform_int_distribution<std::int8_t>( min, max );
}

void Generator::gen(int i, int j)
{
    int arr = ijToarray(i, j);
    colors[arr] = genPix();
    depth[arr] = gen();
}

std::int8_t Generator::gen()
{
    return (*dis )( *generator );
}

PixelARGB & Generator::genPix()
{
    PixelARGB * p = new PixelARGB;
    p->A = gen();
    p->R = gen();
    p->G = gen();
    p->B = gen();
    return *p;
}



void Generator::genLine(int iline){
//    tmpLine.clear();
    
    for(int i = 0; i < 576; ++i) {
            data[iline].argb[i] = genPix();
            data[iline].depth[i] = gen();
    }
    data[iline].number = iline;
    data[iline].reserv = 100;

//    data[iline] = tmpLine;
};

