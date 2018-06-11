#ifndef UTIL_HPP
#define UTIL_HPP

#ifdef WITH_OPENMP
#include <omp.h>
#endif

#include <chrono>
#include <thread>
#include <iostream>

#include <opencv2/imgproc.hpp>
#include "vecs.hpp"

vec renderXY(vec gl_FragCoord_2d);

namespace UTIL{
    
    void displayResult(cv::Mat& frame, bool SHOW_FRAME=false){
        static int num_frame=0;
        if (SHOW_FRAME){
            std::ostringstream ss;
            ss << "FRAME: " << num_frame ;
            num_frame++;
            cv::putText(frame, ss.str(), Point(20,20), 0, 0.5, Scalar(0,0,255));
        }
        for (size_t i = 0; i < (size_t)(frame.dataend - frame.datastart); i++) 
            std::cout << frame.data[i];
        std::this_thread::sleep_for(std::chrono::microseconds(30));
    }
 
    void renderImage(Mat& frame, bool FLIP_Y=true){
        uint8_t* pixelPtr = (uint8_t*)frame.data;
        int cn = frame.channels();
        
        
        #ifdef WITH_OPENMP
        #pragma omp parallel for
        #endif
        for(int y=0; y<frame.rows; y++)
            for(int x=0; x<frame.cols; x++)
            {
                int _y = y;
                if(FLIP_Y) _y=frame.rows-y-1;
                vec gl_coord_2d(x, _y);
                vec result = renderXY(gl_coord_2d);
                pixelPtr[y*frame.cols*cn + x*cn + 0] = result._z; // B
                pixelPtr[y*frame.cols*cn + x*cn + 1] = result._y; // G
                pixelPtr[y*frame.cols*cn + x*cn + 2] = result._x; // R
            }
        
    }
}


#endif /* UTIL_HPP */
