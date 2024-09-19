#include <QMainWindow>

#include <QSettings>
#include <QVariantMap>

#include <vector>

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
    QString mSolutionText {"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"};
};
