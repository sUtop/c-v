#include "generator.h"

Generator::Generator(std::uint8_t seed, std::uint8_t min, std::uint8_t max)
{
    generator = new std::mt19937(seed);
    dis = new std::uniform_int_distribution<std::uint8_t>( min, max );
}

void Generator::gen(int i, int j)
{
    int arr = ijToarray(i, j);
    genPix(colors[arr]);
    depth[arr] = gen();
}

std::int8_t Generator::gen()
{
    return (*dis )( *generator );
}

void Generator::genPix(PixelARGB &p)
{
    p.A = gen();
    p.R = gen();
    p.G = gen();
    p.B = gen();
}

void Generator::genLine(int iline)
{
    for(int i = 0; i < 576; ++i) {
        genPix(data[iline].argb[i]);
        data[iline].depth[i] = gen();
    }
    data[iline].number = iline;
    data[iline].reserv = 100; //Проверочная строка
};

