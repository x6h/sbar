static const char* delimiter = " | ";

struct c_module modules[] = {
    /*
     * update time, function, { .argument = value }
     * view the c_arguments implementation in functions.h if you need more information
     *
     * function help:
     * get_time: '.string' is the strftime format (for help, run: 'man strftime')
     * get_date: same as above)
     */
    { 1, get_date, { .string = "%A %d/%m" } },
    { 1, get_time, { .string = "%H:%M" } },
};
