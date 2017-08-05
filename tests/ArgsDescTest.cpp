#include "ArgsDescTest.h"

#include <QTest>

#include <set>
#include <algorithm>

#include "ArgsDesc.h"

void ArgsDescTest::availableArguments()
{
    std::set<std::string> args;
    {
        auto a = ArgsDesc::get().args();
        std::copy(a.begin(), a.end(), std::inserter(args, args.begin()));
    }
    QCOMPARE(args.size(), ArgsDesc::get().args().size());

    QVERIFY(args.find("-f") != args.end());
    QVERIFY(args.find("-m") != args.end());
    QVERIFY(args.find("-v") != args.end());
    QVERIFY(args.find("-h") != args.end());
}
void ArgsDescTest::correctArgumentsValueAndType()
{
    const auto & argsDesc = ArgsDesc::get();

    std::set<ArgsDesc::ArgType> types;
    for (auto arg : argsDesc.args())
    {
        auto type = argsDesc.type(arg);
        QVERIFY(type != ArgsDesc::ArgType::Invalid);
        types.insert(type);
    }
    QCOMPARE(types.size(), argsDesc.args().size());

    QCOMPARE(argsDesc.mode("words"  ), ArgsDesc::ModeType::Words);
    QCOMPARE(argsDesc.mode("checksum"), ArgsDesc::ModeType::CheckSum);
}
void ArgsDescTest::descriptionIsFilled()
{
    const auto & argsDesc = ArgsDesc::get();
    for (auto arg : argsDesc.args())
        QVERIFY(argsDesc.desc(argsDesc.type(arg)).empty() == false);

    QVERIFY(argsDesc.desc(ArgsDesc::ModeType::Words   ).empty() == false);
    QVERIFY(argsDesc.desc(ArgsDesc::ModeType::CheckSum).empty() == false);
}
