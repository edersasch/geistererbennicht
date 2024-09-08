#include <QWidget>
#include <QSortFilterProxyModel>
#include <QListView>

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

private:
    QModelIndex getSelectedIndex();
    QString getSelectedText();

    const std::int32_t mId;
    QListView mListView;
    QSortFilterProxyModel mFilterModel {};
    const std::int32_t mLetterPosition;
    QStringList mFilteredStrings;
    QToolButton* mPinButton;
    QChar mLetter {'_'};
};
