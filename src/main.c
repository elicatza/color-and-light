#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "calc.h"


int main(int argc, char *argv[]) {

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

                    printf("%.1f\t%.1f%%\t%.1f%%\n", hsl.hue, hsl.saturation * 100, hsl.luminance * 100);

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

