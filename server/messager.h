#ifndef MESSAGER_H
#define MESSAGER_H

#include <thread>
#include "generator.h"

#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include <cstdint>

// \brief Поток для запуска диспетчера исходящих сообщений
void senderThread();

/* *\brief MessageSender - Класс для отправки сгенерированных данных
 *      попытка послать одну строку отображения + высоту
 */
class MessageSender {
    // sockaddr_in - описывает сокет для работы с протоколами IP
    struct sockaddr_in * m_socaddrMe; //!< Переменная для открытия соединения
    struct sockaddr_in * m_socaddrOther; //!< Переменная для получения/отправки сообщений
    int m_socetHandler; //!< ID сокета
    int m_recvLen; //!< Количество полученных байт

    Generator * msgGenerator; //!< Указатель на генератор пикселей
    socklen_t m_socLen; //!< socklen_t - структура для хранения размер адреса

    int m_lines; //!< Количество отображенных линий - считаетсколько линий было 
    // отображено
    int m_step; //!<  !!! Шаг запроса отображения - изменяется при приходе 
    // каждого 720-го запроса.
    
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
class MessageClient {
    // sockaddr_in - описывает сокет для работы с протоколами IP
    struct sockaddr_in * si_me; //!< Переменная для открытия соединения
    struct sockaddr_in * si_other; //!< Переменная для получения/отправки сообщений
    int m_socetHandler; //! ID сокета
    int m_recvLen; //! Количество полученных байт

//    static const int BUFLEN = 2;
    std::uint16_t m_buf; //! Временное хранилище

    socklen_t slen; //! socklen_t - структура для хранения размер адреса

public:
    MessageClient(std::uint16_t PORT);
    std::uint16_t receive(); //!< Процесс прослушки порта возвращает сообщение
    ~MessageClient();
};


#endif
