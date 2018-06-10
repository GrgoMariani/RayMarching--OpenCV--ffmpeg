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

const vec2 resolution = vec2(320, 240);
double _ratio=1.0;
vec3 cameraPosition(0.0, 0.0, -10.0);
vec3 lightPosition(3.0, 4.5, -8.0);


/**** This is our program Start . No need to edit this*/
int main(int argc, char** argv) {
    Mat frame(resolution._y, resolution._x, CV_8UC3, Scalar(0, 0, 0));
    _ratio = resolution._x / resolution._y;
    while(true){
        UTIL::renderImage(frame);
        UTIL::displayResult(frame, true);
    }
    return 0;
}

/* Define functions we'll use */
double sphere(vec3 p, double radius){
    return p.length() - radius;
}

double map(vec3 p){
    return sphere(p, 3.0);
}

vec3 getNormal(vec3 p){
    double _delta = 0.001;
    double deltaX = map(p+vec3(_delta, 0.0, 0.0)) - map(p-vec3(_delta, 0.0, 0.0));
    double deltaY = map(p+vec3(0.0, _delta, 0.0)) - map(p-vec3(0.0, _delta, 0.0));
    double deltaZ = map(p+vec3(0.0, 0.0, _delta)) - map(p-vec3(0.0, 0.0, _delta));
    return vec3(deltaX, deltaY, deltaZ).normalize();
}

float trace(vec3 origin, vec3 direction, vec3& p){
    double totalDistanceTraveled = 0.0;
    for(int i=0; i<32; ++i){
        p = origin + direction*totalDistanceTraveled;
        double distanceFromPointOnRayToClosestObjectInScene = map( p );
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


vec3 calculateLighting(vec3 pointOnSurface, vec3 surfaceNormal, vec3 lightPosition, vec3 cameraPosition){
    vec3 fromPointToLight = (lightPosition - pointOnSurface).normalize();
    /* ^ is short for dot product*/
    double diffuseStrength = e_glsl::clamp(surfaceNormal^fromPointToLight, 0.0, 1.0 );
    
    vec3 diffuseColor = vec3(0.0, 255.0, 0.0)*diffuseStrength;
    vec3 reflectedLightVector = ( e_glsl::reflect( vec3(0.0, 0.0, 0.0)-fromPointToLight, surfaceNormal ) ).normalize();
    
    vec3 fromPointToCamera = ( cameraPosition - pointOnSurface ).normalize();
    double specularStrength = pow( e_glsl::clamp( reflectedLightVector^fromPointToCamera, 0.0, 1.0 ), 10.0 );
    
    specularStrength = min( diffuseStrength, specularStrength );
    vec3 specularColor = vec3( 255.0, 255.0, 255.0 )*specularStrength;
    
    vec3 finalColor = diffuseColor + specularColor;
    
    return finalColor;
}

/**** This function takes care of each pixel rendering */
vec3 renderXY(vec2 gl_FragCoord){
    /* gl_FragCoord are current coordinates */
    /* uv are our screen coordinates        */
    vec2 uv = (gl_FragCoord/resolution)*2.0 - vec2(1.0, 1.0);
    uv._x *= _ratio;
    
    vec3 cameraDirection = vec3(uv._x, uv._y, 1.0).normalize();
    
    vec3 pointOnSurface(0.0, 0.0, 0.0);
    double distanceToClosestPointInScene = trace(cameraPosition, cameraDirection, pointOnSurface);
    
    vec3 finalColor = vec3(0.0, 0.0, 0.0);
    
    if( distanceToClosestPointInScene>0.0 ){
        vec3 surfaceNormal = getNormal(pointOnSurface);
        finalColor = calculateLighting(pointOnSurface, surfaceNormal, lightPosition, cameraPosition);
    }
    
    return finalColor;
}


// to compile use 'g++ main.cpp -std=c++11 -o `pkg-config opencv --cflags --libs` raymarching'
//./raymarching | ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -i - -f mpegts -preset veryslow -vcodec libx264 udp://localhost:5000
// Use VLC to check results
// CTRL+N   and then    udp://@:5000
