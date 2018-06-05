#ifndef UTIL_HPP
#define UTIL_HPP

#include <chrono>
#include <thread>
#include <iostream>

#include <opencv2/imgproc.hpp>
#include "vecs.hpp"

vec3 renderXY(vec2 gl_FragCoord);

namespace UTIL{
    
    void displayResult(cv::Mat& frame){
        for (size_t i = 0; i < frame.dataend - frame.datastart; i++) 
            std::cout << frame.data[i];
        std::this_thread::sleep_for(std::chrono::microseconds(30));
    }
 
    void renderImage(Mat& frame){
        uint8_t* pixelPtr = (uint8_t*)frame.data;
        int cn = frame.channels();

        for(int y=0; y<frame.rows; y++)
            for(int x=0; x<frame.cols; x++)
            {
                vec2 gl_coord(x,y);
                vec3 result = renderXY(gl_coord);
                pixelPtr[y*frame.cols*cn + x*cn + 0] = result._z; // R
                pixelPtr[y*frame.cols*cn + x*cn + 1] = result._y; // G
                pixelPtr[y*frame.cols*cn + x*cn + 2] = result._x; // B
            }
    }
}


#endif /* UTIL_HPP */

