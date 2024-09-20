#ifndef TESTS_LETTERSELECTOR_TEST_HPP
#define TESTS_LETTERSELECTOR_TEST_HPP

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <QObject>

class LetterSelectorSlots
: public QObject
{
    Q_OBJECT
public:
    LetterSelectorSlots();
    ~LetterSelectorSlots() override;

    MOCK_METHOD3(stateChanged, void(std::int32_t selectorId, bool isPinned, const QString& text));
};

#endif // TESTS_LETTERSELECTOR_TEST_HPP
