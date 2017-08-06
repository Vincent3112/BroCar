#include "VideoGrabber.h"

VideoGrabber::VideoGrabber(UserControl& userControl) :
    mUserControl(userControl)
{
    cv::namedWindow("My Webcam");
}

VideoGrabber::~VideoGrabber(){

}

std::thread VideoGrabber::start(){
    return std::thread([=] { streamWebcam(); });
}

void VideoGrabber::streamWebcam(){
    cv::VideoCapture Camera(0);
    while (mUserControl.mUserData.running){
        cv::Mat OutputImage;
        Camera.read(OutputImage);
        if (OutputImage.rows > 0 && OutputImage.cols > 0){
            cv::imshow("My Webcam", OutputImage);
            cv::waitKey(1);
        } else {
            printf("issue");
        }
    }
}
