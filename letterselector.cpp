#include "letterselector.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

LetterSelector::LetterSelector(int32_t selectorId, QAbstractItemModel* strings, std::int32_t letterPosition, QWidget* parent)
: QWidget(parent)
, mId(selectorId)
, mLetterPosition(letterPosition)
, mPinButton(new QToolButton(this))
{
    mFilterModel.setSourceModel(strings);

    auto* mainLayout = new QVBoxLayout(this);

    mListView.setModel(&mFilterModel);
    mListView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    mListView.setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(&mListView);

    auto* rowLayout = new QHBoxLayout;

    auto* letterLabel = new QLabel(this);
    auto updateLetterLabel = [this, letterLabel] {
        const auto text = getSelectedText();
        emit stateChanged(mId, false, text);
        std::int32_t pos = 0;
        for (const auto letter : text) {
            if (!letter.isSpace()) {
                if (pos == mLetterPosition) {
                    letterLabel->setText(letter.toUpper());
                    return;
                }
                pos += 1;
            }
        }
    };
    connect(mListView.selectionModel(), &QItemSelectionModel::selectionChanged, this, updateLetterLabel);
    rowLayout->addWidget(letterLabel);

    mPinButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    mPinButton->setCheckable(true);
    connect(mPinButton, &QToolButton::toggled, &mListView, &QWidget::setDisabled);
    auto emitSelection = [this](bool checked) {
        const auto text = getSelectedText();
        if (!text.isEmpty()) {
            emit stateChanged(mId, checked, text);
        }
    };
    connect(mPinButton, &QToolButton::toggled, &mListView, emitSelection);
    rowLayout->addWidget(mPinButton);

    mainLayout->addLayout(rowLayout);
}

LetterSelector::~LetterSelector() = default;

void LetterSelector::updateFilter(bool enable, const QString& text)
{
    const auto selectedText = getSelectedText();
    if (!mListView.isEnabled() && selectedText == text) {
        return;
    }
    if (enable) {
        mFilteredStrings.removeAll(text);
    } else {
        mFilteredStrings.append(text);
    }
    QString filter;
    if (!mFilteredStrings.empty()) {
        // https://stackoverflow.com/questions/8610743/how-to-negate-any-regular-expression-in-java
        filter = QString("^(?!") + mFilteredStrings.join('|') + "$).*$";
    }
    mFilterModel.setFilterRegularExpression(filter);
}

void LetterSelector::setState(bool pin, const QString& text)
{
    for (int i = 0; i < mFilterModel.rowCount(); i += 1) {
        const auto idx = mFilterModel.index(i, 0);
        const auto textData = mFilterModel.data(idx).toString();
        if (textData == text) {
            mListView.selectionModel()->select(idx, QItemSelectionModel::Select);
            mPinButton->setChecked(pin);
            break;
        }
    }
}

// private

QString LetterSelector::getSelectedText()
{
    QString text;
    const auto idxs = mListView.selectionModel()->selectedIndexes();
    if (!idxs.empty()) {
        const auto idx = idxs.first();
        text = mFilterModel.data(idx).toString();
    }
    return text;
}
