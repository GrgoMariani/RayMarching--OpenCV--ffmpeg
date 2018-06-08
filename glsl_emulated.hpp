#ifndef GLSL_EMULATED_HPP
#define GLSL_EMULATED_HPP

#include "vecs.hpp"
#include <math.h>

namespace e_glsl{
    
    double clamp(double value, double _min, double _max){
        return min(max(value, _min), _max);
    }

    vec3 reflect(vec3 I, vec3 N){
        return I-(N*(N^I)*2.0);
    }
    
}

#endif /* GLSL_EMULATED_HPP */
