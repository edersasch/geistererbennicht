#include <QWidget>
#include <QSortFilterProxyModel>
#include <QListView>

#include <cstdint>

class LetterSelector
: public QWidget
{
    Q_OBJECT

public:
    LetterSelector(QAbstractItemModel* strings, std::int32_t letterPosition, QWidget* parent = nullptr);
    ~LetterSelector();
    void updateFilter(bool enable, const QString& text);

signals:
    void pinnedChanged(bool isPinned, const QString& text);

private:
    QString getSelectedText();

    QListView mListView;
    QSortFilterProxyModel mFilterModel {};
    std::int32_t mLetterPosition;
    QStringList mFilteredStrings;
};
