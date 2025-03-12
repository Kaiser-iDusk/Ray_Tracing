#include "./include/LinAlg.hpp"
#include<fstream>
#include<iostream>
#include<cmath>

// struct Vec3{
//     double x, y, z;
//     Vec3(){x=y=z=0;}
//     Vec3(double x_, double y_, double z_) {x = x_; y = y_; z = z_;}
//     Vec3 operator + (const Vec3 b){return Vec3(x+b.x, y+b.y, z+b.z);}
//     Vec3 operator - (const Vec3 b){return Vec3(x-b.x, y-b.y, z-b.z);}
//     Vec3 operator * (double c){return Vec3(c*x, x*y, c*z);}
//     Vec3 operator / (double c){return Vec3(x/c, y/c, z/c);}
//     // Vec3 operator = (const Vec3 b){return Vec3(b.x, b.y, b.z);}
//     double dot(const Vec3 b){return (x*b.x + y*b.y + z*b.z);}
//     double norm(){return pow((x*x + y*y + z*z), 0.5);}
// };

// struct Ray{
//     Vec3 o;
//     Vec3 d;
//     Ray(Vec3& org, Vec3& dir){
//         o = org;
//         d = dir;
//     }
// };

struct Info{
    Vec3 pt;
    double lambda;
    Info(){
        lambda = 0;
    }
};

struct Sphere{
    double r;
    Vec3 c;
    Sphere(Vec3& center, double radius){
        r = radius;
        c = center;
    }
    bool intersect(Ray ray, Info* intersect){
        LinAlg solver;

        Vec3 o = ray.o, d = ray.d;
        Vec3 oc = (o - c);
        
        double b = 2 * solver.dot(oc, d);
        double a = pow(solver.norm(d), 2);
        double c = pow(solver.norm(oc), 2) - r*r;

        double disc = b*b - 4*a*c;
        if(disc< 0) return false;

        double t0 = -(b / 2) + 0.5 * pow(disc, 0.5);
        double t1 = -(b / 2) - 0.5 * pow(disc, 0.5);
        double lambda = (t0<t1)?t0:t1;
        intersect->lambda = lambda;
        intersect->pt = (o + (d * lambda));
        return true;
    }
};

struct Color{
    double r, g, b;
    Color(){r=g=b=0;}
    Color(double r_, double g_, double b_){r = r_; g = g_; b = b_;}
};

int main(){
    int W = 540, H = 540;

    std::ofstream out("out.ppm");
    out << "P3\n" << W << "\n" << H << "\n" << "255\n";

    Color pixel_col[H][W];
    Color white(255, 255, 255);
    Color red(255, 0, 0);
    Color green(0, 255, 0);
    Color blue(0, 0, 255);

    LinAlg solver;

    Vec3 center(W/2, H/2, 150), lgt_src_cen(75, 100, 50);
    Sphere sphere(center, 60);
    Sphere light_src(lgt_src_cen, 40);

    for(int y = 0; y< H; y++){
        for(int x = 0; x< W; x++){
            Vec3 org(x, y, 0);
            Vec3 dir(0, 0, 1);
            Ray ray(org, dir);

            Info intersect;
            if(sphere.intersect(ray, &intersect)){ 
                print(intersect.pt);
                Vec3 normal = (intersect.pt - center); 
                Vec3 refl = solver.reflect(dir, normal);
                Ray reflected(intersect.pt, refl);

                pixel_col[y][x] = red;

                if(light_src.intersect(reflected, &intersect)){
                    std::cout << "Intersect\n";
                    pixel_col[y][x].r = (pixel_col[y][x].r + 255) / 2.0;
                    pixel_col[y][x].g = (pixel_col[y][x].g + 255) / 2.0;
                    pixel_col[y][x].b = (pixel_col[y][x].b + 255) / 2.0;
                }
            }

            if(light_src.intersect(ray, &intersect)){
                pixel_col[y][x].r = 255;
                pixel_col[y][x].g = 255;
                pixel_col[y][x].b = 255;
            }

            out << pixel_col[y][x].r << "\n";
            out << pixel_col[y][x].g << "\n";
            out << pixel_col[y][x].b << "\n";
        }
    }

    out.close();

    return 0;
}