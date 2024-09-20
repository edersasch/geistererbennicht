#include "letterselector.test.hpp"

#include "letterselector.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <QApplication>
#include <QListView>
#include <QStringListModel>

#include <memory>

LetterSelectorSlots::LetterSelectorSlots() = default;
LetterSelectorSlots::~LetterSelectorSlots() = default;

LetterSelectorSlots* getConnectedSlots(LetterSelector* letsel)
{
    auto* ret = new LetterSelectorSlots;
    QObject::connect(letsel, &LetterSelector::stateChanged, ret, &LetterSelectorSlots::stateChanged);
    return ret;
}

TEST(LetterSelector_Test, noModel)
{
    auto* letsel = new LetterSelector(0, nullptr, 0);
    EXPECT_EQ(QChar('_'), letsel->getLetter());
}

TEST(LetterSelector_Test, singleEntry)
{
    QStringListModel model;
    std::unique_ptr<LetterSelector> letsel(new LetterSelector(0, &model, 0));
    std::unique_ptr<LetterSelectorSlots> mockSlots(getConnectedSlots(letsel.get()));
    EXPECT_EQ(QChar('_'), letsel->getLetter());
    model.setStringList({"one"});
    EXPECT_EQ(QChar('_'), letsel->getLetter());
    auto* listView = letsel->findChild<QListView*>("ListView");
    auto idx = listView->model()->index(0, 0);
    EXPECT_CALL(*mockSlots, stateChanged(0, false, QString("one")));
    listView->selectionModel()->select(idx, QItemSelectionModel::SelectCurrent);
    EXPECT_EQ(QChar('O'), letsel->getLetter());
}

TEST(LetterSelector_Test, entries)
{
    QStringListModel model;
    static constexpr auto selectorid = 5;
    static constexpr auto letterPosition = 9;
    std::unique_ptr<LetterSelector> letsel(new LetterSelector(selectorid, &model, letterPosition));
    std::unique_ptr<LetterSelectorSlots> mockSlots(getConnectedSlots(letsel.get()));
    EXPECT_EQ(QChar('_'), letsel->getLetter());
    model.setStringList({"onewithoutspaces", "two with spaces"});
    EXPECT_EQ(QChar('_'), letsel->getLetter());
    auto* listView = letsel->findChild<QListView*>("ListView");
    auto idx = listView->model()->index(0, 0);
    EXPECT_CALL(*mockSlots, stateChanged(selectorid, false, QString("onewithoutspaces")));
    listView->selectionModel()->select(idx, QItemSelectionModel::SelectCurrent);
    EXPECT_EQ(QChar('T'), letsel->getLetter());
    idx = listView->model()->index(1, 0);
    EXPECT_CALL(*mockSlots, stateChanged(selectorid, false, QString("two with spaces")));
    listView->selectionModel()->select(idx, QItemSelectionModel::SelectCurrent);
    EXPECT_EQ(QChar('A'), letsel->getLetter());
}
