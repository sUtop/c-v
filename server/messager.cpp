#include "messager.h"
#include <iostream>


#include <atomic>

std::atomic<std::uint16_t> request;

void senderThread()
{
    const std::chrono::nanoseconds sleep_time(10);
    try {
        while(1) {
            if(request != 0) {

                MessageSender ms(8888);

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
            else std::this_thread::sleep_for(sleep_time);
        };
    }
    catch(std::string str) {
        std::cout << "catched " << str << "\n";
    }


}

MessageSender::MessageSender(std::uint16_t PORT)
{
    m_lines = 0;
    m_step = 0;

    msgGenerator = new Generator(0, 0, 254);

    m_socaddrMe = new sockaddr_in();
    m_socaddrOther = new sockaddr_in();

    m_socLen = sizeof (sockaddr_in );
    m_recvLen = sizeof (Line );

    //Открытие UDP сокета
    if(( m_socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );

    m_socaddrOther->sin_family = AF_INET;
    m_socaddrOther->sin_port = htons(PORT);
    //    si_other->sin_addr.s_addr = htonl(INADDR_ANY);

    // Открытие DNS-соединения на чтение на сокете по порту
    //!< Bind для получения информации открывает клиент !!
    std::cout << "MessageSender  listening \n";

    std::uint16_t buff = 404;

    sendto(
           m_socetHandler, // socet
           &buff, // *buff
           2, // len_data
           0, // ?
           (struct sockaddr*) m_socaddrOther, // Адрес клиента
           m_socLen);
}

void MessageSender::send(std::uint16_t &c)
{
    int tmp = c;

    if(m_step <= 20)
        msgGenerator->genLine(tmp);
    else { // от 20-го до 23-го шага
            msgGenerator->m_data[tmp].clear();
            msgGenerator->m_data[tmp].m_number = tmp;
            msgGenerator->m_data[tmp].m_reserv = 100;
        // Выводит черный экран
    }

    if(sendto(
              m_socetHandler, // socet
              &( msgGenerator->m_data[tmp] ), // *buff
              m_recvLen, // len_data
              0, // ?
              (struct sockaddr*) m_socaddrOther, // Адрес клиента
              m_socLen)
       == -1)
        throw (std::string("sendto") );

    ++m_lines; // !Увеличиваем количество отосланных 

    // Если отослали один экран
    if(m_lines >= 719) {
        m_lines = 0;

        // Увеличиваем количество шагов
        ++m_step;

        // Если прошли 23 шага - сбрасываем
        if(m_step > 23)
            m_step = 0;
    }

//    std::cout << " m_lines " << m_lines << " m_step " << m_step << "\n";

}

MessageSender::~MessageSender()
{
    close(m_socetHandler);
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
    if(( m_socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );

    si_me->sin_family = AF_INET;
    si_me->sin_port = htons(PORT);
    si_me->sin_addr.s_addr = htonl(INADDR_ANY);

    // Открытие DNS-соединения на чтение на сокете по порту
    if(bind(m_socetHandler, (struct sockaddr*) si_me, sizeof (sockaddr_in )) == -1)
        throw (std::string("bind") );
}

std::uint16_t MessageClient::receive()
{
    // Попытка получить данные, блокирующий вызов, блокировка до получения данных
    if(( m_recvLen = recvfrom(m_socetHandler, &m_buf, sizeof (std::uint16_t ), 0, (struct sockaddr *) si_other, &slen) ) == -1)
        throw (std::string("recvfrom") );

    return m_buf;

}

MessageClient::~MessageClient()
{
    close(m_socetHandler);
}

