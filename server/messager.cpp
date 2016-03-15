#include "messager.h"
#include <iostream>


#include <atomic>

std::atomic<std::uint16_t> request;

void senderThread()
{
    const std::chrono::milliseconds sleep_time(10);
    try {
        while(1) {
            if(request != 0) {

                MessageSender ms(8888);

                // Цыкл прослушивания
                while(1) {
                    if(request) {
                        //                        std::cout << "request in work" << request << "\n";
                        std::uint16_t tmp = request;
                        request = 0;
                        ms.send(tmp);
                    }
                    //                    else std::this_thread::sleep_for(sleep_time);
                }
            }
            else std::this_thread::sleep_for(sleep_time);
        };
    }
    catch(std::string str) {
        std::cout << "catched " << str << "\n";
    }


}

MessageSender::MessageSender(std::uint16_t PORT)
{

    msgGenerator = new Generator(0, 50, 255);

    si_me = new sockaddr_in();
    si_other = new sockaddr_in();

    slen = sizeof (sockaddr_in );

    //Открытие UDP сокета
    if(( socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );

    si_other->sin_family = AF_INET;
    si_other->sin_port = htons(PORT);
    //    si_other->sin_addr.s_addr = htonl(INADDR_ANY);

    // Открытие DNS-соединения на чтение на сокете по порту
    //!< Bind для получения информации открывает клиент !!
    std::cout << "MessageSender  listening \n";

    std::uint16_t buff = 404;

    sendto(
           socetHandler, // socet
           &buff, // *buff
           2, // len_data
           0, // ?
           (struct sockaddr*) si_other, // Адрес клиента
           slen);
}

void MessageSender::send(std::uint16_t &c)
{
    int tmp = c;

    msgGenerator->genLine(tmp);
    recv_len = sizeof (Line );

    if(sendto(
              socetHandler, // socet
              &( msgGenerator->data[tmp] ), // *buff
              recv_len, // len_data
              0, // ?
              (struct sockaddr*) si_other, // Адрес клиента
              slen)
       == -1)
        throw (std::string("sendto") );

    //    std::cout << "sended " << c << "\n";
}

MessageSender::~MessageSender()
{
    close(socetHandler);
}

void receiverThread()
{
    try {
        MessageClient mr(7777);

        //    const std::chrono::milliseconds sleep_time(1);
        while(1) {

            std::uint16_t tmp = mr.receive();
            if(tmp > 720) tmp %= 720;
            request = tmp;

            //        std::cout << "request geted  =  " << request << "\n";
            //        std::this_thread::sleep_for(sleep_time);

        }
    }
    catch(std::string str) {
        std::cout << "catched " << str << "\n";
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

