#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "vecs.hpp"

namespace shapes{
    
    double sphere(vec p_3d, double radius){
        return p_3d.length() - radius;
    }
    
    double sphere(vec p_3d, vec center_3d, double radius){
        return (p_3d-center_3d).length() - radius;
    }
    
    double udBox( vec p_3d, vec b_3d )
    {
        return (p_3d.vecAbs()-b_3d).vecMax(0.0).length();
    }

    double udRoundBox(vec p_3d, vec b_3d, double r )
    {
      return udBox(p_3d, b_3d)-r;
    }

    // I should add more shapes from
    // http://iquilezles.org/www/articles/distfunctions/distfunctions.htm
    
}


#endif /* SHAPES_HPP */

