#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>

#include "rgb.h"


#define FIELD_COUNT 3

struct Flags {
    bool hsl;
    bool hsv;
    bool rgb;
    bool active_fields[FIELD_COUNT];
};


struct Flags parse_args(int argc, char *argv[]);
struct Flags init_default_falgs();
void display_hsl(struct HSL hsl, struct Flags flags);
void display_hsv(struct HSV hsv, struct Flags flags);


int main(int argc, char *argv[]) {
    struct Flags flags = parse_args(argc, argv);

    if (!(flags.hsl || flags.hsv)) {
        fprintf(stderr, "You have to enter an output format!\n");
        return EXIT_FAILURE;
    }

    /* Read from stdin */
    {
        int rv;
        struct RGB rgb;
        unsigned int red, green, blue;
        struct HSL hsl;
        struct HSV hsv;
        char input_buffer[8];
        char valid_hex_chars[8];

        while (fgets(input_buffer, sizeof input_buffer, stdin) != NULL) {

            if (input_buffer[strlen(input_buffer) - 1] == '\n') {
                /* read full line */
                /* Parse hexadecimal */
                sscanf(input_buffer, "%6[0-9a-fA-F]", valid_hex_chars);
                if (errno != 0) {
                    fprintf(stderr, "Error parsing hexadecimal: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }

                if (strlen(valid_hex_chars) == 6) {
                    /* Valid hexadecimal */
                    rv = sscanf(valid_hex_chars, "%2x%2x%2x", &red, &green, &blue);
                    if (rv == 3) {
                        rgb.red = (float)red / 255;
                        rgb.green = (float)green / 255;
                        rgb.blue = (float)blue / 255;

                        if (flags.hsv || flags.hsl) {
                            if (flags.hsl) {
                                hsl.hue = rgb_to_hue(rgb);
                                hsl.saturation = rgb_to_hsl_saturation(rgb);
                                hsl.luminance = rgb_to_hsl_luminance(rgb);

                                display_hsl(hsl, flags);
                            }
                            if (flags.hsv) {
                                hsv.hue = rgb_to_hue(rgb);
                                hsv.saturation = rgb_to_hsv_saturation(rgb);
                                hsv.value = rgb_to_hsv_value(rgb);

                                display_hsv(hsv, flags);
                            }

                        } else if (errno != 0) {
                            /* sscanf had an error */
                            fprintf(stderr, "Error parsing hexadecimal: %s\n", strerror(errno));
                            exit(EXIT_FAILURE);
                        } else {
                            fprintf(stderr, "Something unexpected happened\n");
                            exit(EXIT_FAILURE);
                        }

                    } else {
                        /* Invalid hexadecimal */
                        fprintf(stderr, "Unable to parse hexadecimal.\n");
                        fprintf(stderr, "Valid hex range: 0-9 & a-f & A-F\n");
                        fprintf(stderr, "Required length: 6\n");
                        return EXIT_FAILURE;
                    }

                } else {
                    /* line was truncated */
                    fprintf(stderr, "Line too long. Could not read input.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    
    return 0;
}

struct Flags parse_args(int argc, char *argv[]) {
    struct Flags flags = init_default_falgs();

    static struct option long_options[] = {
        { "hsl",        no_argument,        NULL,  'l' },
        { "hsv",        no_argument,        NULL,  'v' },
        { "rgb",        no_argument,        NULL,  'r' },
        { "fields",     required_argument,  NULL,  'F' },
        { 0,            0,                  0,      0  }
    };


    int option;
    int option_index = 0;
    int i;

    while ((option = getopt_long(argc, argv, "F:lvr", long_options, &option_index)) != EOF) { 
        switch (option) {

            case 'l':
                flags.hsl = true;
                break;

            case 'v': 
                flags.hsv = true;
                break;

            case 'r': 
                flags.rgb = true;
                break;

            case 'F': 
                /* Disable all fields */
                for (i = 0; i < FIELD_COUNT; ++i) {
                    flags.active_fields[i] = false;
                }

                int user_args[FIELD_COUNT];
                char user_field_args[FIELD_COUNT + 1] = {'\0'};

                sscanf(optarg, "%3[1-3]", user_field_args);
                if (errno != 0) {
                    fprintf(stderr, "Error parsing active fields: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }

                if (strlen(optarg) == strlen(user_field_args)) {
                    /* Enable active fields based on user input */
                    for (i = 0; i < strlen(user_field_args); ++i) {
                        user_args[i] = user_field_args[i] - '0';
                        if (user_args[i] <= FIELD_COUNT) {
                            flags.active_fields[user_args[i] - 1] = true;
                        }
                    }

                } else {
                    fprintf(stderr, "Field argument has to be in range [1-%d]\n", FIELD_COUNT);
                    exit(EXIT_FAILURE);
                }

            case '?':
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", option);

        }
    }

    return flags;
}

struct Flags init_default_falgs() {
    struct Flags flags = {
        .rgb = false,
        .hsv = false,
        .hsl = false,
        .active_fields[0] = true,
        .active_fields[1] = true,
        .active_fields[2] = true,
    };

    return flags;
}

/* Print hue, saturation, luminance according to fields enabled */
void display_hsl(struct HSL hsl, struct Flags flags) {
    char separator = '\t';
    printf("HSL:");

    if (flags.active_fields[0]) {
        printf("%lc%.1f", separator, hsl.hue);
    }
    if (flags.active_fields[1]) {
        printf("%lc%.1f%%", separator, hsl.saturation * 100);
    }
    if (flags.active_fields[2]) {
        printf("%lc%.1f%%", separator, hsl.luminance * 100);
    }
    printf("\n");

    return;
}

/* Print hue, saturation, value according to fields enabled */
void display_hsv(struct HSV hsv, struct Flags flags) {
    char separator = '\t';
    printf("HSV:");

    if (flags.active_fields[0]) {
        printf("%lc%.1f", separator, hsv.hue);
    }
    if (flags.active_fields[1]) {
        printf("%lc%.1f%%", separator, hsv.saturation * 100);
    }
    if (flags.active_fields[2]) {
        printf("%lc%.1f%%", separator, hsv.value * 100);
    }
    printf("\n");

    return;
}

