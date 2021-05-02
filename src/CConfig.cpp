#include "CConfig.hpp"
#include <iostream>
#include <algorithm>

CConfig& CConfig::config()
{
    static CConfig conf;
    return conf;
}

std::string CConfig::operator[](const std::string& key) const noexcept
{
    auto it = data.find(key);
    if (it == data.end())
    {
        return "";
    }

    return it->second;
}

std::string CConfig::at(const std::string& key, std::string&& default_ret) const noexcept
{
    auto it = data.find(key);
    if (it == data.end())
    {
        return default_ret;
    }

    return it->second;
}


void CConfig::load_from_envp(char** envp)
{
    char** env = envp;
    std::string line;
    std::string key;
    std::string val;
    for (/**/; *env; ++env)
    {
        line = *env;

        size_t pos = line.find_first_of('=');

        if (pos == line.npos)
            continue;

        key = line.substr(0, pos);
        val = line.substr(pos + 1);

        data[key] = val;
    }
}

CConfig::CConfig() noexcept
{

}
