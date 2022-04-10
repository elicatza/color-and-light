#include <stdbool.h>
#include <math.h>

#include "rgb.h"

bool is_in_rgb_range(struct RGB rgb) {
    if (
            rgb.red < 0 ||
            rgb.red > 1 ||
            rgb.green < 0 ||
            rgb.green > 1 ||
            rgb.blue < 0 ||
            rgb.blue > 1
       ) {
        return false;
    }
    return true;
}

float get_rgb_min(struct RGB rgb) {
    if (rgb.red <= rgb.green && rgb.red <= rgb.blue) {
        return rgb.red;
    } else if (rgb.green <= rgb.blue) {
        return rgb.green;
    } else {
        return rgb.blue;
    }
}

float get_rgb_max(struct RGB rgb) {
    if (rgb.red >= rgb.green && rgb.red >= rgb.blue) {
        return rgb.red;
    } else if (rgb.green >= rgb.blue) {
        return rgb.green;
    } else {
        return rgb.blue;
    }
}

/* returns max - min */
float get_rgb_range(struct RGB rgb) {
    return get_rgb_max(rgb) - get_rgb_min(rgb);
}


/* rgb -> hsl luminance */
float rgb_to_hsl_luminance(struct RGB rgb) {
    return (get_rgb_min(rgb) + get_rgb_max(rgb)) / 2;
}

/* rgb -> hsl saturation */
float rgb_to_hsl_saturation(struct RGB rgb) {
    float min = get_rgb_min(rgb);
    float max = get_rgb_max(rgb);
    float luminance = rgb_to_hsl_luminance(rgb);

    if (luminance <= 0.5) {
        return (max - min) / (max + min);
    } else {
        return (max - min) / (2.0 - max - min);
    }
}

/* rgb -> hue */
float rgb_to_hue(struct RGB rgb) {
    float max = get_rgb_max(rgb);
    float range = get_rgb_range(rgb);
    float hue;

    if (range == 0) {
        return NAN;
    }

    if (rgb.red == max) {
        hue = fmodf((rgb.green - rgb.blue) / (range), 6);
    } else if (rgb.green == max) {
        hue = ((rgb.blue - rgb.red) / (range)) + 2;
    } else {
        hue = ((rgb.red - rgb.green) / (range)) + 4;
    }

    hue *= 60;
    if (hue < 0) {
        hue += 360;
    }
    return hue;
}

/* rgb -> hsv value */
float rgb_to_hsv_value(struct RGB rgb) {
    if (!is_in_rgb_range(rgb)) {
        return -1;
    }

    return get_rgb_max(rgb);
}

/* rgb -> hsv saturation */
float rgb_to_hsv_saturation(struct RGB rgb) {
    if (!is_in_rgb_range(rgb)) {
        return -1;
    }

    float value = rgb_to_hsv_value(rgb);

    if (value == 0) {
        return -1;
    } else {
        return (get_rgb_range(rgb)) / value; 
    }
}

