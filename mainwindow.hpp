#include <QMainWindow>

class MainWindow
: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

signals:
    void updateFilter(bool enable, const QString& text);
};
