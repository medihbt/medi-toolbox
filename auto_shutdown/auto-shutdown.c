#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool check_if_over(struct tm *ftime, unsigned hour, unsigned min)
{
    unsigned ft_hr = ftime->tm_hour, ft_min = ftime->tm_min;
    unsigned ft_cnt = ft_hr * 60 + ft_min;
    unsigned chk_cnt = hour * 60 + min;

    /*0:00 never shuts down*/
    if (ft_cnt == 0)
        return false;
    else if (ft_cnt >= chk_cnt)
        return true;
    
    return false;
}

int main()
{
    time_t timecnt;
    struct tm *ftime;
    int flag = 0;
    while (flag == 0)
    {
        timecnt = time(NULL);
        ftime = localtime(&timecnt);
        if (check_if_over(ftime, 23, 0))
        {
            system("zenity --notification --text=\"**你的电脑将在1分钟内关机!**\n请立即保存你的工作.\"");
            system("shutdown");
            flag = 1;
        }
        sleep(2);
    }
    return 0;
}