#include "functions.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define ARRAY_SIZE(x) sizeof(x) / sizeof(*x)

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
    for (unsigned int k = 0; k < ARRAY_SIZE(modules); ++k)
        modules[k].saved_value = (char*)calloc(MAX_MODULE_LENGTH, sizeof(char));

    unsigned int bytes_allocated = 1;
    char* status = (char*)calloc(bytes_allocated, sizeof(char));

    for (unsigned int i = 1; ; ++i)
    {
        /* 'clear' the status */
        status[0] = '\0';

        for (unsigned int k = 0; k < ARRAY_SIZE(modules); ++k)
        {
            /* update the modules saved value if the update time has passed */
            if (i % modules[k].update_time == 0)
            {
                modules[k].saved_value = modules[k].function(modules[k].arguments);
                strcpy(modules[k].saved_value, modules[k].function(modules[k].arguments));
            }

            /* allocate more memory for status if the status length + a modules saved value overflows the buffer */
            if (strlen(status) + strlen(modules[k].saved_value) > strlen(status))
            {
                bytes_allocated = strlen(status) + strlen(modules[k].saved_value) + 1;
                status = realloc(status, bytes_allocated);
            }

            /* append each modules saved value to the status string */
            strcat(status, modules[k].saved_value);

            /* add delimiters between each saved value */
            if (k != ARRAY_SIZE(modules) - 1)
            {
                if (bytes_allocated < strlen(status) + strlen(delimiter))
                {
                    bytes_allocated = strlen(status) + strlen(delimiter) + 1;
                    status = realloc(status, bytes_allocated);
                }

                strcat(status, delimiter);
            }
        }

        /* lowercase status text (remove if you prefer otherwise) */
        for (unsigned int i = 0; i < strlen(status); ++i)
            status[i] = tolower(status[i]);

        /* set the root window name as the status (dwm defaults to using it as the bars status text) */
        XStoreName(display, XDefaultRootWindow(display), status);
        /* flush the XStoreName request to the X server */
        XFlush(display);

        sleep(1);
    }

    return 0;
}
