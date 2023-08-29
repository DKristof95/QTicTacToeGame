#include <QApplication>
//#include "tictactoewidget.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //TicTacToeWidget widget;
    //widget.show();

    MainWindow m;
    m.show();

    return a.exec();
}
