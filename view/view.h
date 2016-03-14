#ifndef VIEW_H
#define VIEW_H

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

struct Line {
    PixelARGB argb[576]; // Данные о цвете       [2304 байт]
    std::uint8_t depth[576]; // Глубина          [576  байт]
    std::uint16_t number; // Индекс строки       [2    байта]
    std::uint16_t reserv; // Выравнивание        [2    байта]
                         // Итого                [2884 байт]

    void clear() {
        for (int i = 0; i < 576; ++i) {
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

static const int global_width = 720;
extern std::array<Line, global_width> * data;

extern char * pixels; //!< Указатель на заполненную структуру пикселей
extern MessageClient * ms; //!< Класс для работы с сетью

#endif
