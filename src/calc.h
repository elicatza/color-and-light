#ifndef CALC_H
#define CALC_H

struct RGB {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

struct RGB_f {
    float red;
    float green;
    float blue;
};

struct HSL {
    float hue;
    float saturation;
    float luminance;
};

struct RGB_f parse_rgb_f(struct RGB rgb);
float get_min_rgb_f(struct RGB_f rgb);
float get_max_rgb_f(struct RGB_f rgb);

float calculate_luminance(struct RGB_f rgb_f);
float calculate_saturation(struct RGB_f rgb_f);
float calculate_hue(struct RGB_f rgb_f);

#endif
