#pragma once
#include "functions.h"

struct c_module
{
    int update_time;
    char* (*function)(struct c_arguments arguments);
    struct c_arguments arguments;
    char* saved_value;
};

static const char* delimiter = " | ";

static struct c_module modules[] = {
    /*
     * { update time, function, { .argument = value } }
     * view the c_arguments implementation in functions.h if you need more information
     *
     * function help:
     * get_time:            argument .string = "strftime() format" (for help, run: 'man strftime')
     * get_date:            argument .string = "strftime() format" (for help, run: 'man strftime')
     * get_network_speed:   argument .string = "network interface name" (eg. eth0)
     */
    //{ 1, get_network_speed, { .string = "eth0" } },
    { 1, get_datetime, { .string = "%A %d/%m | %H:%M" } },
};
