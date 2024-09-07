#include <QMainWindow>

#include <vector>
#include <QVariantMap>
#include <QSettings>

class LetterSelector;
class QCloseEvent;

class MainWindow
: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void closeEvent(QCloseEvent* event) override;

signals:
    void updateFilter(bool enable, const QString& text);

private:
    std::vector<LetterSelector*> mLetterSelectors;
    QVariantMap mSelectorState;
};
