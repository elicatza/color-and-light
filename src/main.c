#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "calc.h"


int main(int argc, char *argv[]) {
    struct RGB rgb[16];
    unsigned int valid_input_count = 0;

    /* Read from stdin */
    {
        int rv;
        struct RGB rgb_tmp;
        char input_buffer[8];

        while (fgets(input_buffer, sizeof input_buffer, stdin) != NULL) {

            if (input_buffer[strlen(input_buffer) - 1] == '\n') {
                /* read full line */

                /* FIX: aabbcl is valid input */
                rv = sscanf(input_buffer, "%2x%2x%2x", &rgb_tmp.red, &rgb_tmp.green, &rgb_tmp.blue);
                if (rv == 3) {
                    rgb[valid_input_count] = rgb_tmp;
                    ++valid_input_count;
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

    unsigned int i;
    for (i = 0; i < valid_input_count; ++i) {
        struct RGB_f rgb_f = parse_rgb_f(rgb[i]);
        float h = calculate_hue(rgb_f);
        float s = calculate_saturation(rgb_f);
        float l = calculate_luminance(rgb_f);

        printf("Hue: %.1f\nSat: %.1f\nLum: %.1f\n\n", h, s * 100, l * 100);
    }

    
    return 0;
}

