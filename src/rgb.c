#include "rgb.h"


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

