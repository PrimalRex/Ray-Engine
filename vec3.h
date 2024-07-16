#ifndef VEC3_H
#define VEC3_H
#include <cmath>

class vec3 {
public:
    double x,y,z;

    vec3() {}
    vec3 (double x2, double y2, double z2) : x(x2), y(y2), z(z2) {}

    inline static double Dot(const vec3 &v1, const vec3 &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    void Normalize (){
        double l = 1.0/sqrt (x*x + y*y + z*z);
        x*=l; y*=l; z*=l;
    }

    const vec3 operator- (const vec3 &vec) const
    { return vec3 (x-vec.x, y-vec.y, z-vec.z); }

    const vec3 operator+ (const vec3 &vec) const
    { return vec3 (x+vec.x, y+vec.y, z+vec.z); }

    const vec3 operator* (double fact) const
    { return vec3 (x*fact, y*fact, z*fact); }

};



#endif //VEC3_H
