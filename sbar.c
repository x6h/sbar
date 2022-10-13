#include "functions.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define ARRAY_SIZE(x) sizeof(x) / sizeof(*x)

struct c_module
{
    int update_time;
    char* (*function)(struct c_arguments arguments);
    struct c_arguments arguments;
    char* saved_value;
};

#include "config.h"

int main()
{
    /* open a connection to the X server */
    Display* display = XOpenDisplay(NULL);

    if (!display)
    {
        fprintf(stderr, "sbar: failed to connect to the X server\n");
        exit(1);
    }

    /* allocate memory for each modules saved value */
    for (int k = 0; k < ARRAY_SIZE(modules); ++k)
        modules[k].saved_value = (char*)calloc(1, MAX_MODULE_LENGTH);

    for (unsigned int i = 1; ; ++i)
    {
        char status[256] = "";

        for (int k = 0; k < ARRAY_SIZE(modules); ++k)
        {
            /* update the modules saved value if the update time has passed */
            if (i % modules[k].update_time == 0)
            {
                modules[k].saved_value = modules[k].function(modules[k].arguments);
                strcpy(modules[k].saved_value, modules[k].function(modules[k].arguments));
            }

            /* append each modules saved value to the status string */
            strcat(status, modules[k].saved_value);

            /* add delimiters between each saved value */
            if (k != ARRAY_SIZE(modules) - 1)
                strcat(status, delimiter);
        }

        /* lowercase status text (remove if you prefer otherwise) */
        for (int i = 0; i < strlen(status); ++i)
            status[i] = tolower(status[i]);

        /* set the root window name as the status (dwm defaults to using it as the bars status text) */
        XStoreName(display, XDefaultRootWindow(display), status);
        /* flush the XStoreName request to the X server */
        XFlush(display);

        sleep(1);
    }

    return 0;
}
