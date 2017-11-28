
#include "who.h"

Who::Who() : buff(nullptr)
{
    v_utmp.reserve(256);
}

Who::~Who()
{
    if(buff != nullptr) delete[] buff;
    for(struct utmp *it : v_utmp)
    {
        delete it;
        it = nullptr;
    }
}

void Who::get_info()
{
    FILE *fp = fopen(file_name, "r");
    struct utmp *it_utmp = nullptr;
    while(!feof(fp))
    {
        it_utmp = new utmp;
        fread(it_utmp, sizeof(struct utmp), 1, fp);
        v_utmp.push_back(it_utmp);  it_utmp = nullptr;
    }

    fclose(fp);
}

void Who::show_info()
{
    printf("=>pid    user      tty      login time         host<=\n");
    for(struct utmp *it : v_utmp)
    {
        if(it->ut_type != USER_PROCESS && it->ut_type != LOGIN_PROCESS) continue;
        this->dis_format_info(it);
    }
}

void Who::dis_format_info(struct utmp *it)
{
    /* pid  user   tty  date time   (ip:port) */
    struct timeval tmp;
    tmp.tv_sec = it->ut_tv.tv_sec;  tmp.tv_usec = it->ut_tv.tv_usec;
    printf("%4d    %s    %s    %s    (%s)\n",
            it->ut_pid, it->ut_user, it->ut_line, time_str(&tmp.tv_sec), it->ut_host);
}

char *Who::time_str(time_t *time1)
{
    struct tm * s_tm = localtime(time1);
    buff = new char[32];

    sprintf(buff, "%04d-%02d-%02d %02d:%02d",
        1900+s_tm->tm_year, 1+s_tm->tm_mon, s_tm->tm_mday, s_tm->tm_hour, s_tm->tm_min);
    return buff;
}