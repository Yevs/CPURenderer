#include "tgaimage.h"
#include "Model.h"
#include <algorithm>
#include <cmath>
#include <string.h>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

Model *model = NULL;

bool isDegenerated(Vec3i vec3, Vec3i t1, Vec3i t2);

const int width = 800;
const int height = 800;
const int depth = 255;

void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) { //transpose if steep line
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) { //make it left to right
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(dy) * 2, error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error += derror;
        if (error > dx * 2) {
            y += y1 > y0 ? 1 : -1;
            error -= dx * 2;
        }
    }
}

int vectorProd(Vec2i a, Vec2i b) {
    return a.x * b.y - a.y * b.x;
}

int find_z(int x, int y, Vec3i t0, Vec3i t1, Vec3i t2) {
    int divider = (t1.x  - t0.x) * (t2.y - t0.y) - (t1.y - t0.y) * (t2.x - t0.x);
    int a = (t1.x - t0.x) * (t2.z - t0.z) - (t1.z - t0.z) * (t2.x - t0.x);
    int b = (t1.y - t0.y) * (t2.z - t0.z) - (t1.z - t0.z) * (t2.y - t0.y);
    if (divider == 0) return std::numeric_limits<int>::min();
    return std::round(t0.z + (y - t0.y) * a / (1. * divider) - (x - t0.x) * b/ (1. * divider));
}

bool insideTriangle(int x, int y, Vec3i t0, Vec3i t1, Vec3i t2) {
    Vec2i a(t0.x - x, t0.y - y), b(t1.x - x, t1.y - y), c(t2.x - x, t2.y - y);
    return vectorProd(a, b) * vectorProd(b, c) >= 0 &&
           vectorProd(b, c) * vectorProd(c, a) >= 0 &&
           vectorProd(c, a) * vectorProd(a, b) >= 0;
}

void triangle(Vec3i t0, Vec3i t1, Vec3i t2, int* zbuf, TGAImage& image, const TGAColor& color) {
    if (isDegenerated(t0,t1,t2)) return;
    int boundbox[4] = {std::min(t0.x, std::min(t1.x, t2.x)), std::min(t0.y, std::min(t1.y, t2.y)),
                       std::max(t0.x, std::max(t1.x, t2.x)), std::max(t0.y, std::max(t1.y, t2.y))};
    for (int x = boundbox[0]; x <= boundbox[2]; x++) {
        for (int y = boundbox[1]; y <= boundbox[3]; y++) {
            if (insideTriangle(x, y, t0, t1, t2)) {
                int idx = x + y * width;
                int z = find_z(x, y, t0, t1, t2);
                if (zbuf[idx] < z) {
                    zbuf[idx] =  z;
                    image.set(x, y, color);
                }
            }
        }
    }
}

bool isDegenerated(Vec3i t0, Vec3i t1, Vec3i t2) {
    if (t0.y==t1.y && t0.y==t2.y) {
        return true;
    }
    if (t0.x == t1.x && t0.x == t2.x) {
        return true;
    }
    Vec2i a(t1.x - t0.x, t1.y - t0.y);
    Vec2i b(t2.x - t0.x, t2.y - t0.y);
    int res = a.x * b.y - a.y * b.x;
    if (res == 0) {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);
    if (argc == 2) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }
    Vec3f light_dir(0, 0, -1);
    int* zbuffer = new int[width*height];
    memset(zbuffer, std::numeric_limits<int>::min(), sizeof(zbuffer));
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3i screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(face[j]);
            world_coords[j] = v;
            screen_coords[j] = Vec3i((v.x+1.)*width/2., (v.y+1.)*height/2., (v.z + 1.) * depth / 2.);
        }
        Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0) {
            triangle(screen_coords[0], screen_coords[1], screen_coords[2], zbuffer, image,
                     TGAColor(intensity*255, intensity*255, intensity*255, 255));
        }
    }
    image.flip_vertically();
    image.write_tga_file("/home/eugene/Documents/image.tga");
    delete model;
    return 0;
}