#pragma once

#include <map>
#include <list>
#include <string>

class ArgsDesc
{
    ArgsDesc();
    ArgsDesc(const ArgsDesc &) = delete;
    ArgsDesc& operator==(const ArgsDesc &) = delete;
public:
    enum class ArgType {
        Invalid,
        File,
        Mode,
        Word,
        Help,
    };
    enum class ModeType {
        Invalid,
        Words,
        CheckSum,
    };
    static const ArgsDesc & get()
    {
        static ArgsDesc inst;
        return inst;
    }
    std::list<std::string> args() const;
    std::string arg (ArgType ) const;
    std::string arg (ModeType) const;
    std::string desc(ArgType ) const;
    std::string desc(ModeType) const;

    ArgType  type(const std::string &) const;
    ModeType mode(const std::string &) const;
private:
    std::list<std::string> m_args;
    std::map<ArgType, std::string> m_type2arg;
    std::map<std::string, ArgType> m_arg2type;
    std::map<ArgType, std::string> m_type2desc;
    std::map<std::string, ModeType> m_mode2modeType;
    std::map<ModeType, std::string> m_modeType2mode;
    std::map<ModeType, std::string> m_modeType2desc;
};
