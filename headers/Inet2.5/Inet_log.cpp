#include "Inet_log.hpp"

void Inet_Log::add_log(std::string s)
{
    if (log_str.size()+1==max_size)
        log_str.clear();
    log_str.push_back(s);
}

void Inet_Log::max_log(unsigned int mx)
{
    max_size=mx;
}

std::vector<std::string> Inet_Log::print_log()
{
    return log_str;
}
