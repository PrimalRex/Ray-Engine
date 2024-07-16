
#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H
#include "vec3.h"



class world_object {
public:
    world_object() {}
    world_object(vec3 pos, vec3 color, vec3 scale) : m_position(pos), m_albedoColor(color), m_scale(scale) {}

    vec3 m_position;
    vec3 m_albedoColor;
    vec3 m_scale;

    virtual ~world_object() {}

};

class sphere : public world_object {
public:
    sphere() : world_object() {}
    sphere(vec3 pos, vec3 color, vec3 scale) : world_object(pos, color, scale) {}
};


#endif //WORLD_OBJECT_H
