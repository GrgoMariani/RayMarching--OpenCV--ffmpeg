#ifndef RENDER_HPP
#define RENDER_HPP

#include <math.h>
#include "libs/globals.hpp"
#include "libs/vecs.hpp"
#include "libs/glsl_emulated.hpp"
#include "libs/shapes.hpp"

/* Define functions we'll use */
double map(vec p_3d){
    using namespace shapes;
    return sphere(REPEAT(p_3d, vec(2, 2, 2)), 2);
}

vec getNormal(vec p_3d){
    double deltaX = map(p_3d+vec(EPSILON, 0.0, 0.0)) - map(p_3d-vec(EPSILON, 0.0, 0.0));
    double deltaY = map(p_3d+vec(0.0, EPSILON, 0.0)) - map(p_3d-vec(0.0, EPSILON, 0.0));
    double deltaZ = map(p_3d+vec(0.0, 0.0, EPSILON)) - map(p_3d-vec(0.0, 0.0, EPSILON));
    return vec(deltaX, deltaY, deltaZ).normalize();
}

float trace(vec origin_3d, vec direction_3d, vec& p_3d){
    double totalDistanceTraveled = 0.0;
    for(int i=0; i<MAX_STEPS; ++i){
        p_3d = origin_3d + direction_3d*totalDistanceTraveled;
        double distanceFromPointOnRayToClosestObjectInScene = map( p_3d );
        totalDistanceTraveled += distanceFromPointOnRayToClosestObjectInScene;
        
        if( distanceFromPointOnRayToClosestObjectInScene < 0.0001 )
        {
            break;
        }
        
        if( totalDistanceTraveled > MAX_DISTANCE )
        {
            totalDistanceTraveled = 0.0;
            break;
        }
    }
    return totalDistanceTraveled;
}


vec calculateLighting(vec pointOnSurface_3d, vec surfaceNormal_3d, vec lightPosition_3d, vec cameraPosition_3d){
    vec fromPointToLight_3d = (lightPosition_3d - pointOnSurface_3d).normalize();
    /* ^ is short for dot product*/
    double diffuseStrength = e_glsl::clamp(surfaceNormal_3d^fromPointToLight_3d, 0.0, 1.0 );
    
    vec diffuseColor_c = vec(1.0, 0.0, 0.0)*diffuseStrength;
    vec reflectedLightVector_3d = ( e_glsl::reflect( vec(0.0, 0.0, 0.0)-fromPointToLight_3d, surfaceNormal_3d ) ).normalize();
    
    vec fromPointToCamera_3d = ( cameraPosition_3d - pointOnSurface_3d ).normalize();
    double specularStrength = pow( e_glsl::clamp( reflectedLightVector_3d^fromPointToCamera_3d, 0.0, 1.0 ), 10.0 );
    
    specularStrength = min( diffuseStrength, specularStrength );
    vec specularColor_c = vec( 1.0, 1.0, 1.0 )*specularStrength;
    
    vec finalColor_c = diffuseColor_c + specularColor_c;
    finalColor_c.clamp(0, 1);
    finalColor_c *= 255.0;
    
    return finalColor_c;
}



#endif /* RENDER_HPP */

