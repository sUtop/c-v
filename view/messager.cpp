#include "messager.h"
#include "view.h" // Для печати данных


MessageClient * ms; //!< Класс для работы с сетью

void messageClientThread() {
    const std::chrono::nanoseconds sleep_time(10);
    ms = new MessageClient(8888);
    try {
        ms->init();
        while (1) {
            ms->getOnce();
            std::this_thread::sleep_for(sleep_time);
        };
    } catch (std::string str) {
        std::cout << "catched " << str << "\n";
    }
};

MessageClient::MessageClient(std::uint16_t PORT) {
    m_PORT = PORT;
}

void MessageClient::init() {

    m_address = new QHostAddress(QHostAddress::LocalHost);

    std::cout << "bind return " << bind(*m_address, m_PORT) << "\n";

}

void MessageClient::getOnce() {

    waitForReadyRead();
    Line buf;
    int i = readDatagram((char *) &buf, sizeof (Line), m_address, &m_PORT);

    if (buf.m_reserv == 100) { // Этой строкой проверяется корректность 
        // полученного сообщения
        for (int i = 0; i < 576; ++i) {
            // строка * количество байт на пиксель * строка + 
            // номер в строке * количество байт на пиксель
            pixels[576 * 4 * buf.m_number + i * 4] = buf.m_argb[i].m_A;
            pixels[576 * 4 * buf.m_number + i * 4 + 1] = buf.m_argb[i].m_R; // * 4 
            pixels[576 * 4 * buf.m_number + i * 4 + 2] = buf.m_argb[i].m_G; // * 4 
            pixels[576 * 4 * buf.m_number + i * 4 + 3] = buf.m_argb[i].m_B;
        }
        if (!m_finish && buf.m_number >= 700)
            m_finish = true;


    };

    if (m_finish && buf.m_number <= 20) {
        // Отправляем запрос только на следующем проходе
        // Так гарантируется корректность что пришел один экран.
        m_finish = false;
        askToRedraw();
    }

};

void MessageClient::askToRedraw() {
    emit pixelsFull();
}

MessageClient::~MessageClient() {
    close();
};

void messageAnswerThread() {

    try {
        MessageAnswer ma(7777);
        const std::chrono::nanoseconds sleep_time(10);

        while (1) {
            for (std::uint16_t i = 0; i < globalWidth; ++i) {
                ma.send(i);
                std::this_thread::sleep_for(sleep_time);
            }
        }
    } catch (std::string str) {
        std::cout << "catched " << str << "\n";
    }
};

MessageAnswer::MessageAnswer(std::uint16_t PORT) {
    m_PORT = PORT;
}

void MessageAnswer::send(const std::uint16_t message) {
    writeDatagram(
            (const char *) (&message),
            sizeof (std::uint16_t),
            QHostAddress::LocalHost,
            m_PORT);
};

MessageAnswer::~MessageAnswer() {
    close();

}

