#include <iostream>

// На вход программа получает номер порта 
//   для передачи/приема сообщений


#include "messager.h"

int main(int argc, char** argv)
{
    std::thread sThread(senderThread);
    std::thread rThread(receiverThread);

    sThread.detach();
    rThread.detach();

    const std::chrono::nanoseconds sleep_time(100000);

    while(1) {
        std::this_thread::sleep_for(sleep_time);
    }


    //    try {
    //    MessageSender ms(8888);

    //    ms.send();
    //    }
    //    catch(std::exception e) {
    // ! Проброс исключений для ловли ошибок
    //    }

    return 0;
}

