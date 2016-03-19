#ifndef MESSAGER_H
#define MESSAGER_H

#include <Qobject>
#include <QtNetwork>


#include <thread>
#include <atomic>
#include <iostream>


void messageClientThread();

//! Класс для получения сообщений
//! метод run - запускает метод loop в отдельном потоке
//!

class MessageClient : public QUdpSocket {
    Q_OBJECT

    bool m_finish;
    quint16 m_PORT;
    QHostAddress * m_address;

public:
    MessageClient(std::uint16_t PORT);
    void getOnce();

    void init();
    void askToRedraw();
    ~MessageClient();
signals:
    void pixelsFull();

};


void messageAnswerThread();

/* *\brief MessageAnswer - Класс для отправки запросов на отображение.
 */
class MessageAnswer : public QUdpSocket {
    quint16 m_PORT;

    QHostAddress * m_address;

public:
    MessageAnswer(std::uint16_t PORT);

    void send(const std::uint16_t message);

    ~MessageAnswer();

};

void run_msg();

#endif
