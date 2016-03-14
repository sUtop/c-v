#ifndef MESSAGER_H
#define MESSAGER_H

#include <qobject.h>
// ? qobject ? <- 
#include <thread>

void messageClientThread();



#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>


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

    static const int BUFLEN = 512;
    char buf[BUFLEN]; //! Временное хранилище

    socklen_t slen; //! socklen_t - структура для хранения размер адреса

public:
    MessageClient(std::uint16_t PORT);
    void run();

    void sendSignal();
signals:
    void getMessage();

};

class MessageAnswer {
    struct sockaddr_in * si_me; //!< Переменная для открытия соединения
    struct sockaddr_in * si_other; //!< Переменная для получения/отправки сообщений
    int socetHandler, //! ID сокета
    recv_len; //! Количество полученных байт

    static const int BUFLEN = 4;
    char buf[BUFLEN]; //! Временное хранилище

    socklen_t slen; //! socklen_t - структура для хранения размер адреса

public:
    MessageAnswer(std::uint16_t PORT);

    void send(int &);
    void get();
    
    ~MessageAnswer();

};



//void loop(MessageClient *ms);
void run_msg();



#endif


