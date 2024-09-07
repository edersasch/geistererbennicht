#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
