#ifndef VECS_HPP
#define VECS_HPP

#include <opencv2/imgproc.hpp>
#include <math.h>

using namespace cv;

class vec2{
private:
    
public:
    double _x;
    double _y;
    
    vec2(double x, double y) : _x(x), _y(y){
    }
    
    vec2 normalize() const{
        double dist = sqrt(this->_x*this->_x + this->_y*this->_y);
        if(dist==0) return vec2(1.0, 0.0);
        return vec2(this->_x/dist, this->_y/dist);
    }
    
    double length(){
        return sqrt(this->_x*this->_x + this->_y*this->_y);
    }
    
    /* Overloaded operators*/
    vec2 operator+(const vec2& right){
        return vec2(this->_x+right._x, this->_y+right._y);
    }
    vec2 operator-(const vec2& right){
        return vec2(this->_x-right._x, this->_y-right._y);
    }
    vec2 operator*(const double& right){
        return vec2(this->_x*right, this->_y*right);
    }
    double operator^(const vec2& right){  //DOT PRODUCT
        return this->_x*right._x + this->_y*right._y;
    }
    vec2 operator/(const vec2& right){
        double result_x = (right._x)?this->_x/right._x:1.0;
        double result_y = (right._y)?this->_y/right._y:1.0;
        return vec2(result_x, result_y);
    }
    
    vec2& operator += (const vec2& right){
        this->_x += right._x;
        this->_y += right._y;
        return *this;
    }
};







class vec3{
private:
    
public:
    double _x;
    double _y;
    double _z;
    
    vec3(double x, double y, double z) : _x(x), _y(y), _z(z){
    }
    
    vec3 normalize() const{
        double dist = sqrt(this->_x*this->_x + this->_y*this->_y + this->_z*this->_z);
        if(dist==0) return vec3(1.0, 0.0, 0.0);
        return vec3(this->_x/dist, this->_y/dist, this->_z/dist);
    }
    
    double length(){
        return sqrt(this->_x*this->_x + this->_y*this->_y + this->_z*this->_z);
    }
    
    /* Overloaded operators*/
    vec3 operator+(const vec3& right){
        return vec3(this->_x+right._x, this->_y+right._y, this->_z+right._z);
    }
    vec3 operator-(const vec3& right){
        return vec3(this->_x-right._x, this->_y-right._y, this->_z+right._z);
    }
    vec3 operator*(const double& right){
        return vec3(this->_x*right, this->_y*right, this->_z*right);
    }
    double operator^(const vec3& right){  // DOT PRODUCT
        return this->_x*right._x + this->_y*right._y + this->_z*right._z;
    }
    vec3 operator/(const vec3& right){
        double result_x = (right._x)?this->_x/right._x:1.0;
        double result_y = (right._y)?this->_y/right._y:1.0;
        double result_z = (right._z)?this->_z/right._z:1.0;
        return vec3(result_x, result_y, result_z);
    }
    
    vec3& operator += (const vec3& right){
        this->_x += right._x;
        this->_y += right._y;
        this->_z += right._z;
        return *this;
    }
    
};


#endif /* VECS_HPP */

