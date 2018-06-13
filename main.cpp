/* Inspired by the tutorial @ http://xdpixel.com/ray-marching-101-part-2/ */
/* Grgo Mariani                                                                                                                                     *
 *    READ THIS FIRST                                                                                                                               *
 * to compile use 'g++ main.cpp -std=c++11 -o `pkg-config opencv --cflags --libs` raymarching'                                                      *
 * ./raymarching | ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -i - -f mpegts -preset veryslow -vcodec libx264 udp://localhost:5000  *
 * Use VLC to check results    (CTRL+N   and then    udp://@:5000)                                                                                  */

#include <cstdlib>
#include <opencv2/imgproc.hpp>

#include "libs/globals.hpp"
#include "libs/vecs.hpp"
#include "libs/util.hpp"

#include "render.hpp"

using namespace std;
using namespace cv;

const vec resolution_2d = vec(320, 240);

const int MAX_STEPS=32;
const double MAX_DISTANCE=10000.0;
const double EPSILON = 0.001;

double _ratio=1.0;


/**** This is our program Start . No need to edit this main function */
int main(int argc, char** argv) {
    Mat frame(resolution_2d._y, resolution_2d._x, CV_8UC3, Scalar(0, 0, 0));
    _ratio = resolution_2d._x / resolution_2d._y;
    while(true){
        UTIL::renderImage(frame);
        UTIL::displayResult(frame, true);
    }
    return 0;
}

/**** renderXY takes care of each pixel rendering                     */
/*    WRITE YOUR CODE HERE                                            */
/*    currently it calls the methods defined in render.hpp            */
vec renderXY(vec gl_FragCoord_2d){
    // gl_FragCoord_2d are current coordinates 
    // uv_2d are our modified screen coordinates        
    vec uv_2d = (gl_FragCoord_2d/resolution_2d)*2.0 - vec(1.0, 1.0);
    uv_2d._x *= _ratio;
    
    static vec cameraPosition_3d(0.0, 0.0, -10.0);
    static vec lightPosition_3d(3.0, 4.5, -10.0);
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

