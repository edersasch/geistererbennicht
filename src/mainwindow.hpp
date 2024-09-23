#ifndef SRC_MAINWINDOW_HPP
#define SRC_MAINWINDOW_HPP

#include <QMainWindow>

#include <QSettings>
#include <QVariantMap>

#include <memory>
#include <vector>

class LetterSelector;
class QCloseEvent;
class QLabel;

class PicView
: public QWidget
{
public:
    PicView(QWidget* parent = nullptr);
    ~PicView() override;

protected:
    void resizeEvent(QResizeEvent* event) override;
    QPixmap mPic;
    QLabel* mPicLabel;
};

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
    std::unique_ptr<PicView> mPicView = nullptr;
};

#endif // SRC_MAINWINDOW_HPP
