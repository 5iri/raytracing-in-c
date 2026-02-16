#include "color.h"
#include "vec3.h"

int main() {

    // Image

    int image_width = 256;
    int image_height = 256;

    // Render 

    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
         for (int i = 0; i < image_width; i++) {
            vec3 pixel_color = vec3_make(((float)i/(image_height-1)), ((float)j/(image_height-1)), 0.0);
         write_color(stdout, pixel_color);
         }
    }
    return 0;
}
