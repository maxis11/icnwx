#ifndef _MINET_LOG_HPP
#define _MINET_LOG_HPP
#include <vector>
#include <string>

class Inet_Log
{
private:
    std::vector<std::string>log_str;
    unsigned int max_size;
public:
    void add_log(std::string);
    void max_log(unsigned int);
    std::vector<std::string> print_log ();
};

#endif
