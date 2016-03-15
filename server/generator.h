#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdint>
#include <array>

struct PixelARGB {
    // 1 байт для каждого элемента структуры
    std::uint8_t A; // Альфа-канал
    std::uint8_t R; //
    std::uint8_t G;
    std::uint8_t B;

    PixelARGB() : A(0), R(0), G(0), B(0) {
    };
};

//!< TODO Вынести константу вовне!
struct Line {
    PixelARGB argb[576];    // Данные о цвете       [2304 байт]
    std::uint8_t depth[576];// Глубина              [576  байт]
    std::uint16_t number;   // Индекс строки        [2    байта]
    std::uint16_t reserv;   // Выравнивание         [2    байта]
                            // Итого                [2884 байт]
    void clear() {
        for(int i = 0; i < 576; ++i) {
            argb[i].A = 0;
            argb[i].B = 0;
            argb[i].G = 0;
            argb[i].R = 0;
            depth[i] = 0;
        }
        number = 0;
        reserv = 0;
    }
};

#include <random>

class Generator {
    //    std::random_device rd;
    std::mt19937 * generator;
    std::uniform_int_distribution<std::uint8_t> * dis;

    static const int width = 720;
    static const int height = 576;

    std::int8_t gen();

    void genPix(PixelARGB &p);
//    PixelARGB & genPix();

    inline int ijToarray(int i, int j) {
        return i * height + j;
    }

    Line tmpLine;
public:
    std::array<PixelARGB, width * height> colors;
    std::array<std::uint8_t, width * height> depth; //!< глубина

    std::array<Line, width> data;
    
    // Переменные для полной генерации
    int m_step;
    int m_width;
    int m_height;


    Generator(std::uint8_t seed, std::uint8_t min, std::uint8_t max);

    void gen(int i, int j);

    void genLine(int i);
};

#endif
