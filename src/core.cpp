#include "../headers/core.hpp"

Core_connector::Core_connector()
{
    cl.set_address(9000,"192.168.1.1");
    cl.set_repeat_time(900);
    cl.set_quit_connect(1);
    cl.set_max_log(3);
}

bool technikal_connect  (SOCKET sock,void* data, void*)
{
    usr_data* usr;
    usr=(usr_data*) data;
    int nsize;
    std::string login("");
    if (usr->command==0)
    {
        login+="on";
    }
    else
    {
        login+="of";
    }
    std::string s( usr->login.begin(), usr->login.end() );
    login+=s;
    if (usr->bmstu==0)
    {
        login+="|1";
    }
    login+='\n';
    std::string s2( usr->password.begin(), usr->password.end() );
    std::string password=s2;
    char buff[1024];
    idea_ks key;
    idea_user_key us_key;
    unsigned int len = password.length();
    char *pass_data;
    send(sock,login.c_str(),login.size(),0);
    nsize=recv(sock,&buff[0],sizeof(buff)-1,0);
    memset (us_key, '0', sizeof (us_key));
    if (len > sizeof (idea_user_key))
        len = sizeof (idea_user_key);
    pass_data = (char*)password.data();
    for (unsigned int r = 0; r < len; r ++) {
        *(((char *)us_key) + r) = pass_data[r];
    }
    idea_expand_key (us_key, key);
    idea_cblock in;
    idea_cblock out;
    memcpy (in, buff, sizeof (in));
    idea_crypt (in, out, key);
    for (unsigned int i = 0; i < sizeof (out) / sizeof (out [0]); i++)
    {
        out [i] = out [i] >> 8 | out [i] << 8;
        char brr [10];
        sprintf (brr, "%04x", out [i]);
            send(sock,brr,strlen(brr),0);
    }
    send(sock,"\n\r", 2,0);
    nsize=recv(sock,&buff[0],sizeof(buff)-1,0);
    buff[nsize]=0;
    buff[nsize+1]='\0';
    cout<<buff;
    return 0;
}

bool technikal_connect2  (SOCKET sock,void* data, void*)
{
    usr_data* usr;
    usr=(usr_data*) data;
    int nsize;
    std::string login("");
    if (usr->command==0)
    {
        login+="on";
    }
    else
    {
        login+="of";
    }
    std::string s( usr->login.begin(), usr->login.end() );
    login+=s;
    if (usr->bmstu==0)
    {
        login+="|1";
    }
    login+='\n';
    std::string s2( usr->password.begin(), usr->password.end() );
    std::string password=s2;
    char buff[1024];
    idea_ks key;
    idea_user_key us_key;
    unsigned int len = password.length();
    char *pass_data;
    send(sock,login.c_str(),login.size(),0);
    nsize=recv(sock,&buff[0],sizeof(buff)-1,0);
    memset (us_key, '0', sizeof (us_key));
    if (len > sizeof (idea_user_key))
        len = sizeof (idea_user_key);
    pass_data = (char*)password.data();
    for (unsigned int r = 0; r < len; r ++) {
        *(((char *)us_key) + r) = pass_data[r];
    }
    idea_expand_key (us_key, key);
    idea_cblock in;
    idea_cblock out;
    memcpy (in, buff, sizeof (in));
    idea_crypt (in, out, key);
    for (unsigned int i = 0; i < sizeof (out) / sizeof (out [0]); i++)
    {
        out [i] = out [i] >> 8 | out [i] << 8;
        char brr [10];
        sprintf (brr, "%04x", out [i]);
            send(sock,brr,strlen(brr),0);
    }
    send(sock,"\n\r", 2,0);
    nsize=recv(sock,&buff[0],sizeof(buff)-1,0);
    buff[nsize]=0;
    buff[nsize+1]='\0';
    cout<<buff;
    return 0;
}

void Core_connector::connect_serv(usr_data& usri)
{
    usr=usri;
    usr.command=0;
    cl.set_quit_connect(1);
    cl.connect_serv(technikal_connect,&usr);

}

void Core_connector::disconnect_serv()
{
    usr.command=1;
    cl.set_quit_connect(0);
    cl.close_connection();
    while (cl.running()==1) {}
    cl.connect_serv(technikal_connect2,&usr);
    while (cl.running()==1) {}
    cl.close_connection();

}

void Core_connector::set_repeat_time (unsigned int tm=900)
{
    cl.set_repeat_time(tm);
}

std::vector<string> Core_connector::print_log()
{
    return cl.print_log();
}

void Core_connector::os_log()
{
    std::vector<string> log;
    log=cl.print_log();
    for (unsigned int i=0; i<log.size(); i++)
    {
        cout<<log[i];
    }
}

void Core_connector::set_max_log(unsigned int mx=2)
{
    cl.set_max_log(mx+1);
}

Core_connector::~Core_connector()
{
    cl.interrupt();
    cl.join_in_main();
}
