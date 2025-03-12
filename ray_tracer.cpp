#include "./include/LinAlg.hpp"
#include<fstream>
#include<iostream>
#include<cmath>


#define WIDTH 600
#define HEIGHT 512
#define K_A 0.2
#define BP_P 6.0
#define K_D 1.0
#define K_S 0.9

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
    Color(double r_, double g_, double b_){r = _clamp(r_); g = _clamp(g_); b = _clamp(b_);}

    static double _clamp(double x){
        if(x > 255.0) return 255.0;
        if(x < 0.0) return 0.0;
        return x;
    }

    static Color clamp(Color col){Color ret(_clamp(col.r), _clamp(col.g), _clamp(col.b)); return ret;}

    Color operator+(Color col){Color res(_clamp(r+col.r), _clamp(g+col.g), _clamp(b+col.b)); return res;}
    Color operator*(double val){Color res(_clamp(r*val), _clamp(g*val), _clamp(b*val)); return res;}
};

int main(){
    int W = WIDTH, H = HEIGHT;

    std::ofstream out("out.ppm");
    out << "P3\n" << W << "\n" << H << "\n" << "255\n";

    Color pixel_col[H][W];
    Color white(255, 255, 255);
    Color dark_gray(5, 5, 5);
    Color red(255, 0, 0);
    Color green(0, 255, 0);
    Color blue(0, 0, 255);

    LinAlg solver;

    Vec3 center(W/2, H/2, 150), lgt_src_cen(W/2, 0, 50);
    Sphere sphere(center, 100);
    Sphere light_src(lgt_src_cen, 1);

    for(int y = 0; y< H; y++){
        for(int x = 0; x< W; x++){
            Vec3 org(x, y, 0);
            Vec3 dir(0, 0, 1);
            Ray ray(org, dir);

            Info intersect;
            if(sphere.intersect(ray, &intersect)){ 
                Vec3 l_dir = (light_src.c - intersect.pt);
                Vec3 normal = (intersect.pt - center);
                Vec3 view_dir = dir * (-1.0);

                pixel_col[y][x] = red;

                // Bling-Phonng shading
                Vec3 bisector = (view_dir + l_dir);
                Vec3 h_dir = bisector / solver.norm(bisector);

                double nl = solver.dot((normal / solver.norm(normal)), (l_dir / solver.norm(l_dir)));
                double nh = solver.dot((normal / solver.norm(normal)), h_dir);
                
                double dt1 = std::max(0.0, nl), dt2 = pow(std::max(0.0, nh), BP_P); 

                pixel_col[y][x] = Color::clamp(red + (dark_gray * K_A) + (white * (K_D * dt1 + K_S * dt2)));
            }

            if(light_src.intersect(ray, &intersect)){
                pixel_col[y][x].r = 255;
                pixel_col[y][x].g = 255;
                pixel_col[y][x].b = 255;
            }

            out << (int)pixel_col[y][x].r << "\n";
            out << (int)pixel_col[y][x].g << "\n";
            out << (int)pixel_col[y][x].b << "\n";
        }
    }

    out.close();

    return 0;
}