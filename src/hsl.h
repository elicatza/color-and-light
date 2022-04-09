#ifndef HSL_H
#define HSL_H


struct HSL {
    float hue;
    float saturation;
    float luminance;
};

float hsl_rgb_luminance(struct RGB rgb);
float hsl_rgb_saturation(struct RGB rgb);
float hsl_rgb_hue(struct RGB rgb);

#endif
