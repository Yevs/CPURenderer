//
// Created by eugene on 24.06.15.
//

#ifndef CPURENDERER_MODEL_H
#define CPURENDERER_MODEL_H

#include <vector>
#include "geometry.h"
#include "tgaimage.h"

class Model {
private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<Vec3i>> faces_;
    std::vector<Vec2f> uv_;
    std::vector<Vec3f> vn_;
    TGAImage _diffusemap;

public:
    void load_texture(std::string filename, const char *suffix, TGAImage &img);
    Model(const char *filename);
    ~Model();
    int nverts();
    int nfaces();
    Vec3f vert(int i);
    std::vector<Vec3i> face(int idx);
    TGAColor getDiffusive(Vec2i uv);
    Vec2i uv(int iface, int nvert);
};


#endif //CPURENDERER_MODEL_H
