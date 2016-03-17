#include "messager.h"
#include "view.h" // Для печати данных

MessageClient * ms = new MessageClient(8888); //!< Класс для работы с сетью

std::array<Line, global_width> * data = nullptr;

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

    if(buf.reserv == 100) {
        for(int i = 0; i < 576; ++i) {
            // строка * количество байт на пиксель * строка + номер в строке * количество байт на пиксель
            pixels[576 * 4 * buf.number + i * 4] = buf.argb[i].A;
            pixels[576 * 4 * buf.number + i * 4 + 1] = buf.argb[i].R; // * 4 
            pixels[576 * 4 * buf.number + i * 4 + 2] = buf.argb[i].G; // * 4 
            pixels[576 * 4 * buf.number + i * 4 + 3] = buf.argb[i].B;
            if(buf.number < 5 || buf.number > 718 )
                std::cout << buf.number << "  = " << 576 * 4 * buf.number + i * 4 << 576 * 4 * buf.number + i * 4 + 1<< 576 * 4 * buf.number + i * 4  + 2 << 576 * 4 * buf.number + i * 4  + 3<< "\n";
        }
        if(buf.number >= 718)
            m_finish = true;

    };

    if(m_finish) {
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
        const std::chrono::nanoseconds sleep_time(1000);

        while(1) {
            for(std::uint16_t i = 0; i < global_width; ++i) {
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

