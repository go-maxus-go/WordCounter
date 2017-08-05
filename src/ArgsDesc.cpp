#include "ArgsDesc.h"

ArgsDesc::ArgsDesc()
{
    auto addArg = [this](auto arg, auto type, auto desc)
    {
        m_args.push_back(arg);
        m_arg2type[arg] = type;
        m_type2arg[type] = arg;
        m_type2desc[type] = desc;
    };
    addArg("-f", ArgType::File, "Input file path");
    addArg("-m", ArgType::Mode, "Operating mode");
    addArg("-v", ArgType::Word, "Word parameter");
    addArg("-h", ArgType::Help, "Show help");

    auto addMode = [this](auto mode, auto type, auto desc)
    {
        m_mode2modeType[mode] = type;
        m_modeType2desc[type] = desc;
    };
    addMode("words"   , ModeType::Words   , "Count words in file");
    addMode("checksum", ModeType::CheckSum, "Count file checksum");
}
std::list<std::string> ArgsDesc::args() const
{
    return m_args;
}
std::string ArgsDesc::arg(ArgType type) const
{
    auto it = m_type2arg.find(type);
    return it == m_type2arg.end() ? std::string() : it->second;
}
std::string ArgsDesc::desc(ArgType type) const
{
    auto it = m_type2desc.find(type);
    return it == m_type2desc.end() ? std::string() : it->second;
}
std::string ArgsDesc::desc(ModeType type) const
{
    auto it = m_modeType2desc.find(type);
    return it == m_modeType2desc.end() ? std::string() : it->second;
}
ArgsDesc::ArgType ArgsDesc::type(const std::string & name) const
{
    auto it = m_arg2type.find(name);
    return it == m_arg2type.end() ? ArgType::Invalid : it->second;
}
ArgsDesc::ModeType ArgsDesc::mode(const std::string & name) const
{
    auto it = m_mode2modeType.find(name);
    return it == m_mode2modeType.end() ? ModeType::Invalid : it->second;
}
