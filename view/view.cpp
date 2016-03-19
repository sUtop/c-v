#include <iostream>
#include "messager.h"
#include "view.h"
#include "widget.h"

char * pixels = new char[720 * 576 * 4]; // 4 - байта в каждом пикселе - rgba // 2 - запас

int main(int argc, char** argv) {
    try {
        std::cout << "Started \n";
        std::thread mcThread(messageClientThread);
        std::thread maThread(messageAnswerThread);

        QApplication MainApp(argc, argv);
        Widget w(0);

        std::cout << " mcThread Started \n";
        mcThread.detach();
        std::cout << " maThread Started \n";
        maThread.detach();

        w.show();
        MainApp.exec();


    }    catch (std::string str) {
        std::cout << "catched " << str << "\n";
    }

    return 0;
}

