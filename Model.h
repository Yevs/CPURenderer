//
// Created by eugene on 24.06.15.
//

#ifndef CPURENDERER_MODEL_H
#define CPURENDERER_MODEL_H

#include <vector>
#include "geometry.h"

class Model {
private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<int>> faces_;

public:
    Model(const char *filename);
    ~Model();
    int nverts();
    int nfaces();
    Vec3f vert(int i);
    std::vector<int> face(int idx);
};


#endif //CPURENDERER_MODEL_H
