#pragma once
#ifndef _CConfig_hpp
#define _CConfig_hpp
#include <map>
#include <string>

class CConfig
{
    std::map<std::string, std::string> data;

public:

    static CConfig& config();

    // Default null string
    std::string operator[](const std::string& key) const noexcept;

    std::string at(const std::string& key, std::string&& default_ret = "") const noexcept;

    void load_from_envp(char** envp);

private:
    CConfig(const CConfig&) = delete;
    CConfig() noexcept;
};

#endif
