#include "rgb.h"

/* rgb -> hsv value */
float hsv_rgb_value(struct RGB rgb) {
    if (!is_in_rgb_range(rgb)) {
        return -1;
    }

    return get_max_rgb(rgb);
}

/* rgb -> hsv saturation */
float hsv_rgb_saturation(struct RGB rgb) {
    if (!is_in_rgb_range(rgb)) {
        return -1;
    }

    float value = hsv_rgb_value(rgb);

    if (value == 0) {
        return -1;
    } else {
        return (get_range_rgb(rgb)) / value; 
    }
}

/* rgb -> hsv hue */
float hsv_rgb_hue(struct RGB rgb) {
    float min = get_min_rgb(rgb);
    float max = get_max_rgb(rgb);
    float range = get_range_rgb(rgb);
    float hue;

    if (range == 0) {
        return -1;
    }

    if (rgb.red == max) {
        hue = (rgb.green - rgb.blue) / (range);
    } else if (rgb.green == max) {
        hue = (float)2 + (rgb.blue - rgb.red) / (range);
    } else {
        hue = (float)4 + (rgb.red - rgb.green) / (range);
    }

    return hue * (float)60;
}
