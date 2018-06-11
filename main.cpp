/* Inspired by the tutorial @ http://xdpixel.com/ray-marching-101-part-2/ */
/*
 Grgo Mariani
 */
#include <math.h>
#include <cstdlib>
#include <opencv2/imgproc.hpp>

#include "libs/vecs.hpp"
#include "libs/util.hpp"
#include "libs/glsl_emulated.hpp"

using namespace std;
using namespace cv;

const vec resolution_2d = vec(320, 240);
double _ratio=1.0;
vec cameraPosition_3d(0.0, 0.0, -10.0);
vec lightPosition_3d(3.0, 4.5, -10.0);


/**** This is our program Start . No need to edit this*/
int main(int argc, char** argv) {
    Mat frame(resolution_2d._y, resolution_2d._x, CV_8UC3, Scalar(0, 0, 0));
    _ratio = resolution_2d._x / resolution_2d._y;
    while(true){
        UTIL::renderImage(frame);
        UTIL::displayResult(frame, true);
    }
    return 0;
}

/* Define functions we'll use */
double sphere(vec p_3d, double radius){
    return p_3d.length() - radius;
}

double map(vec p_3d){
    return sphere(p_3d, 3.0);
}

vec getNormal(vec p_3d){
    double _delta = 0.001;
    double deltaX = map(p_3d+vec(_delta, 0.0, 0.0)) - map(p_3d-vec(_delta, 0.0, 0.0));
    double deltaY = map(p_3d+vec(0.0, _delta, 0.0)) - map(p_3d-vec(0.0, _delta, 0.0));
    double deltaZ = map(p_3d+vec(0.0, 0.0, _delta)) - map(p_3d-vec(0.0, 0.0, _delta));
    return vec(deltaX, deltaY, deltaZ).normalize();
}

float trace(vec origin_3d, vec direction_3d, vec& p_3d){
    double totalDistanceTraveled = 0.0;
    for(int i=0; i<32; ++i){
        p_3d = origin_3d + direction_3d*totalDistanceTraveled;
        double distanceFromPointOnRayToClosestObjectInScene = map( p_3d );
        totalDistanceTraveled += distanceFromPointOnRayToClosestObjectInScene;
        
        if( distanceFromPointOnRayToClosestObjectInScene < 0.0001 )
        {
            break;
        }
        
        if( totalDistanceTraveled > 10000.0 )
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
    
    vec diffuseColor_c = vec(0.0, 255.0, 0.0)*diffuseStrength;
    vec reflectedLightVector_3d = ( e_glsl::reflect( vec(0.0, 0.0, 0.0)-fromPointToLight_3d, surfaceNormal_3d ) ).normalize();
    
    vec fromPointToCamera_3d = ( cameraPosition_3d - pointOnSurface_3d ).normalize();
    double specularStrength = pow( e_glsl::clamp( reflectedLightVector_3d^fromPointToCamera_3d, 0.0, 1.0 ), 10.0 );
    
    specularStrength = min( diffuseStrength, specularStrength );
    vec specularColor_c = vec( 255.0, 255.0, 255.0 )*specularStrength;
    
    vec finalColor_c = diffuseColor_c + specularColor_c;
    
    return finalColor_c;
}

/**** This function takes care of each pixel rendering */
vec renderXY(vec gl_FragCoord_2d){
    /* gl_FragCoord are current coordinates */
    /* uv are our screen coordinates        */
    vec uv_2d = (gl_FragCoord_2d/resolution_2d)*2.0 - vec(1.0, 1.0);
    uv_2d._x *= _ratio;
    
    vec cameraDirection_3d = vec(uv_2d._x, uv_2d._y, 1.0).normalize();
    
    vec pointOnSurface_3d(0.0, 0.0, 0.0);
    double distanceToClosestPointInScene = trace(cameraPosition_3d, cameraDirection_3d, pointOnSurface_3d);
    
    vec finalColor_c(0.0, 0.0, 0.0);
    
    if( distanceToClosestPointInScene>0.0 ){
        vec surfaceNormal_3d = getNormal(pointOnSurface_3d);
        finalColor_c = calculateLighting(pointOnSurface_3d, surfaceNormal_3d, lightPosition_3d, cameraPosition_3d);
    }
    
    return finalColor_c;
}


// to compile use 'g++ main.cpp -std=c++11 -o `pkg-config opencv --cflags --libs` raymarching'
//./raymarching | ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -i - -f mpegts -preset veryslow -vcodec libx264 udp://localhost:5000
// Use VLC to check results
// CTRL+N   and then    udp://@:5000
