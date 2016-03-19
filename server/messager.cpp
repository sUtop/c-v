#include "messager.h"
#include <iostream>

#include <atomic>

std::atomic<std::uint16_t> request;

void senderThread() {
    const std::chrono::nanoseconds sleep_time(10);
    try {
        while (1) {
            if (request != 0) {

                MessageSender ms(8888);

                // Цыкл прослушивания
                while (1) {
                    if (request) {
                        std::uint16_t tmp = request;
                        request = 0;
                        ms.send(tmp);
                    } else std::this_thread::sleep_for(sleep_time);
                }
            } else std::this_thread::sleep_for(sleep_time);
        };
    } catch (std::string str) {
        std::cout << "catched " << str << "\n";
    }


}

MessageSender::MessageSender(std::uint16_t PORT) {
    m_lines = 0;
    m_step = 0;

    msgGenerator = new Generator(0, 0, 254);

    //!< Bind для получения информации открывает клиент !!
    std::cout << "MessageSender  listening \n";

    std::uint16_t buff = 404;

    m_PORT = PORT;

    writeDatagram(
            (const char *) (&buff),
            2,
            QHostAddress::LocalHost,
            m_PORT);
}

void MessageSender::send(std::uint16_t &c) {
    int tmp = c;

    if (m_step <= 20)
        msgGenerator->genLine(tmp);
    else { // от 20-го до 23-го шага
        msgGenerator->m_data[tmp].clear();
        msgGenerator->m_data[tmp].m_number = tmp;
        msgGenerator->m_data[tmp].m_reserv = 100;
        // Выводит черный экран
    }

    writeDatagram(
            (const char *) (&(msgGenerator->m_data[tmp])),
            sizeof (Line),
            QHostAddress::LocalHost,
            m_PORT);


    ++m_lines; // !Увеличиваем количество отосланных 

    // Если отослали один экран
    if (m_lines >= 719) {
        m_lines = 0;

        // Увеличиваем количество шагов
        ++m_step;

        // Если прошли 23 шага - сбрасываем
        if (m_step > 23)
            m_step = 0;
    }
    //    std::cout << " m_lines " << m_lines << " m_step " << m_step << "\n";
}

MessageSender::~MessageSender() {
    close(); //m_socetHandler);
}

void receiverThread() {
    try {
        MessageClient mr(7777);

        const std::chrono::nanoseconds sleep_time(1);
        while (1) {

            std::uint16_t tmp = mr.receive();
            if (tmp > 720) tmp %= 720;
            request = tmp;

            //                    std::cout << "request geted  =  " << request << "\n";
            std::this_thread::sleep_for(sleep_time);

        }
    } catch (std::string str) {
        std::cout << "catched " << str << "\n";
    }


}

MessageClient::MessageClient(std::uint16_t PORT) {
    m_PORT = PORT;
    m_address = new QHostAddress(QHostAddress::LocalHost);

    bind(*m_address, m_PORT);
}

std::uint16_t MessageClient::receive() {
    if (readDatagram((char *) &m_buf, sizeof (std::uint16_t), m_address, &m_PORT) == -1)
        return 0;
    return m_buf;
}

MessageClient::~MessageClient() {
    close(); //m_socetHandler);
}

