#include <iostream>

// На вход программа получает номер порта 
//   для передачи/приема сообщений


#include "messager.h"

int main(int argc, char** argv) {
    try {
        std::thread sThread(senderThread);
        std::thread rThread(receiverThread);

        sThread.detach();
        rThread.detach();

        const std::chrono::milliseconds sleep_time(100000);

        while (1) {
            std::this_thread::sleep_for(sleep_time);
        }

    }    catch (std::string str) {
        std::cout << "catched " << str << "\n";
    }



    return 0;
}

