#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct {
    float e[3];
} vec3;

typedef vec3 point3;

/* constructors */ 

static inline vec3 vec3_make(float e0, float e1, float e2) {
    vec3 v = {{e0, e1, e2}};
    return v;
}

static inline vec3 vec3_zero(void) {
    return vec3_make(0.0, 0.0, 0.0); 
}

/* accessors */ 
static inline float vec3_x(const vec3 *v) {
    return v->e[0];
}

static inline float vec3_y(const vec3 *v) {
    return v->e[1];
}

static inline float vec3_z(const vec3 *v) {
    return v->e[2];
}

static inline float vec3_get(const vec3 *v, int i) {
    return v->e[i];
}

static inline float *vec3_at(vec3 *v, int i) {
    return &v->e[i];
}

/* in-place ops (like +=, *=, /=) */ 
static inline void vec3_add_eq(vec3 *a, const vec3 *b) {
    a->e[0] += b->e[0];
    a->e[1] += b->e[1];
    a->e[2] += b->e[2];
}

static inline void vec3_mul_eq(vec3 *v, float t) {
    v->e[0] *= t;
    v->e[1] *= t;
    v->e[2] *= t;
}

static inline void vec3_div_eq(vec3 *v, float t) {
    vec3_mul_eq(v, 1.0/ t);
}

/* non-mutating ops (replacing operator overloads) */ 
static inline vec3 vec3_neg(vec3 v) {
    return vec3_make(-v.e[0], -v.e[1], -v.e[2]);
}

static inline vec3 vec3_add(vec3 u, vec3 v) {
    return vec3_make(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

static inline vec3 vec3_sub(vec3 u, vec3 v){ 
    return vec3_make(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]); }

static inline vec3 vec3_mul(vec3 u, vec3 v){
    return vec3_make(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

static inline vec3 vec3_scale(vec3 v, float t) {
    return vec3_make(t*v.e[0], t*v.e[1], t*v.e[2]);
}

static inline vec3 vec3_div(vec3 v, float t) {
    return vec3_scale(v, 1.0/t);
}

static inline float vec3_dot(vec3 u, vec3 v) {
    return u.e[0]*v.e[0]+u.e[1]*v.e[1]+u.e[2]*v.e[2];
}

static inline vec3 vec3_cross(vec3 u, vec3 v) {
    return vec3_make(
        u.e[1]*v.e[2] - u.e[2]*v.e[1],
        u.e[2]*v.e[0] - u.e[0]*v.e[2],
        u.e[0]*v.e[1] - u.e[1]*v.e[0]
    );
}

static inline float vec3_length_squared(vec3 v) {
    return v.e[0]*v.e[0]+v.e[1]*v.e[1]+v.e[2]*v.e[2];
}

static inline float vec3_length(vec3 v) {
    return sqrt(vec3_length_squared(v));
}

static inline vec3 vec3_unit(vec3 v) {
    return vec3_div(v, vec3_length(v));
}

static inline void vec3_fprint(FILE *out, const vec3 *v) {
    fprintf(out, "%g %g %g\n", v->e[0], v->e[1], v->e[2]);
}

#endif



