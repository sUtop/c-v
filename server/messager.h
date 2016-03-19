#ifndef MESSAGER_H
#define MESSAGER_H

#include <thread>
#include "generator.h"

#include <QtNetwork>

// \brief Поток для запуска диспетчера исходящих сообщений
void senderThread();

/* *\brief MessageSender - Класс для отправки сгенерированных данных
 *      попытка послать одну строку отображения + высоту
 */
class MessageSender : public QUdpSocket {
    Generator * msgGenerator; //!< Указатель на генератор пикселей

    int m_lines; //!< Количество отображенных линий - считаетсколько линий было 
    // отображено
    int m_step; //!<  !!! Шаг запроса отображения - изменяется при приходе 
    // каждого 720-го запроса.

    quint16 m_PORT;

public:
    MessageSender(std::uint16_t PORT);
    void send(std::uint16_t &);
    ~MessageSender();
};

// \brief Поток для запуска диспетчера входящих сообщений
void receiverThread();

/* *\brief MessageClient - Класс для получения запросов на отображение
 *      через него происходит рукопожатие и заявки на недоставленные данные
 */
class MessageClient : public QUdpSocket {
    std::uint16_t m_buf; //! Временное хранилище

    quint16 m_PORT;
    QHostAddress * m_address;

public:
    MessageClient(std::uint16_t PORT);
    std::uint16_t receive(); //!< Процесс прослушки порта возвращает сообщение
    ~MessageClient();
};


#endif
