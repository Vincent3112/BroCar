//
//  main.cpp
//  OpenCVWebcam
//
//  Created by Guillaume GRANIE on 11/07/2017.
//  Copyright © 2017 Guillaume GRANIE. All rights reserved.
//

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <thread>
#include <condition_variable>
#include <mutex>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

std::string stop;
std::condition_variable cond_var;
std::mutex m;

void detectUserInput(){
    std::cin >> stop;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    cv::VideoCapture Camera(0);
    
    std::cout << "Press any key to stop." << std::endl;
    
    
    std::thread detect(detectUserInput);
    
    while (stop == ""){
        cv::Mat OutputImage;
        Camera.read(OutputImage);
        if (OutputImage.rows > 0 && OutputImage.cols > 0){
            cv::Mat Canny, Final;
            cv::Canny(OutputImage, Canny, 50, 120);
            std::vector<cv::Vec4i> lines;
            cv::HoughLinesP(Canny, lines, 1, CV_PI/180, 50, 50, 10 );
            for( size_t i = 0; i < lines.size(); i++ )
            {
                cv::Vec4i l = lines[i];
                cv::line(Final, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
            }
            cv::cvtColor(Canny, Final, CV_GRAY2BGR);
            cv::imshow("My Webcam", Final);
            cv::waitKey(1);
        }
    }
    
    detect.join();
    
    return 0;
}
