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
     * update time, function, { .argument = value }
     * view the c_arguments implementation in functions.h if you need more information
     *
     * function help:
     * get_time: '.string' is the strftime format (for help, run: 'man strftime')
     * get_date: same as above)
     */
    //{ 1, get_network_speed, { .string = "eth0" } },
    { 1, get_date, { .string = "%A %d/%m" } },
    { 1, get_time, { .string = "%H:%M" } }
};
