/**
 *@file CurlRAII.cpp
 * @author Fabio Rossini Sluzala ()
 * @brief CurlRAII definitions
 * @version 0.1
 *
 *
 */
#include "CurlRAII.hpp"

CurlRAII::CurlRAII()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CurlRAII::~CurlRAII()
{
    curl_global_cleanup();
}

CurlRAII& CurlRAII::instance()
{
    static CurlRAII inst;
    return inst;
}

curlCallBack CurlRAII::dispatch_github_action(const std::string& url, const std::string& GITHUBTOKEN, const std::string& payload)
{
    curlCallBack result;
    curlraii_t curl = make_curl_easy();

    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_POST, 1);
    curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, payload.c_str());

    curl_easy_setopt(curl.get(), CURLOPT_HEADER, true);

    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, std::addressof(result.cb));
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, std::addressof(result));

    curlslitraii_t headers;

    /*
    * Trecho de std::string possivelmente otimizavel
    */
    std::string token;
    token.reserve(64);
    token = "Authorization: token ";
    token += GITHUBTOKEN;

    CurlRAII::curl_slist_append_raii(headers, token.c_str());
    CurlRAII::curl_slist_append_raii(headers, "User-Agent: request");
    CurlRAII::curl_slist_append_raii(headers, "Accept: application/vnd.github.everest-preview+json");

    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headers.get());

    result.curl_perfm_res = curl_easy_perform(curl.get());

    if (result.curl_perfm_res == CURLE_OK)
    {
        curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, std::addressof(result.response_code));
    }

    return result;
}

