#include <stdbool.h>

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

float get_min_rgb(struct RGB rgb) {
    if (rgb.red <= rgb.green && rgb.red <= rgb.blue) {
        return rgb.red;
    } else if (rgb.green <= rgb.blue) {
        return rgb.green;
    } else {
        return rgb.blue;
    }
}

float get_max_rgb(struct RGB rgb) {
    if (rgb.red >= rgb.green && rgb.red >= rgb.blue) {
        return rgb.red;
    } else if (rgb.green >= rgb.blue) {
        return rgb.green;
    } else {
        return rgb.blue;
    }
}

/* returns max - min */
float get_range_rgb(struct RGB rgb) {
    return get_max_rgb(rgb) - get_min_rgb(rgb);
}

