#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    QApplication::setOrganizationName("Edersasch_Opensource");
    QApplication::setApplicationName("GeisterErbenNichtHelper");
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
