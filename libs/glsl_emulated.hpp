#ifndef GLSL_EMULATED_HPP
#define GLSL_EMULATED_HPP

#include "vecs.hpp"
#include <math.h>

namespace e_glsl{
    
    double clamp(double value, double _min, double _max){
        return min(max(value, _min), _max);
    }

    vec reflect(vec I, vec N){
        return I-(N*(N^I)*2.0);
    }
    
    vec normalize(vec I){
        double dist = I.length();
        vec result(I);
        if(dist!=0) result /= dist;
        return result;
    }
    
    vec cross(vec A, vec B){
        //only vec3-s for now
        double _x =  A._y*B._z -A._z*B._y;
        double _y = -A._x*B._z +A._z*B._x;
        double _z =  A._x*B._y -A._y*B._x;
        return vec(_x, _y, _z);
    }
}

#endif /* GLSL_EMULATED_HPP */

