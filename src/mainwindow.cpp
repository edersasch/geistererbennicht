#include "mainwindow.hpp"

#include "letterselector.hpp"

#include <QCloseEvent>
#include <QLabel>
#include <QStandardPaths>
#include <QStringList>
#include <QStringListModel>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

#ifdef _WIN32
constexpr std::string_view ahorn_1 =        "Der Ahorn";
constexpr std::string_view hoffenster_2 =   "Hoffenster";
constexpr std::string_view englkorb_3 =     "Englischer Korb";
constexpr std::string_view rgbfalter_4 =    "Regenbogenfalter";
constexpr std::string_view straute_5 =      "Sternenraute";
constexpr std::string_view obstbaum_6 =     "Obstbaum";
constexpr std::string_view wspule_7 =       "Weberspule";
constexpr std::string_view lmitte_8 =       "Lebensmitte";
constexpr std::string_view fstern_9 =       "Frühlingsstern";
constexpr std::string_view plus_10 =        "Plusfläche";
constexpr std::string_view bltri_11 =       "Blaue Triangel";
constexpr std::string_view okreuz_12 =      "Ornamentenkreuz";
constexpr std::string_view rwind_13 =       "Rad im Wind";
constexpr std::string_view grot_14 =        "Gerade in Rot";
constexpr std::string_view igelh_15 =       "Igels Haus";
constexpr std::string_view hegelg_16 =      "Hegels Gesetz";
constexpr std::string_view estern_17 =      "Stern von Eliza";
constexpr std::string_view pinie_18 =       "Die Pinie";
constexpr std::string_view ksonne_19 =      "Im Kreis der Sonne";
constexpr std::string_view sigo_20 =        "Silber & Gold";

constexpr std::array<std::string_view, 20> stringArray
{
    ahorn_1,        hoffenster_2,       englkorb_3,     rgbfalter_4,        straute_5,
    obstbaum_6,     wspule_7,           lmitte_8,       fstern_9,           plus_10,
    bltri_11,       okreuz_12,          rwind_13,       grot_14,            igelh_15,
    hegelg_16,      estern_17,          pinie_18,       ksonne_19,          sigo_20
};
#else
constexpr std::wstring_view ahorn_1 =       L"Der Ahorn";
constexpr std::wstring_view hoffenster_2 =  L"Hoffenster";
constexpr std::wstring_view englkorb_3 =    L"Englischer Korb";
constexpr std::wstring_view rgbfalter_4 =   L"Regenbogenfalter";
constexpr std::wstring_view straute_5 =     L"Sternenraute";
constexpr std::wstring_view obstbaum_6 =    L"Obstbaum";
constexpr std::wstring_view wspule_7 =      L"Weberspule";
constexpr std::wstring_view lmitte_8 =      L"Lebensmitte";
constexpr std::wstring_view fstern_9 =      L"Frühlingsstern";
constexpr std::wstring_view plus_10 =       L"Plusfläche";
constexpr std::wstring_view bltri_11 =      L"Blaue Triangel";
constexpr std::wstring_view okreuz_12 =     L"Ornamentenkreuz";
constexpr std::wstring_view rwind_13 =      L"Rad im Wind";
constexpr std::wstring_view grot_14 =       L"Gerade in Rot";
constexpr std::wstring_view igelh_15 =      L"Igels Haus";
constexpr std::wstring_view hegelg_16 =     L"Hegels Gesetz";
constexpr std::wstring_view estern_17 =     L"Stern von Eliza";
constexpr std::wstring_view pinie_18 =      L"Die Pinie";
constexpr std::wstring_view ksonne_19 =     L"Im Kreis der Sonne";
constexpr std::wstring_view sigo_20 =       L"Silber & Gold";

constexpr std::array<std::wstring_view, 20> stringArray
{
    ahorn_1,        hoffenster_2,       englkorb_3,     rgbfalter_4,        straute_5,
    obstbaum_6,     wspule_7,           lmitte_8,       fstern_9,           plus_10,
    bltri_11,       okreuz_12,          rwind_13,       grot_14,            igelh_15,
    hegelg_16,      estern_17,          pinie_18,       ksonne_19,          sigo_20
};
#endif

constexpr std::array<std::string_view, 20> picArray
{
    ":/r1c1", ":/r1c2", ":/r1c3", ":/r1c4", ":/r1c5",
    ":/r2c1", ":/r2c2", ":/r2c3", ":/r2c4", ":/r2c5",
    ":/r3c1", ":/r3c2", ":/r3c3", ":/r3c4", ":/r3c5",
    ":/r4c1", ":/r4c2", ":/r4c3", ":/r4c4", ":/r4c5",
};

