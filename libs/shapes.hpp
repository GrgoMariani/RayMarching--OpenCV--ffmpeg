#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "vecs.hpp"
#include "glsl_emulated.hpp"
#include <math.h>

namespace shapes{
    
    double sphere(vec p_3d, double radius){
        return p_3d.length() - radius;
    }
    
    double udBox( vec p_3d, vec b_3d )
    {
        return (p_3d.vecAbs()-b_3d).vecMax(0.0).length();
    }

    double udRoundBox(vec p_3d, vec b_3d, double r )
    {
      return udBox(p_3d, b_3d)-r;
    }

    double sdTorus( vec p_3d, vec t_2d )
    {
        vec p_3dxz(p_3d._x, p_3d._z);
        vec q_2d = vec(p_3dxz.length()-t_2d._x,p_3d._y);
        return q_2d.length()-t_2d._y;
    }

    double sdCylinder( vec p_3d, vec c_3d )
    {
        return (vec(p_3d._x, p_3d._z)-vec(c_3d._x, c_3d._y)).length()-c_3d._z;
    }
    
    double sdCone( vec p_3d, vec c_2d )
    {
        c_2d.normalize();
        double q = vec(p_3d._x, p_3d._y).length();
        return c_2d^vec(q, p_3d._z);
    }
    
    double sdPlane( vec p_3d, vec n_4d )
    {
        n_4d.normalize();
        return (p_3d^n_4d) + n_4d._w;
    }

    double sdHexPrism( vec p_3d, vec h_2d )
    {
        vec q_3d = p_3d.vecAbs();
        return max(q_3d._z-h_2d._y, max((q_3d._x*0.866025+q_3d._y*0.5),q_3d._y)-h_2d._x);
    }
    
    double sdTriPrism( vec p_3d, vec h_2d )
    {
        vec q = p_3d.vecAbs();
        return max(q._z-h_2d._y,max(q._x*0.866025+p_3d._y*0.5,-p_3d._y)-h_2d._x*0.5);
    }

    double sdCapsule( vec p_3d, vec a_3d, vec b_3d, double r )
    {
        vec pa_3d = p_3d - a_3d, ba_3d = b_3d - a_3d;
        double h = e_glsl::clamp( (pa_3d^ba_3d)/(ba_3d^ba_3d), 0.0, 1.0 );
        return (pa_3d - ba_3d*h).length() - r;
    }

    double sdCappedCylinder( vec p_3d, vec h_2d )
    {
        vec d_2d = vec(vec(p_3d._x, p_3d._z).length(), p_3d._y).vecAbs() - h_2d;
        return min(max(d_2d._x,d_2d._y),0.0) + d_2d.vecMax(0.0).length();
    }
    
    double sdEllipsoid( vec p_3d, vec r_3d)
    {
        return ( (p_3d/r_3d).length() - 1.0) * min(min(r_3d._x,r_3d._y),r_3d._z);
    }


    double UNION( double d1, double d2 )
    {
        return min(d1,d2);
    }

    double SUBSTRACT( double d1, double d2 )
    {
        return max(-d1,d2);
    }

    double INTERSECT( double d1, double d2 )
    {
        return max(d1,d2);
    }
    
    vec REPEAT( vec p_3d, vec c_3d)
    {
        // usage:  sphere(REPEAT(p_3d), 5)
        vec q_3d = (p_3d%c_3d)-(c_3d/2.0);
        return q_3d;
    }
    

    // Shapes added from
    // http://iquilezles.org/www/articles/distfunctions/distfunctions.htm
    
    
}


#endif /* SHAPES_HPP */

