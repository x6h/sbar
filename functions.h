#pragma once
#define MAX_MODULE_LENGTH 32

extern char bar_date[MAX_MODULE_LENGTH];
extern char bar_time[MAX_MODULE_LENGTH];
extern char bar_network_speed[MAX_MODULE_LENGTH];

struct c_arguments
{
    char* string;
    char** string_array;
};

char* get_time(struct c_arguments arguments);
char* get_date(struct c_arguments arguments);
char* get_network_speed(struct c_arguments arguments);
