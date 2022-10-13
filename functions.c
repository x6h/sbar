#include "functions.h"
#include <stdio.h>
#include <time.h>

char bar_date[MAX_MODULE_LENGTH] = "";
char bar_time[MAX_MODULE_LENGTH] = "";

char* get_time(struct c_arguments arguments)
{
    time_t unix_time = time(NULL);
    struct tm* local_time = localtime(&unix_time);

    if (unix_time != -1 && local_time)
        strftime(bar_time, MAX_MODULE_LENGTH, arguments.string, local_time);
    else
        snprintf(bar_time, MAX_MODULE_LENGTH, "n/a");

    return bar_time;
}

char* get_date(struct c_arguments arguments)
{
    time_t unix_time = time(NULL);
    struct tm* local_time = localtime(&unix_time);

    if (unix_time != -1 && local_time)
        strftime(bar_date, MAX_MODULE_LENGTH, arguments.string, local_time);
    else
        snprintf(bar_date, MAX_MODULE_LENGTH, "n/a");

    return bar_date;
}
