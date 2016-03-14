#include "messager.h"
#include "view.h" // Для печати данных


MessageClient * ms = new MessageClient(8888); //!< Класс для работы с сетью

std::array<Line, global_width> * data = nullptr;

void messageClientThread()
{
    try {
//    MessageClient mc(8888);

        ms->init();
//    ms = &mc;

    while(1) {

        ms->getOnce();
        //        std::this_thread::sleep_for(sleep_time);

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

    if(buff != 404) throw(std::string("wtf" + std::to_string(buff)));
    else std::cout << " Correct handshake ! \n";

}

void MessageClient::getOnce()
{

    Line buf;
    int i = recvfrom(socetHandler, &buf, sizeof (Line), 0, (struct sockaddr *) si_other, &slen);
    if(i == -1) {
        std::cout << "geted " << i << " " << errno << "\n";
        return;
    }
    
//    std::cout << " Geted               MessageClient   " << buf.number << " " << buf.reserv <<"\n";

    //  char * pixels = new char[720 * 576 * 4]; // 4 - байта в каждом пикселе - rgba
    //    PixelARGB argb[576]; // Данные о цвете       [2304 байт]

    if(buf.reserv == 100) {
        //        data->at(buf->number);
        for(int i = 0; i < 576; ++i) {
            pixels[575 * buf.number * 4 + i] = buf.argb[i].A;
            pixels[575 * buf.number * 4 + i + 1] = buf.argb[i].R;
            pixels[575 * buf.number * 4 + i + 2] = buf.argb[i].G;
            pixels[575 * buf.number * 4 + i + 3] = buf.argb[i].B;
        }
        if(buf.number >= 718)
            m_finish = true;
        
        
        
    };

//    delete buf;
    
    if(m_finish) {
//        std::cout << " !!!!!     ==================================================       !!!!!!!!!!!\n";
        sendSignal();
        m_finish = false;
    }

};

void MessageClient::sendSignal()
{
    emit getMessage();
}

void messageAnswerThread()
{

    try {
    MessageAnswer ma(7777);
//    const std::chrono::milliseconds sleep_time(100);


    while(1) {
        for(std::uint16_t i = 0; i < global_width; ++i) {
            ma.send(i);
//            std::this_thread::sleep_for(sleep_time);
        }

    }

    }
    catch(std::string str) {
        std::cout << "catched " << str << "\n";
    }


    //          Пересылка запросов
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

//     #define SERVER "127.0.0.1"
//        if (inet_aton(SERVER, &si_other->sin_addr) == 0)
//            throw(std::string("inet_aton"));

}

void MessageAnswer::send(std::uint16_t & message)
{
//        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
    std::uint16_t tmp = message;
//    std::cout << " send " << sendto(socetHandler, &tmp, sizeof (std::uint16_t ), 0, (struct sockaddr *) si_other, slen) <<
//            "  " << message << "  " << sizeof (std::uint16_t ) << "  " << si_other->sin_port <<"\n";

    if(sendto(socetHandler, &message, sizeof (std::uint16_t ), 0, (struct sockaddr *) si_other, slen) == -1)
        throw (std::string("MessageAnswer::send") );
};

MessageAnswer::~MessageAnswer()
{
    close(socetHandler);

}

