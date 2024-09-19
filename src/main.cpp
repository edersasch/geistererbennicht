#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    Q_INIT_RESOURCE(pics);
    QApplication::setOrganizationName("Edersasch_Opensource");
    QApplication::setApplicationName("GeisterErbenNichtHelper");
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
