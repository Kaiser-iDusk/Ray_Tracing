#ifndef RAYLIB_HPP
#define RAYLIB_HPP

#include <cmath>

struct Vec3{
    double x, y, z;
    Vec3(){x=y=z=0;}
    Vec3(double x_, double y_, double z_) {x = x_; y = y_; z = z_;}
    Vec3 operator + (const Vec3 b){return Vec3(x+b.x, y+b.y, z+b.z);}
    Vec3 operator - (const Vec3 b){return Vec3(x-b.x, y-b.y, z-b.z);}
    Vec3 operator * (double c){return Vec3(c*x, x*y, c*z);}
    Vec3 operator / (double c){return Vec3(x/c, y/c, z/c);}
    // Vec3 operator = (const Vec3 b){return Vec3(b.x, b.y, b.z);}
};

struct Ray{
    Vec3 o;
    Vec3 d;
    Ray(Vec3& org, Vec3& dir){
        o = org;
        d = dir;
    }
};

#endif