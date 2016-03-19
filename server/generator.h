#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdint>
#include <array>

/* * 
 * \brief PixelARGB Структура, описывающая один пиксель 
 *  На каждый канал выделено по 1 байт для каждого элемента структуры
 */
struct PixelARGB {
    std::uint8_t m_A; //!< Альфа-канал
    std::uint8_t m_R; //!< Канал красного цвета 
    std::uint8_t m_G; //!< Канал зеленого цвета
    std::uint8_t m_B; //!< Канал голубого цвета

    PixelARGB() : m_A(0), m_R(0), m_G(0), m_B(0) {
    };
};

/* * 
 * \brief Line Структура, описывающая одну пересылаемую строчку данных
 *  Содержит в себе строку пикселей, строку высот и индекс стоки
 * !TODO Вынести константу вовне!
 */
struct Line {
    PixelARGB m_argb[576]; //!< Данные о цвете       [2304 байт]
    std::uint8_t m_depth[576]; //!< Глубина          [576  байт]
    std::uint16_t m_number; //!< Индекс строки       [2    байта]
    std::uint16_t m_reserv; //!< Выравнивание        [2    байта]
    //!< Итого               [2884 байт]

    void clear(); //!< Последовательная очистка.
};

#include <random>

class Generator {
    std::mt19937 * m_generator;
    std::uniform_int_distribution<int> * m_dis;

    static const int mc_width = 720;
    static const int mc_height = 576;

    Line m_tmpLine;

    std::int8_t gen(); //!< Генерация одного значения
    void genPix(PixelARGB &p); //!< Генерация одного пикселя

public:
    std::array<Line, mc_width> m_data;
    //!< Хранилище пикселей. Хранит все строки 

    Generator(std::uint8_t seed, std::uint8_t min, std::uint8_t max);

    void genLine(int i);
};

#endif
