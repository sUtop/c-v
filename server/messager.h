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


/* *\brief Класс для отправки сгенерированных данных
 *      попытка послать одну строку отображения + высоту
 */
class MessageSender {
    // sockaddr_in - описывает сокет для работы с протоколами IP
    struct sockaddr_in * si_me; //!< Переменная для открытия соединения
    struct sockaddr_in * si_other; //!< Переменная для получения/отправки сообщений
    int socetHandler, //! ID сокета
    recv_len; //! Количество полученных байт


    Generator * msgGenerator;
    //#define BUFLEN 512  //  Длинна буффера - нужно 576 * 5 - одна строка
    static const int BUFLEN = 576 * 5;
    char buf[BUFLEN]; //! Временное хранилище

    socklen_t slen; //! socklen_t - структура для хранения размер адреса

public:
    MessageSender(std::uint16_t PORT);
    void send(std::uint16_t &);
    ~MessageSender();
};


// \brief Поток для запуска диспетчера входящих сообщений
void receiverThread();


/* *\brief Класс для получения запросов на отображение
 *      через него происходит рукопожатие и заявки на недоставленные данные
 */
class MessageClient {
    // sockaddr_in - описывает сокет для работы с протоколами IP
    struct sockaddr_in * si_me; //!< Переменная для открытия соединения
    struct sockaddr_in * si_other; //!< Переменная для получения/отправки сообщений
    int socetHandler, //! ID сокета
    recv_len; //! Количество полученных байт

//    static const int BUFLEN = 2;
    std::uint16_t buf; //! Временное хранилище

    socklen_t slen; //! socklen_t - структура для хранения размер адреса

public:
    MessageClient(std::uint16_t PORT);
    std::uint16_t receive(); //!< Процесс прослушки порта возвращает сообщение
    ~MessageClient();
};





#endif


