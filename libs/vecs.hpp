#ifndef VECS_HPP
#define VECS_HPP

#include <opencv2/imgproc.hpp>
#include <math.h>

using namespace cv;


class vec{
private:
    unsigned short _dim;
public:
    double _x;
    double _y;
    double _z;
    double _w;
    vec(const vec& othervec){
        this->_x = othervec._x;
        this->_y = othervec._y;
        this->_z = othervec._z;
        this->_w = othervec._w;
        this->_dim = othervec._dim;
    }
    vec(double x, double y):_x(x), _y(y){
        this->_z = 0;
        this->_w = 0;
        this->_dim = 2;
    }
    vec(double x, double y, double z):_x(x), _y(y), _z(z){
        this->_w = 0;
        this->_dim = 3;
    }
    vec(double x, double y, double z, double w):_x(x), _y(y), _z(z), _w(w){
        this->_dim = 4;
    }
    double getDimension(){
        return this->_dim;
    }
    double length(){
        return sqrt(this->_x*this->_x + this->_y*this->_y+this->_z*this->_z+this->_w*this->_w);
    }
    vec& normalize(){
        double dist = this->length();
        if(dist!=0){
            this->_x /= dist;
            this->_y /= dist;
            this->_z /= dist;
            this->_w /= dist;
        }
        return *this;
    }
    vec& cross(vec B){
        //only vec3-s for now
        double _x =  this->_y*B._z - this->_z*B._y;
        double _y = -this->_x*B._z + this->_z*B._x;
        double _z =  this->_x*B._y - this->_y*B._x;
        this->_x=_x, this->_y=_y, this->_z=_z, this->_dim=3;
        return *this;
    }
    vec& clamp_x(double _min, double _max){
        this->_x = min(max(this->_x, _min), _max);
        return *this;
    }
    vec& clamp_y(double _min, double _max){
        this->_y = min(max(this->_y, _min), _max);
        return *this;
    }
    vec& clamp_z(double _min, double _max){
        this->_z = min(max(this->_z, _min), _max);
        return *this;
    }
    vec& clamp_w(double _min, double _max){
        this->_w = min(max(this->_w, _min), _max);
        return *this;
    }
    vec& clamp(double _min, double _max){
        this->clamp_x(_min, _max);
        this->clamp_y(_min, _max);
        if (this->_dim > 2) this->clamp_z(_min, _max);
        if (this->_dim > 3) this->clamp_w(_min, _max);
        return *this;
    }
    vec& vecAbs(){
        this->_x = abs(this->_x);
        this->_y = abs(this->_y);
        this->_z = abs(this->_z);
        this->_w = abs(this->_w);
        return *this;
    }
    vec& vecMax(double _max){
        this->_x = max(_max, this->_x);
        this->_y = max(_max, this->_y);
        this->_z = max(_max, this->_z);
        this->_w = max(_max, this->_w);
        return *this;
    }
    /* Overloaded operators*/
public:
    vec operator+(const vec& right){
        return vec(this->_x+right._x, this->_y+right._y, this->_z+right._z, this->_w+right._w);
    }
    vec operator-(const vec& right){
        return vec(this->_x-right._x, this->_y-right._y, this->_z-right._z, this->_w-right._w);
    }
    vec operator*(const double& right){
        return vec(this->_x*right, this->_y*right, this->_z*right, this->_w*right);
    }
    vec operator/(const double& right){
        return vec(this->_x/right, this->_y/right, this->_z/right, this->_w/right);
    }
    double operator^(const vec& right){  // DOT PRODUCT
        return this->_x*right._x + this->_y*right._y + this->_z*right._z + this->_w*right._w;
    }
    vec operator%(const vec& right){  // modulo - only vec3
        vec result(*this);
        vec y(right);
        if(y.length()){
            result -= y*(floor(result.length()/y.length()));
        }
        return result;
    }
    vec operator/(const vec& right){
        double result_x = (right._x)?this->_x/right._x:1.0;
        double result_y = (right._y)?this->_y/right._y:1.0;
        double result_z = (right._z)?this->_z/right._z:1.0;
        double result_w = (right._w)?this->_w/right._w:1.0;
        return vec(result_x, result_y, result_z, result_w);
    }
    
    vec& operator += (const vec& right){
        this->_x += right._x;
        this->_y += right._y;
        this->_z += right._z;
        this->_w += right._w;
        return *this;
    }
    vec& operator -= (const vec& right){
        this->_x -= right._x;
        this->_y -= right._y;
        this->_z -= right._z;
        this->_w -= right._w;
        return *this;
    }
    vec& operator *= (const double& factor){
        this->_x *= factor;
        this->_y *= factor;
        this->_z *= factor;
        this->_w *= factor;
        return *this;
    }
    vec& operator /= (const double& factor){
        this->_x /= factor;
        this->_y /= factor;
        this->_z /= factor;
        this->_w /= factor;
        return *this;
    }
    /* Reflections and such */
public:
    vec& convertTo2D(){
        this->_z=0, this->_w=0, this->_dim=2;
        return *this;
    }
    vec& convertTo3D(){
        this->_w=0, this->_dim=3;
        return *this;
    }
    vec& convertTo4D(){
        this->_dim=4;
        return *this;
    }
    
};


#endif /* VECS_HPP */

