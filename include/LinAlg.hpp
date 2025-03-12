#ifndef LINALG_HPP
#define LINALG_HPP

#include "./RayLib.hpp"

class LinAlg{
public:
    Vec3 cross(Vec3 a, Vec3 b){
        Vec3 res((a.y * b.z - b.y * a.z), -(a.x * b.z - a.z * b.x), (a.x * b.y - b.x * a.y));
        return res;
    }
    Vec3 proj(Vec3 u, Vec3 normal){
        Vec3 unit_normal = normal / norm(normal);
        Vec3 proj = cross(unit_normal, cross(u, unit_normal));
        return proj;
    }
    Vec3 reflect(Vec3 a, Vec3 normal){
        Vec3 project = proj(a, normal);
        Vec3 res = (project*2) - a;
        return res;
    }
    double dot(const Vec3 a, const Vec3 b){return (a.x*b.x + a.y*b.y + a.z*b.z);}
    double norm(const Vec3 a){return pow((a.x*a.x + a.y*a.y + a.z*a.z), 0.5);}
};

#endif