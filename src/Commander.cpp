#include "Commander.h"

#include <algorithm>

#include "ArgsDesc.h"
#include "ArgsParser.h"

class Commander::Impl
{
    using Command = Commander::Command;
    using ArgType = ArgsDesc::ArgType;
public:
    Command retrieveCommand(int argc, char * argv[])
    {
        std::list<std::string> args;
        for (int i = 1; i < argc; ++i)
            args.push_back(std::string(argv[i]));

        const auto options = AD.args();
        for (auto option : options)
            m_parser.setOption(option);

        if (!m_parser.parse(args) || m_parser.isSet(""))
            return Command::Invalid;

        auto optionCount = std::count_if(options.begin(), options.end(),
            [this](auto o){ return m_parser.isSet(o); });
        // Help
        auto helpValues = m_parser.values(AD.arg(ArgType::Help));
        if (m_parser.isSet(AD.arg(ArgType::Help)))
            return (optionCount == 1 && helpValues.empty())
                   ? Command::Help : Command::Invalid;

        parseFile();
        parseMode();
        parseWord();

        switch (m_mode)
        {
        case ArgsDesc::ModeType::CheckSum:
            return m_file.empty() || m_parser.isSet(AD.arg(ArgType::Word))
                   ? Command::Invalid : Command::CheckSum;
        case ArgsDesc::ModeType::Words:
            return m_file.empty() || m_word.empty()
                   ? Command::Invalid : Command::CountWord;
        default:
            return Command::Invalid;
        }
        return Command::Invalid;
    }
    std::string file() const { return m_file; }
    std::string word() const { return m_word; }
private:
    void parseFile()
    {
        if (!isSingleOption(ArgType::File))
            return;
        m_file = m_parser.values(AD.arg(ArgType::File)).front();
    }
    void parseMode()
    {
        if (!isSingleOption(ArgType::File))
            return;
        auto mode = m_parser.values(AD.arg(ArgType::Mode)).front();
        m_mode = AD.mode(mode);
    }
    void parseWord()
    {
        if (!isSingleOption(ArgType::Mode))
            return;
        m_word = m_parser.values(AD.arg(ArgType::Word)).front();
    }
    bool isSingleOption(ArgType type)
    {
        if (!m_parser.isSet(AD.arg(type)))
            return false;
        if (m_parser.values(AD.arg(type)).size() != 1)
            return false;
        return true;
    }
private:
    ArgsParser m_parser;
    std::string m_file;
    std::string m_word;
    ArgsDesc::ModeType m_mode = ArgsDesc::ModeType::Invalid;
    const ArgsDesc & AD = ArgsDesc::get();
};

Commander::Commander() : m_impl(new Impl) {}
Commander::~Commander() = default;

Commander::Command Commander::retrieveCommand(int argc, char * argv[])
    { return m_impl->retrieveCommand(argc, argv); }
std::string Commander::file() const
    { return m_impl->file(); }
std::string Commander::word() const
    { return m_impl->word(); }
