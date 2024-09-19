#include "letterselector.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QToolButton>
#include <QVBoxLayout>

LetterSelector::LetterSelector(int32_t selectorId, QAbstractItemModel* strings, std::int32_t letterPosition, QWidget* parent)
: QWidget(parent)
, mId(selectorId)
, mLetterPosition(letterPosition)
, mPinButton(new QToolButton(this))
{
    mFilterModel.setSourceModel(strings);

    auto* mainLayout = new QVBoxLayout(this);

    mListView.setEditTriggers(QAbstractItemView::NoEditTriggers);
    mListView.setSelectionMode(QAbstractItemView::SingleSelection);
    mListView.setModel(&mFilterModel);
    mainLayout->addWidget(&mListView);

    auto* rowLayout = new QHBoxLayout;

    auto* positionLabel = new QLabel(QString::number(mLetterPosition + 1) + ": ", this);
    rowLayout->addWidget(positionLabel);

    auto* letterLabel = new QLabel(this);
    auto handleSelectionChanged = [this, letterLabel] {
        const auto text = getSelectedText();
        std::int32_t pos = 0;
        mLetter = '_';
        letterLabel->setText(QString());
        for (const auto letter : text) {
            if (!letter.isSpace()) {
                if (pos == mLetterPosition) {
                    mLetter = letter.toUpper();
                    letterLabel->setText(mLetter);
                    break;
                }
                pos += 1;
            }
        }
        mPinButton->setDisabled(text.isEmpty());
        emit stateChanged(mId, false, text);
    };
    connect(mListView.selectionModel(), &QItemSelectionModel::selectionChanged, this, handleSelectionChanged);
    rowLayout->addWidget(letterLabel);

    auto* picButton = new QToolButton(this);
    picButton->setCheckable(true);
    picButton->setIcon(style()->standardIcon(QStyle::SP_DialogHelpButton));
    rowLayout->addWidget(picButton);

    mPinButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    mPinButton->setCheckable(true);
    connect(mPinButton, &QToolButton::toggled, &mListView, &QWidget::setDisabled);
    auto emitSelection = [this](bool checked) {
        const auto text = getSelectedText();
        emit stateChanged(mId, checked, text);
    };
    connect(mPinButton, &QToolButton::toggled, &mListView, emitSelection);
    handleSelectionChanged();
    rowLayout->addWidget(mPinButton);

    auto* clearButton = new QToolButton(this);
    clearButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    connect(clearButton, &QToolButton::clicked, &mListView, &QAbstractItemView::clearSelection);
    connect(mPinButton, &QToolButton::toggled, clearButton, &QWidget::setDisabled);
    rowLayout->addWidget(clearButton);

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
    const auto idx = getSelectedIndex();
    mListView.scrollTo(idx);
}

void LetterSelector::setState(bool pin, const QString& text)
{
    for (int i = 0; i < mFilterModel.rowCount(); i += 1) {
        const auto idx = mFilterModel.index(i, 0);
        const auto textData = mFilterModel.data(idx).toString();
        if (textData == text) {
            mListView.selectionModel()->select(idx, QItemSelectionModel::Select);
            mListView.scrollTo(idx);
            mPinButton->setChecked(pin);
            break;
        }
    }
}

QChar LetterSelector::getLetter()
{
    return mLetter;
}

// protected

void LetterSelector::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    setBackgroundPicture();
}

void LetterSelector::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    setBackgroundPicture();
}

// private

QModelIndex LetterSelector::getSelectedIndex()
{
    QModelIndex idx;
    const auto idxs = mListView.selectionModel()->selectedIndexes();
    if (!idxs.empty()) {
        idx = idxs.first();
    }
    return idx;
}

QString LetterSelector::getSelectedText()
{
    QString text;
    const auto idx = getSelectedIndex();
    if (idx.isValid()) {
        text = mFilterModel.data(idx).toString();
    }
    return text;
}

void LetterSelector::setBackgroundPicture()
{
    auto img = QImage(":/placeholder.png");
    QImage transparentImg(img.size(), QImage::Format_ARGB32);
    transparentImg.fill(Qt::transparent);
    QPainter painter(&transparentImg);
    painter.setOpacity(0.3);
    painter.drawImage(QRect(0, 0, img.width(), img.height()), img);
    painter.end();
    transparentImg = transparentImg.scaled(mListView.viewport()->width(), mListView.viewport()->height());
    auto pic = QPixmap::fromImage(transparentImg);
    auto palette = mListView.viewport()->palette();
    palette.setBrush(QPalette::Base, QBrush(pic));
    mListView.viewport()->setPalette(palette);
}
