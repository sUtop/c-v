#include <iostream>
#include "messager.h"
#include "view.h"
#include "widget.h"

char * pixels = new char[720 * 576 * 4]; // 4 - байта в каждом пикселе - rgba

void run_form(int argc, char** argv)
{

    QApplication MainApp(argc, argv);
    Widget w(0);

    //    connect(this, SIGNAL(mailto()), &w, SLOT(getmail()));

    w.show();
    MainApp.exec();
}

int main(int argc, char** argv)
{

    data = new std::array<Line, global_width>();
    
    std::cout << "Started \n";
    std::thread mcThread(messageClientThread);
    mcThread.detach();

    std::cout << " mcThread Started \n";
    std::thread maThread(messageAnswerThread);
    maThread.detach();

    std::cout << " maThread Started \n";
    
    run_form(argc, argv);

    //    run_msg();

    return 0;
}

