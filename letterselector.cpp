#include "letterselector.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

LetterSelector::LetterSelector(QAbstractItemModel* strings, std::int32_t letterPosition, QWidget* parent)
: QWidget(parent)
, mLetterPosition(letterPosition)
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

    auto* pinButton = new QToolButton(this);
    pinButton->setText("P");
    pinButton->setCheckable(true);
    connect(pinButton, &QToolButton::toggled, &mListView, &QWidget::setDisabled);
    auto emitSelection = [this](bool checked) {
        const auto text = getSelectedText();
        if (!text.isEmpty()) {
            emit pinnedChanged(checked, text);
        }
    };
    connect(pinButton, &QToolButton::toggled, &mListView, emitSelection);
    rowLayout->addWidget(pinButton);

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
