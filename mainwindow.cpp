#include "mainwindow.hpp"
#include "letterselector.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QStringListModel>

#include <string>
#include <string_view>
#include <array>
#include <cstdint>

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

MainWindow::MainWindow()
{
    QStringList stringList;
    for (const auto wsview : stringArray) {
        stringList.append(QString::fromStdWString(std::wstring(wsview)));
    }
    auto* strings = new QStringListModel(this);
    strings->setStringList(stringList);

    auto* mainWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(mainWidget);

    auto pinnedChanged = [this] (bool isPinned, const QString& text) {
        emit updateFilter(!isPinned, text);
    };

    static constexpr auto entriesPerRow = 5;
    auto addSelectorRow = [this,mainLayout, strings, pinnedChanged] (std::array<std::int32_t, entriesPerRow> positions) {
        auto* row = new QHBoxLayout;
        for (auto pos : positions) {
            auto* letterSel = new LetterSelector(strings, pos);
            row->addWidget(letterSel);
            connect(letterSel, &LetterSelector::pinnedChanged, letterSel, pinnedChanged);
            connect(this, &MainWindow::updateFilter, letterSel, &LetterSelector::updateFilter);
        }
        mainLayout->addLayout(row);
    };
    //              Ornamentenkreuz!    Obstbaum!           Die Pinie!          Rad im Wind!!!      Der Ahorn!
    addSelectorRow({0,                  1,                  2,                  0,                  1});
    //              ?                   ?                   ?                   ?                   Englischer Korb!!!
    addSelectorRow({2,                  3,                  0,                  1,                  2});
    //              ?                   ?                   ?                   ?                   ?
    addSelectorRow({3,                  4,                  0,                  1,                  2});
    //              ?                   ?                   ?                   ?                   Regenbogenfalter!!!
    addSelectorRow({3,                  4,                  5,                  6,                  0});

    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow() = default;
