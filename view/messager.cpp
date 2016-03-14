#include "messager.h"
#include "view.h" // Для печати данных


MessageClient * ms = nullptr; //!< Класс для работы с сетью

#include <random>

class Generator {
    //    std::random_device rd;
    std::mt19937 * generator;
    std::uniform_int_distribution<std::int8_t> * dis;

public:

    Generator(std::int8_t seed, std::int8_t min, std::int8_t max)
    {
        generator = new std::mt19937(seed);
        dis = new std::uniform_int_distribution<std::int8_t>( min, max );
    }

    std::int8_t gen()
    {
        return (*dis )( *generator );
    }
};


Generator RanGen(0, 200, 255);

void messageClientThread()
{
    MessageClient mc(8888);

    ms = &mc;

    //    const std::chrono::nanoseconds sleep_time(10);
    //    // Цыкл прослушивания
    //    while(1)
    //    {
    //        if(request) {
    //            char tmp = request;
    //            request = 0;
    //            mc.send(tmp);
    //        } else std::this_thread::sleep_for(sleep_time);
    //    }

    //    char buf[BUFLEN];
    //    char message[BUFLEN];


    while(1) {
        for(int i = 0; i < 720 * 576 * 4; ++i) {
            pixels[i] = RanGen.gen();
            //        std::cout << " " << (std::int8_t)pixels[i];
        }
        ms->sendSignal();
        //ms->event(ms->getMessage());
    };


};

MessageClient::MessageClient(std::uint16_t PORT)
{

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

void MessageClient::sendSignal()
{
    emit getMessage();
}

MessageAnswer::MessageAnswer(std::uint16_t PORT)
{

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

MessageAnswer::~MessageAnswer()
{
    close(socetHandler);

}

