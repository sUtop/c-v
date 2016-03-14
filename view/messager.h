#ifndef MESSAGER_H
#define MESSAGER_H

#include <qobject.h>
// ? qobject ? <- 
#include <thread>
#include <atomic>
#include <iostream>

#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>


void messageClientThread();

//! Класс для получения сообщений
//! метод run - запускает метод loop в отдельном потоке
//!

class MessageClient : public QObject {
    Q_OBJECT

    //    std::thread * m_thread;
    //   static void loop();

    // sockaddr_in - описывает сокет для работы с протоколами IP
    struct sockaddr_in * si_me; //!< Переменная для открытия соединения
    struct sockaddr_in * si_other; //!< Переменная для получения/отправки сообщений
    int socetHandler, //! ID сокета
    recv_len; //! Количество полученных байт

//    static const int BUFLEN = 512;
//    char buf[BUFLEN]; //! Временное хранилище

    bool m_finish;
    socklen_t slen; //! socklen_t - структура для хранения размер адреса

    std::uint16_t m_PORT;

public:
    MessageClient(std::uint16_t PORT);
    void getOnce();

    void init();
    void sendSignal();
signals:
    void getMessage();

};


void messageAnswerThread();

class MessageAnswer {
    struct sockaddr_in * si_other; //!< Переменная для получения/отправки сообщений
    int socetHandler, //! ID сокета
    recv_len; //! Количество полученных байт

    static const int BUFLEN = 4;
    char buf[BUFLEN]; //! Временное хранилище

    socklen_t slen; //! socklen_t - структура для хранения размер адреса

public:
    MessageAnswer(std::uint16_t PORT);

    void send(std::uint16_t & message);
    void get();

    ~MessageAnswer();

};

void run_msg();

#endif
