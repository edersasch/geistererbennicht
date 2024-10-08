#ifndef SRC_LETTERSELECTOR_HPP
#define SRC_LETTERSELECTOR_HPP

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
    ~LetterSelector() override;
    void updateFilter(bool enable, const QString& text);
    void setState(bool pin, const QString& text);
    [[nodiscard]] QChar getLetter() const;
    void setPicture(const QString& path);
    void setSolutionRow(int row);

signals:
    void stateChanged(std::int32_t selectorId, bool isPinned, const QString& text);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    QModelIndex getSelectedIndex();
    QString getSelectedText();
    void setBackgroundPicture(bool transpararent);

    const std::int32_t mId;
    const std::int32_t mLetterPosition;
    QListView mListView;
    QSortFilterProxyModel mFilterModel {};
    QStringList mFilteredStrings;
    QToolButton* mPinButton;
    QToolButton* mSolveButton;
    QChar mLetter {'_'};
    QImage mPicture;
    int mSolutionRow = -1;
};

#endif // SRC_LETTERSELECTOR_HPP
