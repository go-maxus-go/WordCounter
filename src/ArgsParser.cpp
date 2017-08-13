#include "ArgsParser.h"

#include <map>
#include <set>

using StringList = std::list<std::string>;

class ArgsParser::Impl
{
public:
    void setOption(const std::string & option)
        { m_options.insert(option); }
    bool parse(const StringList & args)
    {
        if (m_options.empty())
            return false;
        m_values.clear();
        std::string curr;
        for (auto a : args)
        {
            auto it = m_options.find(a);
            if (it != m_options.end())
                m_values[curr = *it];
            else
                m_values[curr].push_back(a);
        }
        return true;
    }
    bool isSet(const std::string & option) const
        { return m_values.find(option) != m_values.end(); }
    StringList values(const std::string & option) const
    {
        auto it = m_values.find(option);
        if (it == m_values.end())
            return StringList();
        return it->second;
    }
private:
    std::set<std::string> m_options;
    std::map<std::string, StringList> m_values;
};

ArgsParser::ArgsParser() : m_impl(new Impl) {}
ArgsParser::~ArgsParser() = default;

void ArgsParser::setOption(const std::string & option)
    { m_impl->setOption(option); }
bool ArgsParser::parse(const StringList & args)
    { return m_impl->parse(args); }
bool ArgsParser::isSet(const std::string & option) const
    { return m_impl->isSet(option); }
StringList ArgsParser::values(const std::string & option) const
    { return m_impl->values(option); }
