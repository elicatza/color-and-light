#ifndef HSV_H
#define HSV_H

struct HSV {
    float hue;
    float saturation;
    float value;
};

float hsv_rgb_value(struct RGB rgb);
float hsv_rgb_saturation(struct RGB rgb);
float hsv_rgb_hue(struct RGB rgb);

#endif
