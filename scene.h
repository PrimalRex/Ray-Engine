
#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include "world_object.h"
#include <vector>

struct Scene {
    std::vector<world_object*> Objects;
};

#endif //SCENE_H
