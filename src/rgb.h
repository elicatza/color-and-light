#ifndef RGB_H
#define RGB_H

struct RGB {
    float red;
    float green;
    float blue;
};

struct RGB parse_rgb(struct RGB rgb);
float get_min_rgb(struct RGB rgb);
float get_max_rgb(struct RGB rgb);

#endif
