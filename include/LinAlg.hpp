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
        Vec3 perp_dir, unit_perp;
        perp_dir = cross(normal, cross(u, normal));
        unit_perp = (perp_dir / norm(perp_dir));
        double mag = norm(perp_dir) * pow(1 - pow(dot(normal / norm(normal), u / norm(u)), 2), 0.5);
        Vec3 perp = (unit_perp * mag);
        return (u - perp);
    }
    Vec3 reflect(Vec3 a, Vec3 normal){
        Vec3 project = proj(a, normal);
        Vec3 temp = (project - a);
        Vec3 res = (a + (temp * 2));
        return res;
    }
    double dot(const Vec3 a, const Vec3 b){return (a.x*b.x + a.y*b.y + a.z*b.z);}
    double norm(const Vec3 a){return pow((a.x*a.x + a.y*a.y + a.z*a.z), 0.5);}
};

#endif