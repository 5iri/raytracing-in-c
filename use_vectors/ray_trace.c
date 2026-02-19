#include "color.h"
#include "vec3.h"
#include <stdbool.h>

float hit_sphere(const point3 center, float radius, point3 ray_origin, vec3 ray_direction) {
    vec3 oc = vec3_sub(ray_origin, center);
    float a = vec3_length_squared(ray_direction);
    float h = vec3_dot(oc, ray_direction);
    float c = vec3_dot(oc, oc) - radius * radius;
    float discriminant = h * h - a * c;
    
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-h - sqrt(discriminant))/ a;
    }
}

vec3 ray_color(point3 ray_origin, vec3 ray_direction) {
    float t = hit_sphere(vec3_make(0.0f, 0.0f, -1.0f), 0.5f, ray_origin, ray_direction);
    if (t > 0.0f) {
        point3 sphere_center = vec3_make(0.0f, 0.0f, -1.0f);
        point3 hit_point = vec3_add(ray_origin, vec3_scale(ray_direction, t));
        vec3 normal = vec3_unit(vec3_sub(hit_point, sphere_center));
        vec3 one = vec3_make(1.0f, 1.0f, 1.0f);
        return vec3_scale(vec3_add(normal, one), 0.5f);
    }

    vec3 unit_direction = vec3_unit(ray_direction);
    float a = (vec3_y(&unit_direction) + 1.0f) * 0.5f;
    vec3 white = vec3_make(1.0f, 1.0f, 1.0f);
    vec3 blue = vec3_make(0.5f, 0.7f, 1.0f);
    return vec3_add(vec3_scale(white, 1.0f - a), vec3_scale(blue, a));
}

int main() {
    // Image
    float aspect_ratio = 16.0f / 9.0f;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    float focal_length = 1.0f;
    float viewport_height = 2.0f;
    float viewport_width = viewport_height * ((float)image_width / (float)image_height);
    point3 camera_center = vec3_zero();

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3_make(viewport_width, 0.0f, 0.0f);
    vec3 viewport_v = vec3_make(0.0f, -viewport_height, 0.0f);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = vec3_div(viewport_u, (float)image_width);
    vec3 pixel_delta_v = vec3_div(viewport_v, (float)image_height);

    // Calculate the location of the upper left pixel.
    point3 viewport_upper_left = vec3_sub(
        vec3_sub(vec3_sub(camera_center, vec3_make(0.0f, 0.0f, focal_length)), vec3_div(viewport_u, 2.0f)),
        vec3_div(viewport_v, 2.0f)
    );
    point3 pixel00_loc = vec3_add(viewport_upper_left, vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5f));

    // Render
    printf("P3\n%d %d\n255\n", image_width, image_height);
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            point3 pixel_center = vec3_add(
                pixel00_loc,
                vec3_add(vec3_scale(pixel_delta_u, (float)i), vec3_scale(pixel_delta_v, (float)j))
            );
            vec3 ray_direction = vec3_sub(pixel_center, camera_center);
            write_color(stdout, ray_color(camera_center, ray_direction));
        }
    }

    return 0;
}
