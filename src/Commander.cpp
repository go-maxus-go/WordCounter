#include "Commander.h"

#include <algorithm>

#include "ArgsDesc.h"
#include "CommandParser.h"

class Commander::Impl
{
    using Command = Commander::Command;
    using ArgType = ArgsDesc::ArgType;
public:
    Command retrieveCommand(int argc, char * argv[])
    {
        auto & argsDesc = ArgsDesc::get();
        std::list<std::string> args;
        for (int i = 1; i < argc; ++i)
            args.push_back(std::string(argv[i]));

        const auto options = argsDesc.args();
        for (auto option : options)
            m_parser.setOption(option);

        if (!m_parser.parse(args))
            return Command::Invalid;
        if (m_parser.isSet(""))
            return Command::Invalid;

        auto optionCount = std::count_if(options.begin(), options.end(),
            [this](auto o){ return m_parser.isSet(o); });
        // Help
        auto helpValues = m_parser.values(argsDesc.arg(ArgType::Help));
        if (m_parser.isSet(argsDesc.arg(ArgType::Help)))
            return (optionCount == 1 && helpValues.empty())
                   ? Command::Help : Command::Invalid;

        parseFile();
        parseMode();
        parseWord();

        switch (m_mode)
        {
        case ArgsDesc::ModeType::CheckSum:
            return m_file.empty() || m_parser.isSet(argsDesc.arg(ArgType::Word))
                   ? Command::Invalid : Command::CheckSum;
        case ArgsDesc::ModeType::Words:
            return m_file.empty() || m_word.empty()
                   ? Command::Invalid : Command::CountWord;
        default: return Command::Invalid;
        }
        return Command::Invalid;
    }
    std::string file() const { return m_file; }
    std::string word() const { return m_word; }
private:
    void parseFile()
    {
        if (!isSingleOption((ArgType::File)))
            return;
        m_file = *m_parser.values(ArgsDesc::get().arg(ArgType::File)).begin();
    }
    void parseMode()
    {
        if (!isSingleOption((ArgType::Mode)))
            return;
        auto mode = *m_parser.values(ArgsDesc::get().arg(ArgType::Mode)).begin();
        m_mode = ArgsDesc::get().mode(mode);
    }
    void parseWord()
    {
        if (!isSingleOption((ArgType::Word)))
            return;
        m_word = *m_parser.values(ArgsDesc::get().arg(ArgType::Word)).begin();
    }
    bool isSingleOption(ArgType type)
    {
        auto & argsDesc = ArgsDesc::get();
        if (!m_parser.isSet(argsDesc.arg(type)))
            return false;
        if (m_parser.values(argsDesc.arg(type)).size() != 1)
            return false;
        return true;
    }
private:
    CommandParser m_parser;
    std::string m_file;
    std::string m_word;
    ArgsDesc::ModeType m_mode = ArgsDesc::ModeType::Invalid;
};

Commander::Commander() : m_impl(new Impl) {}
Commander::~Commander() = default;

Commander::Command Commander::retrieveCommand(int argc, char * argv[])
    { return m_impl->retrieveCommand(argc, argv); }
std::string Commander::file() const
    { return m_impl->file(); }
std::string Commander::word() const
    { return m_impl->word(); }
