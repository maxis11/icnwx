#ifndef _CORE_HPP
#define _CORE_HPP
#include <string>
#if defined (WIN32) || defined (WIN64)
#include <winsock2.h>
#elif defined(__unix__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SOCKET int
#define WSAGetLastError() 1
#endif
#include <cstdio>
#include "idea.h"
#include <iostream>
#include <ctime>
#include "Inet2.5/TCP_client.hpp"
#define ICNBASEMAJORV 0
#define ICNBASEMINORV 5
#define ICNBASEPATCHV 2


using std::cin;
using std::cout;
using std::string;

struct usr_data
{
    std::string login;
    std::string password;
    bool command;
    bool bmstu;
};

class Core_connector
{
private:
    usr_data usr;
    void*  datao;
    TCP_client cl;
public:
    Core_connector();
    void connect_serv(usr_data&);
    void set_repeat_time (unsigned int);
    void disconnect_serv();
    void set_max_log(unsigned int);
    std::vector<string> print_log();
    void os_log();
    ~Core_connector();
};

bool technikal_connect(SOCKET,void*,void*);
bool technikal_connect2(SOCKET,void*,void*);

#endif
