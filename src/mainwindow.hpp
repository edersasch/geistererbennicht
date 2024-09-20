#ifndef SRC_MAINWINDOW_HPP
#define SRC_MAINWINDOW_HPP

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
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
    void closeEvent(QCloseEvent* event) override;

signals:
    void updateFilter(bool enable, const QString& text);

private:
    std::vector<LetterSelector*> mLetterSelectors;
    QVariantMap mSelectorState;
    QString mSolutionText {"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"};
};

#endif // SRC_MAINWINDOW_HPP
