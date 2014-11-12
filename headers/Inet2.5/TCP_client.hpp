#ifndef _MTCP_CLIENT_HPP
#define _MTCP_CLIENT_HPP
#if defined (WIN32) || defined (WIN64)
#include "WSA_Inet.hpp"
#elif defined(__unix__)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SOCKET int
#define WSAGetLastError() 1
#endif
#include "Inet_log.hpp"
#include <ctime>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <sstream>
#define TCPCMAJORV 2
#define TCPCMINORV 5
#define TCPCPATCHV 2

class TCP_client
{
private:
    u_short port;
    std::string servip;
    Inet_Log log;
    bool thread_start;
    bool quit_connect;
    SOCKET sock;
    sockaddr_in serv_addr;
    boost::thread list_thread;
    u_int pause;
    void* datai;
    bool thread_run;
    void* datao;
    void tech_listen(boost::function<bool (SOCKET,void*,void*)>);
    void reload_sock();
public:
    TCP_client();
    TCP_client(u_short,std::string,u_int,bool,u_int);
    void set_address (u_short,std::string);
    void set_repeat_time (u_int);
    void set_quit_connect(bool);
    void set_max_log(u_int);
    void connect_serv(boost::function<bool (SOCKET,void*,void*)>,void*);
    void close_connection();
    bool running ();
    std::vector<std::string> print_log();
    void* out_func();
    void join_in_main();
    void interrupt();
    ~TCP_client();
};

#endif
