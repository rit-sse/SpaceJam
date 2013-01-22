#include <iostream>

#include <QApplication>


#include "window.h"


using namespace std;


int main(int argv, char ** argc){
    cout << "hello world" << endl;
    QApplication app(argv, argc);


    Window w;
    w.show();



    // starts all the event loops and stuff
    app.exec();

}
