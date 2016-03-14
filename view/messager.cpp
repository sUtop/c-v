#include "messager.h"
#include "view.h" // Для печати данных


MessageClient * ms = nullptr; //!< Класс для работы с сетью

std::array<Line, global_width> * data = nullptr;

#include <random>

//class Generator {
//    //    std::random_device rd;
//    std::mt19937 * generator;
//    std::uniform_int_distribution<std::int8_t> * dis;
//
//public:
//
//    Generator(std::int8_t seed, std::int8_t min, std::int8_t max)
//    {
//        generator = new std::mt19937(seed);
//        dis = new std::uniform_int_distribution<std::int8_t>( min, max );
//    }
//
//    std::int8_t gen()
//    {
//        return (*dis )( *generator );
//    }
//};

//Generator RanGen(0, 200, 255);

void messageClientThread()
{
    MessageClient mc(8888);

    ms = &mc;

//    const std::chrono::nanoseconds sleep_time(10);
    while(1) {
        //        for(int i = 0; i < 720 * 576 * 4; ++i) {
        //            pixels[i] = RanGen.gen();
        //        }

        mc.getOnce();
        //        std::this_thread::sleep_for(sleep_time);

    };


};

MessageClient::MessageClient(std::uint16_t PORT)
{

    m_finish = false;
    si_me = new sockaddr_in();
    si_other = new sockaddr_in();

    slen = sizeof (sockaddr_in );

    //Открытие UDP сокета
    if(( socetHandler = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == -1)
        throw (std::string("socket") );

    si_other->sin_family = AF_INET;
    si_other->sin_port = htons(PORT);

    si_other->sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    // #define SERVER "127.0.0.1"
    //    if (inet_aton(SERVER, &si_other->sin_addr) == 0)
    //        throw(std::string("inet_aton"));

}

void MessageClient::getOnce()
{

    Line * buf;
    if(recvfrom(socetHandler, buf, sizeof (Line), 0, (struct sockaddr *) si_other, &slen) == -1)
        throw (std::string("MessageClient::getOnce\n") );

    // if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)

    //    if(sendto(socetHandler, &message, sizeof (std::uint16_t ), 0, (struct sockaddr *) si_other, slen) == -1)
    
    std::cout << " Geted               MessageClient   " << buf->number << "\n";

    //  char * pixels = new char[720 * 576 * 4]; // 4 - байта в каждом пикселе - rgba
    //    PixelARGB argb[576]; // Данные о цвете       [2304 байт]

    if(buf->reserv == 100) {
        //        data->at(buf->number);
        for(int i = 0; i < 576; ++i) {
            pixels[720 * 4 * buf->number + i] = buf->argb[i].A;
            pixels[720 * 4 * buf->number + i + 1] = buf->argb[i].R;
            pixels[720 * 4 * buf->number + i + 2] = buf->argb[i].G;
            pixels[720 * 4 * buf->number + i + 3] = buf->argb[i].B;
        }
        if(buf->number > 700)
            m_finish = true;
        
        
        
    };

    delete buf;
    
    if(m_finish) {
        std::cout << " !!!!!     ==================================================       !!!!!!!!!!!\n";
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
    MessageAnswer ma(7777);
    const std::chrono::nanoseconds sleep_time(100);


    while(1) {
        for(std::uint16_t i = 0; i < global_width; ++i) {
            ma.send(i);
            std::this_thread::sleep_for(sleep_time);
        }

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

