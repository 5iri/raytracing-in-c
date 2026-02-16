#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"


void write_color(FILE *out, const vec3 pixel_color) {
    float r = vec3_x(&pixel_color);
    float g = vec3_y(&pixel_color);
    float b = vec3_z(&pixel_color);
    

    // Translate the [0,1] component values to the byte range of [0,255]

    int rbyte = (int)(255.99 * r);
    int gbyte = (int)(255.99 * g);
    int bbyte = (int)(255.99 * b);

    vec3 vec = vec3_make(rbyte, gbyte, bbyte);
    
    vec3_fprint(out, &vec);
}

#endif
