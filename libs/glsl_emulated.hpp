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
}

#endif /* GLSL_EMULATED_HPP */

