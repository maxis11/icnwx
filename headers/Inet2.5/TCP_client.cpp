#include "TCP_client.hpp"

TCP_client::TCP_client()
{
    #if defined (WIN32) || defined (WIN64)
        Glob.WSA_start();
    #endif
    log.max_log(15);
    sock=socket(AF_INET,SOCK_STREAM,0);
    if (sock<0)
    {
        std::stringstream sstr;
        sstr<<"TCP_client "<<WSAGetLastError()<<std::endl;
        log.add_log(sstr.str());
    }
    else
    {
        log.add_log("TCP_client 0\n");
    }
}

TCP_client::TCP_client(u_short porti, std::string ip, u_int tm=0, bool qc=0, u_int mx=15)
{
    #if defined (WIN32) || defined (WIN64)
        Glob.WSA_start();
    #endif
    log.max_log(mx);
    pause=tm;
    quit_connect=qc;
    sock=socket(AF_INET,SOCK_STREAM,0);
    if (sock<0)
    {
        std::stringstream sstr;
        sstr<<"TCP_client "<<WSAGetLastError()<<std::endl;
        log.add_log(sstr.str());
    }
    else
    {
        port=porti;
        servip=ip;
        log.add_log("TCP_client 0\n");
    }
}

void TCP_client::set_address(u_short porti,std::string ip)
{
    port=porti;
    servip=ip;
}

void TCP_client::set_repeat_time (u_int pausei)
{
    pause=pausei;
}

void TCP_client::set_max_log(u_int mx)
{
    log.max_log(mx);
}

void TCP_client::set_quit_connect(bool qc)
{
    quit_connect=qc;
}

void* TCP_client::out_func()
{
    return datao;
}

bool TCP_client::running()
{
    return thread_run;
}

void TCP_client::connect_serv(boost::function<bool (SOCKET,void*,void*)> f, void* data)
{
    datai=data;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    if (inet_addr(servip.c_str())!=INADDR_NONE)
    {
        serv_addr.sin_addr.s_addr=inet_addr(servip.c_str());
        if (connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr)))
        {
            std::stringstream sstr;
            sstr<<"connect_serv_connection "<<WSAGetLastError()<<std::endl;
            log.add_log(sstr.str());
            reload_sock();
        }
        else
        {
            log.add_log("connect_serv 0\n");
            list_thread=boost::thread (boost::bind( &TCP_client::tech_listen, this, f ) );
            thread_start=1;
        }
    }
    else
    {
        std::stringstream sstr;
        sstr<<"connect_serv_ip "<<WSAGetLastError()<<std::endl;
        log.add_log(sstr.str());
        reload_sock();
    }
}

void TCP_client::tech_listen(boost::function<bool (SOCKET,void*,void*)> f)
{
    boost::this_thread::interruption_enabled();
    bool exitwh=0;
    while ((exitwh==0)&&(thread_start==1))
    {
        thread_run=1;
        exitwh=f(sock,datai,datao);
        thread_run=0;
        boost::xtime xt;
        boost::xtime_get(&xt, 1);
        xt.sec += pause;
        boost::this_thread::sleep(xt);
        if (quit_connect==1)
        {
            reload_sock();
            if (connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr)))
            {
                std::stringstream sstr;
                sstr<<"techikal_connect_serv_connection "<<WSAGetLastError()<<std::endl;
                log.add_log(sstr.str());
                reload_sock();
            }
        }

    }
    log.add_log("tech_listen 0");
    close_connection();
    thread_start=0;
}

void TCP_client::close_connection()
{
    if (thread_start==1)
    {
        list_thread.interrupt();
        list_thread.join();
        thread_start=0;
        reload_sock();
        while (list_thread.joinable()) {}
    }
}

void TCP_client::reload_sock()
{
    #if defined (WIN32) || defined (WIN64)
        closesocket(sock);
    #elif defined(__unix__)
        close(sock);
    #endif
    sock=socket(AF_INET,SOCK_STREAM,0);
    if (sock<0)
    {
        std::stringstream sstr;
        sstr<<"reload_sock "<<WSAGetLastError()<<std::endl;
        log.add_log(sstr.str());
    }
    else
    {
        log.add_log("reload_sock 0\n");
    }
}

std::vector<std::string> TCP_client::print_log()
{
    return log.print_log();
}

void TCP_client::join_in_main()
{
    if (thread_start==1)
    {
        thread_start=0;
        list_thread.join();
    }
}

void TCP_client::interrupt()
{
    if (thread_start==1)
    {
        thread_start=0;
        list_thread.interrupt();
    }
}

TCP_client::~TCP_client()
{
    close_connection();
    #if defined (WIN32) || defined (WIN64)
        closesocket(sock);
        Glob.WSA_exit();
    #elif defined(__unix__)
        close(sock);
    #endif
}
