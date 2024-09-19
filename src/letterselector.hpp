#include <QListView>
#include <QSortFilterProxyModel>
#include <QWidget>

#include <cstdint>

class QToolButton;

class LetterSelector
: public QWidget
{
    Q_OBJECT

public:
    LetterSelector(std::int32_t selectorId, QAbstractItemModel* strings, std::int32_t letterPosition, QWidget* parent = nullptr);
    ~LetterSelector();
    void updateFilter(bool enable, const QString& text);
    void setState(bool pin, const QString& text);
    QChar getLetter();

signals:
    void stateChanged(std::int32_t selectorId, bool isPinned, const QString& text);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    QModelIndex getSelectedIndex();
    QString getSelectedText();
    void setBackgroundPicture();

    const std::int32_t mId;
    QListView mListView;
    QSortFilterProxyModel mFilterModel {};
    const std::int32_t mLetterPosition;
    QStringList mFilteredStrings;
    QToolButton* mPinButton;
    QChar mLetter {'_'};
};
