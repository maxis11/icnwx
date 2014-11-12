#if defined (WIN32) || defined (WIN64)
#include "WSA_Inet.hpp"

WSA_Inet::WSA_Inet(u_int mx=5)
{
    log.max_log(mx);
}

void WSA_Inet::set_max_log(u_int mx=5)
{
    log.max_log(mx);
}

void WSA_Inet::WSA_start()
{
    if (WSA_started==0)
    {
        if (WSAStartup(MAKEWORD( 2, 2 ), &ws))
        {
            std::stringstream sstr;
            sstr<<"WSA_start "<<WSAGetLastError()<<std::endl;
            log.add_log(sstr.str());
        }
        else
        {
            WSA_started=1;
            log.add_log("WSA_start 0\n");
        }
    }
}

void WSA_Inet::WSA_exit()
{
    if (WSA_started==1)
    {
        WSACleanup();
        WSA_started=0;
        log.add_log("WSA_exit 0\n");
    }
}

WSADATA WSA_Inet::print_WSA()
{
    return ws;
}

std::vector<std::string> WSA_Inet::print_log()
{
    return log.print_log();
}

#endif
