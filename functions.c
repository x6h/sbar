#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

char bar_date[MAX_MODULE_LENGTH] = "";
char bar_time[MAX_MODULE_LENGTH] = "";
char bar_network_speed[MAX_MODULE_LENGTH] = "";

char* get_datetime(struct c_arguments arguments)
{
    time_t unix_time = time(NULL);
    struct tm* local_time = localtime(&unix_time);

    if (unix_time != -1 && local_time)
        strftime(bar_time, MAX_MODULE_LENGTH, arguments.string, local_time);
    else
        snprintf(bar_time, MAX_MODULE_LENGTH, "n/a");

    return bar_time;
}

char* get_network_speed(struct c_arguments arguments)
{
    // fail if network interface name is null
    if (!arguments.string)
    {
        sprintf(bar_network_speed, "n/a");
        return bar_network_speed;
    }

    // todo: make this dynamically allocated, possibility to cause a buffer overflow
    char rx_bytes_file_path[256] = "";
    char tx_bytes_file_path[256] = "";
    // format file path with network interface specified in config.h
    sprintf(rx_bytes_file_path, "/sys/class/net/%s/statistics/rx_bytes", arguments.string);
    sprintf(tx_bytes_file_path, "/sys/class/net/%s/statistics/tx_bytes", arguments.string);
    // open network statistic files
    FILE* rx_bytes_file = fopen(rx_bytes_file_path, "r");
    FILE* tx_bytes_file = fopen(tx_bytes_file_path, "r");

    if (rx_bytes_file && tx_bytes_file)
    {
        static long unsigned int rx_bytes = 0;
        static long unsigned int tx_bytes = 0;
        static long unsigned int old_rx_bytes = 0;
        static long unsigned int old_tx_bytes = 0;
        // read file data to respective variables
        fscanf(rx_bytes_file, "%lu", &rx_bytes);
        fscanf(tx_bytes_file, "%lu", &tx_bytes);

        snprintf(bar_network_speed, MAX_MODULE_LENGTH, "rx: %lu | tx: %lu", rx_bytes - old_rx_bytes, tx_bytes - old_tx_bytes);

        old_rx_bytes = rx_bytes;
        old_tx_bytes = tx_bytes;

        fclose(rx_bytes_file);
        fclose(tx_bytes_file);
    }
    else
    {
        sprintf(bar_network_speed, "n/a");
    }

    return bar_network_speed;
}
