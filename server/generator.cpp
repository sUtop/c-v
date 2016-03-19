#include "generator.h"

void Line::clear() {
    for (int i = 0; i < 576; ++i) {
        m_argb[i].m_A = 0;
        m_argb[i].m_B = 0;
        m_argb[i].m_G = 0;
        m_argb[i].m_R = 0;
        m_depth[i] = 0;
    }
    m_number = 0;
    m_reserv = 0;
}

Generator::Generator(std::uint8_t seed, std::uint8_t min, std::uint8_t max) {
    m_generator = new std::mt19937(seed);
    m_dis = new std::uniform_int_distribution<int>(min, max);
}

std::int8_t Generator::gen() {
    return (*m_dis)(*m_generator);
}

void Generator::genPix(PixelARGB &p) {
    p.m_A = gen();
    p.m_R = gen();
    p.m_G = gen();
    p.m_B = gen();
}

void Generator::genLine(int iline) {
    for (int i = 0; i < 576; ++i) {
        genPix(m_data[iline].m_argb[i]);
        m_data[iline].m_depth[i] = gen();
    }
    m_data[iline].m_number = iline;
    m_data[iline].m_reserv = 100; //Проверочная строка
};

