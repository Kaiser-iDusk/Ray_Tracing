#include<fstream>
#include<iostream>
#include<cmath>

struct Vec3{
    double x, y, z;
    Vec3(){x=y=z=0;}
    Vec3(double x_, double y_, double z_) {x = x_; y = y_; z = z_;}
    Vec3 operator + (const Vec3 b){return Vec3(x+b.x, y+b.y, z+b.z);}
    Vec3 operator - (const Vec3 b){return Vec3(x-b.x, y-b.y, z-b.z);}
    Vec3 operator * (double c){return Vec3(c*x, x*y, c*z);}
    Vec3 operator / (double c){return Vec3(x/c, y/c, z/c);}
    Vec3 operator = (const Vec3 b){return Vec3(b.x, b.y, b.z);}
    double dot(const Vec3 b){return (x*b.x + y*b.y + z*b.z);}
    double norm(){return pow((x*x + y*y + z*z), 0.5);}
};

struct Ray{
    Vec3 o;
    Vec3 d;
    Ray(Vec3& org, Vec3& dir){
        o = org;
        d = dir;
    }
};

struct Sphere{
    double r;
    Vec3 c;
    Sphere(Vec3& center, double radius){
        r = radius;
        c = center;
    }
    bool intersect(Ray& ray){
        Vec3 o = ray.o, d = ray.d;
        Vec3 oc = (o - c);
        
        double b = 2 * oc.dot(d);
        double a = pow(d.norm(), 2);
        double c = pow(oc.norm(), 2) - r*r;

        double disc = b*b - 4*a*c;
        if(disc< 0) return false;
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

    Vec3 center(W/2, H/2, 50);
    Sphere sphere(center, 20);

    for(int y = 0; y< H; y++){
        for(int x = 0; x< W; x++){
            Vec3 org(x, y, 0);
            Vec3 dir(0, 0, 1);
            Ray ray(org, dir);

            if(sphere.intersect(ray)){
                std::cout << "(" << y << ", " << x << ") ray intersect\n";  

                pixel_col[y][x].r = 255;
                pixel_col[y][x].g = 0;
                pixel_col[y][x].b = 0;
            }

            out << pixel_col[y][x].r << "\n";
            out << pixel_col[y][x].g << "\n";
            out << pixel_col[y][x].b << "\n";
        }
    }

    out.close();

    return 0;
}