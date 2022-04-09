#include "rgb.h"

/* rgb -> hsl luminance */
float hsl_rgb_luminance(struct RGB rgb) {
    return (get_min_rgb(rgb) + get_max_rgb(rgb)) / 2;
}


/* rgb -> hsl saturation */
float hsl_rgb_saturation(struct RGB rgb) {
    float min = get_min_rgb(rgb);
    float max = get_max_rgb(rgb);
    float luminance = hsl_rgb_luminance(rgb);

    if (luminance <= 0.5) {
        return (max - min) / (max + min);
    } else {
        return (max - min) / (2.0 - max - min);
    }
}

/* rgb -> hsl hue */
float hsl_rgb_hue(struct RGB rgb) {
    float min = get_min_rgb(rgb);
    float max = get_max_rgb(rgb);
    float hue;

    if (rgb.red == max) {
        hue = (rgb.green - rgb.blue) / (max - min);
    } else if (rgb.green == max) {
        hue = (float)2 + (rgb.blue - rgb.red) / (max - min);
    } else {
        hue = (float)4 + (rgb.red - rgb.green) / (max - min);
    }

    return hue * (float)60;
}
