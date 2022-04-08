#include "calc.h"


float get_min_rgb_f(struct RGB_f rgb) {
    if (rgb.red <= rgb.green && rgb.red <= rgb.blue) {
        return rgb.red;
    } else if (rgb.green <= rgb.blue) {
        return rgb.green;
    } else {
        return rgb.blue;
    }
}

float get_max_rgb_f(struct RGB_f rgb) {
    if (rgb.red >= rgb.green && rgb.red >= rgb.blue) {
        return rgb.red;
    } else if (rgb.green >= rgb.blue) {
        return rgb.green;
    } else {
        return rgb.blue;
    }
}

struct RGB_f parse_rgb_f(struct RGB rgb) {
    struct RGB_f rgb_f;
    rgb_f.red = (float)rgb.red / 255;
    rgb_f.green = (float)rgb.green / 255;
    rgb_f.blue = (float)rgb.blue / 255;

    return rgb_f;
}

float calculate_luminance(struct RGB_f rgb_f) {
    return (get_min_rgb_f(rgb_f) + get_max_rgb_f(rgb_f)) / 2;
}

float calculate_saturation(struct RGB_f rgb_f) {
    float min = get_min_rgb_f(rgb_f);
    float max = get_max_rgb_f(rgb_f);
    float luminance = (get_min_rgb_f(rgb_f) + get_max_rgb_f(rgb_f)) / 2;

    if (luminance <= 0.5) {
        return (max - min) / (max + min);
    } else {
        return (max - min) / ((float)2 - max - min);
    }
}

float calculate_hue(struct RGB_f rgb_f) {
    float min = get_min_rgb_f(rgb_f);
    float max = get_max_rgb_f(rgb_f);
    float hue;

    if (rgb_f.red == max) {
        hue = (rgb_f.green - rgb_f.blue) / (max - min);
    } else if (rgb_f.green == max) {
        hue = (float)2 + (rgb_f.blue - rgb_f.red) / (max - min);
    } else {
        hue = (float)4 + (rgb_f.red - rgb_f.green) / (max - min);
    }

    return hue * (float)60;
}
