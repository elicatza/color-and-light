#ifndef RGB_H
#define RGB_H

#include <stdbool.h>


struct RGB {
    float red;
    float green;
    float blue;
};

struct HSL {
    float hue;
    float saturation;
    float luminance;
};

struct HSV {
    float hue;
    float saturation;
    float value;
};

bool is_in_rgb_range(struct RGB rgb);
float get_rgb_min(struct RGB rgb);
float get_rgb_max(struct RGB rgb);
float get_rgb_range(struct RGB rgb);

float rgb_to_hue(struct RGB rgb);

float rgb_to_hsl_luminance(struct RGB rgb);
float rgb_to_hsl_saturation(struct RGB rgb);

float rgb_to_hsv_value(struct RGB rgb);
float rgb_to_hsv_saturation(struct RGB rgb);

#endif