constexpr auto selectorState = "SelectorState";
namespace
{

QSettings getSettings()
{
    const auto settingsLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return {settingsLocation, QSettings::IniFormat};
}

}

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent)
{
    static_assert(stringArray.size() == picArray.size());
    QStringList stringList;
    stringList.reserve(stringArray.size());
    for (const auto str : stringArray) {
#ifdef _WIN32
        stringList.append(QString::fromStdString(std::string(str)));
#else
        stringList.append(QString::fromStdWString(std::wstring(str)));
#endif
    }
    auto* strings = new QStringListModel(this);
    strings->setStringList(stringList);

    auto* mainWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(mainWidget);

    auto updateWindowTitle = [this] {
        setWindowTitle("Geister erben nicht: " + mSolutionText);
    };
    updateWindowTitle();

    auto stateChanged = [this, updateWindowTitle] (std::int32_t selectorId, bool isPinned, const QString& text) {
        const auto sel = QString::number(selectorId);
        const auto pin = isPinned ? QString("true") : QString("false");
        mSelectorState[sel] = QStringList{pin, text};
        const auto letter = mLetterSelectors[static_cast<std::size_t>(selectorId)]->getLetter();
        mSolutionText[selectorId * 2] = letter;
        updateWindowTitle();
        emit updateFilter(!isPinned, text);
    };

    static constexpr auto entriesPerRow = 5;
    std::int32_t selectorId = 0;
    mLetterSelectors.reserve(stringArray.size());
    auto addSelectorRow = [this, mainLayout, strings, stateChanged, &selectorId] (std::array<std::int32_t, entriesPerRow> positions) {
        auto* row = new QHBoxLayout;
        for (auto pos : positions) {
            auto* letterSel = new LetterSelector(selectorId, strings, pos, this);
            letterSel->setPicture(picArray.at(static_cast<std::size_t>(selectorId)).data());
            row->addWidget(letterSel);
            connect(letterSel, &LetterSelector::stateChanged, letterSel, stateChanged);
            connect(this, &MainWindow::updateFilter, letterSel, &LetterSelector::updateFilter);
            mLetterSelectors.push_back(letterSel);
            selectorId += 1;
        }
        mainLayout->addLayout(row);
    };
    static constexpr auto letter5 = 5;
    static constexpr auto letter6 = 6;
    //              Ornamentenkreuz!    Obstbaum!           Die Pinie!          Rad im Wind!!!      Der Ahorn!
    addSelectorRow({0,                  1,                  2,                  0,                  1});
    //              ?                   ?                   ?                   ?                   Englischer Korb!!!
    addSelectorRow({2,                  3,                  0,                  1,                  2});
    //              ?                   ?                   ?                   ?                   ?
    addSelectorRow({3,                  4,                  0,                  1,                  2});
    //              ?                   ?                   ?                   ?                   Regenbogenfalter!!!
    addSelectorRow({3,                  4,                  letter5,            letter6,            0});

    auto* toolBar = addToolBar("main");
    toolBar->setMovable(false);

    auto* picButton = new QToolButton(this);
    picButton->setIcon(style()->standardIcon(QStyle::SP_DialogHelpButton));
    connect(picButton, &QToolButton::clicked, this, [this] {
        if (mPicView == nullptr) {
            mPicView = new QWidget;
            auto* picLabel = new QLabel(mPicView);
            picLabel->setPixmap(QPixmap(":/complete.jpg"));
            auto* picLayout = new QHBoxLayout(mPicView);
            picLayout->addWidget(picLabel);
        }
        mPicView->show();
    });
    toolBar->addWidget(picButton);

    setCentralWidget(mainWidget);

    const auto settings = getSettings();
    mSelectorState = settings.value(selectorState).toMap();
    auto itr = mSelectorState.cbegin();
    while (itr != mSelectorState.cend()) {
        selectorId = itr.key().toInt();
        if (selectorId >= 0 && selectorId < 4 * entriesPerRow) {
            const auto state = itr.value().toStringList();
            if (state.size() == 2) {
                auto setState = [this, state, selectorId] {
                    const bool pinned = state[0] == "true";
                    const auto& text = state[1];
                    mLetterSelectors[static_cast<std::size_t>(selectorId)]->setState(pinned, text);
                };
                QTimer::singleShot(0, this, setState);
            }
        }
        itr++;
    }
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent *event)
{
    auto settings = getSettings();
    settings.setValue(selectorState, mSelectorState);
    event->accept();
}
