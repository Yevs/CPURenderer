//
// Created by eugene on 24.06.15.
//

#include <fstream>
#include <sstream>
#include "Model.h"
#include "tgaimage.h"

Model::~Model() {};

Model::Model(const char *filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            iss >> v.x >> v.y >> v.z;
            verts_.push_back(v);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f uv;
            iss >> uv.x >> uv.y;
            uv_.push_back(uv);
        } else if (!line.compare(0, 3, "vn ")){
            iss >> trash >> trash;
            Vec3f vn;
            iss >> vn.x >> vn.y >> vn.z;
            vn_.push_back(vn);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<Vec3i> f;
            int itrash;
            Vec3i tmp;
            iss >> trash;
            while (iss >> tmp.x >> trash >> tmp.y >> trash >> tmp.z) {
                tmp.x--; // in wavefront obj all indices start at 1, not zero
                tmp.y--; // in wavefront obj all indices start at 1, not zero
                tmp.z--; // in wavefront obj all indices start at 1, not zero
                f.push_back(tmp);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
    load_texture(filename, "_diffuse.tga", _diffusemap);
};

int Model::nverts() { return (int) verts_.size(); }
int Model::nfaces() { return (int) faces_.size(); }

std::vector<Vec3i> Model::face(int idx) {
    return faces_[idx];
}
Vec3f Model::vert(int i) {
    return verts_[i];
}

void Model::load_texture(std::string filename, const char *suffix, TGAImage &img) {
    std::string texfile(filename);
    size_t dot = texfile.find_last_of(".");
    if (dot!=std::string::npos) {
        texfile = texfile.substr(0,dot) + std::string(suffix);
        std::cerr << "texture file " << texfile << " loading " <<
                (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
        img.flip_vertically();
    }
}

TGAColor Model::getDiffusive(Vec2i uv) {
    return _diffusemap.get(uv.x, uv.y);
}

Vec2i Model::uv(int iface, int nvert) {
    int idx = faces_[iface][nvert].y;
    return Vec2i(uv_[idx].x*_diffusemap.get_width(), uv_[idx].y*_diffusemap.get_height());
}