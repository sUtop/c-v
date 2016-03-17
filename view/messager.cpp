#include "messager.h"
#include "view.h" // Для печати данных

MessageClient * ms = new MessageClient(8888); //!< Класс для работы с сетью

void messageClientThread()
{
    try {
        ms->init();
        while(1) {
            ms->getOnce();
        };
    }
    catch(std::string str) {
        std::cout << "catched " << str << "\n";
    }
};

MessageClient::MessageClient(std::uint16_t PORT)
{
    m_PORT = PORT;
}

void MessageClient::init()
{
    m_finish = false;
    si_me = new sockaddr_in();
    si_other = new sockaddr_in();

    slen = sizeof (sockaddr_in );

    //Открытие UDP сокета
    if(( socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );

    si_me->sin_family = AF_INET;
    si_me->sin_port = htons(m_PORT);

    si_me->sin_addr.s_addr = htonl(INADDR_ANY);

    //!< Bind для получения информации открывает клиент !!
    if(bind(socetHandler, (struct sockaddr*) si_me, sizeof (sockaddr_in )) == -1)
        throw (std::string("bind") );

    std::uint16_t buff;
    recvfrom(socetHandler, &buff, 2, 0, (struct sockaddr *) si_other, &slen);

//    if(buff != 404) throw (std::string("wtf" + std::to_string(buff)) );
//    else std::cout << " Correct handshake ! \n";

}

void MessageClient::getOnce()
{

    Line buf;
    int i = recvfrom(socetHandler, &buf, sizeof (Line ), 0, (struct sockaddr *) si_other, &slen);
    if(i == -1) {
        std::cout << "geted " << i << " " << errno << "\n";
        return;
    }

    if(buf.m_reserv == 100) { // Этой строкой проверяется корректность 
        // полученного сообщения
        for(int i = 0; i < 576; ++i) {
            // строка * количество байт на пиксель * строка + 
            // номер в строке * количество байт на пиксель
            pixels[576 * 4 * buf.m_number + i * 4] = buf.m_argb[i].m_A;
            pixels[576 * 4 * buf.m_number + i * 4 + 1] = buf.m_argb[i].m_R; // * 4 
            pixels[576 * 4 * buf.m_number + i * 4 + 2] = buf.m_argb[i].m_G; // * 4 
            pixels[576 * 4 * buf.m_number + i * 4 + 3] = buf.m_argb[i].m_B;
        }
        if(!m_finish && buf.m_number >= 700)
            m_finish = true;

    };

//        std::cout << "geted " << buf.m_number << " \n";

    if(m_finish && buf.m_number <= 10) { 
        // Отправляем запрос только на следующем проходе
        // Так гарантируется корректность что пришел один экран.
        askToRedraw();
        m_finish = false;
    }

};

void MessageClient::askToRedraw()
{
    emit pixelsFull();
}

MessageClient::~MessageClient()
{
    close(socetHandler);
};

void messageAnswerThread()
{

    try {
        MessageAnswer ma(7777);
        const std::chrono::nanoseconds sleep_time(10);

        while(1) {
            for(std::uint16_t i = 0; i < globalWidth; ++i) {
                ma.send(i);
                std::this_thread::sleep_for(sleep_time);
            }
        }
    }
    catch(std::string str) {
        std::cout << "catched " << str << "\n";
    }
};

MessageAnswer::MessageAnswer(std::uint16_t PORT)
{

    si_other = new sockaddr_in();
    slen = sizeof (sockaddr_in );

    //Открытие UDP сокета
    if(( socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );
    si_other->sin_family = AF_INET;
    si_other->sin_port = htons(PORT);
    si_other->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

void MessageAnswer::send(std::uint16_t & message)
{
    if(sendto(socetHandler, &message, sizeof (std::uint16_t ), 0, (struct sockaddr *) si_other, slen) == -1)
        throw (std::string("MessageAnswer::send") );
};

MessageAnswer::~MessageAnswer()
{
    close(socetHandler);

}

