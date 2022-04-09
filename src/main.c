#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>

#include "calc.h"

struct Flags {
    bool all;
    bool hue;
    bool saturation;
    bool luminance;
};

struct Flags parse_args(int argc, char *argv[]);
struct Flags init_default_falgs();
void display_hsl(struct HSL hsl, struct Flags flags);


int main(int argc, char *argv[]) {
    struct Flags flags = parse_args(argc, argv);

    /* Read from stdin */
    {
        int rv;
        struct RGB rgb_tmp, rgb;
        struct RGB_f rgb_f;
        struct HSL hsl;
        char input_buffer[8];

        while (fgets(input_buffer, sizeof input_buffer, stdin) != NULL) {

            if (input_buffer[strlen(input_buffer) - 1] == '\n') {
                /* read full line */
                /* TODO: aabbcl is valid input */
                rv = sscanf(input_buffer, "%2x%2x%2x", &rgb_tmp.red, &rgb_tmp.green, &rgb_tmp.blue);
                if (rv == 3) {
                    rgb = rgb_tmp;
                    rgb_f = parse_rgb_f(rgb);

                    hsl.hue = calculate_hue(rgb_f);
                    hsl.saturation = calculate_saturation(rgb_f);
                    hsl.luminance = calculate_luminance(rgb_f);

                    display_hsl(hsl, flags);

                } else if (errno != 0) {
                    fprintf(stderr, "Error parsing hexadecimal: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                } else {
                    /* Hexadecimal conversion failed */
                    fprintf(stderr, "Unable to parse hexadecimal\n");
                }

            } else {
                /* line was truncated */
                fprintf(stderr, "Line too long. Could not read input.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    return 0;
}

struct Flags parse_args(int argc, char *argv[]) {
    struct Flags flags = init_default_falgs();

    static struct option long_options[] = {
        {"all",        no_argument,  NULL,  'a' },
        {"hue",        no_argument,  NULL,  'h' },
        {"saturation", no_argument,  NULL,  's' },
        {"luminance",  no_argument,  NULL,  'l' },
        {0,            0,            0,   0  }
    };


    int option;
    int option_index = 0;

    while ((option = getopt_long(argc, argv, "ahsl", long_options, &option_index)) != EOF) { 
        switch (option) {

            case 'a': 
                flags.all = true;
                break;

            case 'h':
                flags.hue = true;
                flags.all = false;
                break;

            case 's': 
                flags.saturation = true;
                flags.all = false;
                break;

            case 'l': 
                flags.luminance = true;
                flags.all = false;
                break;

            case ':':
                printf("Flag needs a value\n");
                break;

            case '?':
                exit(EXIT_FAILURE);
                break;
        }
    }

    return flags;
}

struct Flags init_default_falgs() {
    struct Flags flags = {
        .all = true,
        .hue = false,
        .saturation = false,
        .luminance = false,
    };

    return flags;
}

/* Print hue, saturation, luminance according to fields enabled */
void display_hsl(struct HSL hsl, struct Flags flags) {
    char separator = '\t';

    if (flags.hue) {
        printf("%lc%.1f", separator, hsl.hue);
    }
    if (flags.saturation) {
        printf("%lc%.1f%%", separator, hsl.saturation * 100);
    }
    if (flags.luminance) {
        printf("%lc%.1f%%", separator, hsl.luminance * 100);
    }
    printf("\n");

    return;
}

