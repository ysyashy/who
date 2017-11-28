#ifndef WHO_WHO_H
#define WHO_WHO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <time.h>

#define BUFF_SIZE 1024

/*
 * pid_t ut_pid;
 * char  ut_line[];
 * char ut_id[];
 * char ut_user[];
 * char ut_host[];
 * struct {...} ut_tv;   time
 */

class Who
{
private:
    char* buff = nullptr;
    const char* file_name = "/var/run/utmp";
    std::vector<struct utmp *> v_utmp;
    void dis_format_info(struct utmp *);
    char *time_str(time_t *);
public:
    Who();
    /* 获取/var/run/utmp中的所有的内容，封装到vector中 */
    void get_info();
    /* 从vector中读取已经封装好的数据，经过处理后显示 */
    void show_info();
    virtual ~Who();
};

//struct utmp {
//    short   ut_type;              /* Type of record */
//    pid_t   ut_pid;               /* PID of login process */
//    char    ut_line[UT_LINESIZE]; /* Device name of tty - "/dev/" */
//    char    ut_id[4];             /* Terminal name suffix,
//                                                or inittab(5) ID */
//    char    ut_user[UT_NAMESIZE]; /* Username */
//    char    ut_host[UT_HOSTSIZE]; /* Hostname for remote login, or
//                                                kernel version for run-level
//                                                messages */
//    struct  exit_status ut_exit;  /* Exit status of a process
//                                                marked as DEAD_PROCESS; not
//                                                used by Linux init (1 */
//    /* The ut_session and ut_tv fields must be the same size when
//       compiled 32- and 64-bit.  This allows data files and shared
//       memory to be shared between 32- and 64-bit applications. */
//#if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
//    int32_t ut_session;           /* Session ID (getsid(2)),
//                                                used for windowing */
//               struct {
//                   int32_t tv_sec;           /* Seconds */
//                   int32_t tv_usec;          /* Microseconds */
//               } ut_tv;                      /* Time entry was made */
//#else
//    long   ut_session;           /* Session ID */
//    struct timeval ut_tv;        /* Time entry was made */
//#endif
//
//    int32_t ut_addr_v6[4];        /* Internet address of remote
//                                                host; IPv4 address uses
//                                                just ut_addr_v6[0] */
//    char __unused[20];            /* Reserved for future use */
//};
//


#endif
