#ifndef _MWSA_INET_HPP
#define _MWSA_INET_HPP
#if defined (WIN32) || defined (WIN64)
#include "Inet_log.hpp"
#include <sstream>
#include <winsock2.h>
#include <windows.h>

class WSA_Inet
{
private:
    bool WSA_started;
    WSADATA ws;
    Inet_Log log;
public:
    WSA_Inet (u_int);
    void WSA_start();
    void WSA_exit();
    void set_max_log(u_int);
    std::vector<std::string> print_log();
    WSADATA print_WSA();
};
#endif
#endif
