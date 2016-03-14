#include <iostream>
#include "messager.h"
#include "view.h"
#include "widget.h"

char * pixels = new char[720 * 576 * 4]; // 4 - байта в каждом пикселе - rgba // 2 - запас

void run_form(int argc, char** argv)
{
}

int main(int argc, char** argv)
{
try {
    data = new std::array<Line, global_width>();
    
    std::cout << "Started \n";
    std::thread mcThread(messageClientThread);
    std::thread maThread(messageAnswerThread);




    QApplication MainApp(argc, argv);
    Widget w(0);

    //    connect(this, SIGNAL(mailto()), &w, SLOT(getmail()));




    std::cout << " mcThread Started \n";
    mcThread.detach();
    std::cout << " maThread Started \n";
    maThread.detach();

    w.show();
    MainApp.exec();


//    const std::chrono::nanoseconds sleep_time(1000000);


//            std::this_thread::sleep_for(sleep_time);



    run_form(argc, argv);

    }
    catch(std::string str) {
        std::cout << "catched " << str << "\n";
    }

    //    run_msg();

    return 0;
}

