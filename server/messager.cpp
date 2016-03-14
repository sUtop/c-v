#include "messager.h"
#include <iostream>


#include <atomic>

std::atomic<std::uint16_t> request;

void senderThread()
{
    MessageSender ms(8888);
    const std::chrono::nanoseconds sleep_time(10);

    // Цыкл прослушивания
    while(1) {
        if(request) {
            std::uint16_t tmp = request;
            request = 0;
            ms.send(tmp);
        }
        else std::this_thread::sleep_for(sleep_time);
    }

}

MessageSender::MessageSender(std::uint16_t PORT)
{

    msgGenerator = new Generator(0, 200, 255);

    si_me = new sockaddr_in();
    si_other = new sockaddr_in();

    slen = sizeof (sockaddr_in );

    //Открытие UDP сокета
    if(( socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );

    si_me->sin_family = AF_INET;
    si_me->sin_port = htons(PORT);
    si_me->sin_addr.s_addr = htonl(INADDR_ANY);

    // Открытие DNS-соединения на чтение на сокете по порту
    if(bind(socetHandler, (struct sockaddr*) si_me, sizeof (sockaddr_in )) == -1)
        throw (std::string("bind") );

    // Полученние рукопожатия ? блокирует конструктор до начала соединения (заполняется si_other)
    if(( recv_len = recvfrom(socetHandler,
                             buf,
                             BUFLEN,
                             0,
                             (struct sockaddr *) si_other,
                             &slen)
         ) == -1)
        throw (std::string("recvfrom") );

    std::cout << "MessageSender " << buf << "\n";

//    
//    if(sendto(
//              socetHandler, // socet
//              &( msgGenerator->data.at(tmp) ), // *buff
//              recv_len, // len_data
//              0, // ?
//              (struct sockaddr*) si_other, // Адрес клиента
//              slen)
//       == -1)
    
    
}

// Пересылка

void MessageSender::send(std::uint16_t &c)
{
    // Попытка получить данные, блокирующий вызов
    //        if ((recv_len = recvfrom(socetHandler, buf, BUFLEN, 0, (struct sockaddr *) si_other, &slen)) == -1)
    //            throw(std::string("recvfrom"));

    int tmp = c;

    msgGenerator->genLine(tmp);
    recv_len = sizeof (Line );
    // Отправка пакета обратно


    /* Send N bytes of BUF on socket FD to peer at address ADDR (which is
       ADDR_LEN bytes long).  Returns the number sent, or -1 for errors.

       This function is a cancellation point and therefore not marked with
       __THROW.  */
    //extern ssize_t sendto (int __fd, const void *__buf, size_t __n,
    //		       int __flags, __CONST_SOCKADDR_ARG __addr,
    //		       socklen_t __addr_len);
    //

    if(sendto(
              socetHandler, // socet
              &( msgGenerator->data[tmp] ), // *buff
              recv_len, // len_data
              0, // ?
              (struct sockaddr*) si_other, // Адрес клиента
              slen)
       == -1)
        throw (std::string("sendto") );
}

MessageSender::~MessageSender()
{
    close(socetHandler);
}

void receiverThread()
{
    MessageClient mr(7777);

    const std::chrono::nanoseconds sleep_time(10);
    while(1) {

        std::uint16_t tmp = mr.receive();
        if(tmp > 720) tmp %= 720;
        request = tmp;

        std::cout << "request geted  =  " << request << "\n";
        std::this_thread::sleep_for(sleep_time);

    }

}

MessageClient::MessageClient(std::uint16_t PORT)
{
    si_me = new sockaddr_in();
    si_other = new sockaddr_in();

    slen = sizeof (sockaddr_in );

    //Открытие UDP сокета
    if(( socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );

    si_me->sin_family = AF_INET;
    si_me->sin_port = htons(PORT);
    si_me->sin_addr.s_addr = htonl(INADDR_ANY);

    // Открытие DNS-соединения на чтение на сокете по порту
    if(bind(socetHandler, (struct sockaddr*) si_me, sizeof (sockaddr_in )) == -1)
        throw (std::string("bind") );
}

std::uint16_t MessageClient::receive()
{
    // Попытка получить данные, блокирующий вызов, блокировка до получения данных
    if(( recv_len = recvfrom(socetHandler, &buf, sizeof (std::uint16_t ), 0, (struct sockaddr *) si_other, &slen) ) == -1)
        throw (std::string("recvfrom") );

    return buf;

}

MessageClient::~MessageClient()
{
    close(socetHandler);
}



// Печать полученного пакета и порта
//        printf("Received packet from %s:%d\n", inet_ntoa(si_other->sin_addr), ntohs(si_other->sin_port));
//        printf("Data: %s\n" , buf);



