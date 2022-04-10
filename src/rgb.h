#ifndef RGB_H
#define RGB_H

#include <stdbool.h>

struct RGB {
    float red;
    float green;
    float blue;
};

bool is_in_rgb_range(struct RGB rgb);
float get_min_rgb(struct RGB rgb);
float get_max_rgb(struct RGB rgb);
float get_range_rgb(struct RGB rgb);

#endif
