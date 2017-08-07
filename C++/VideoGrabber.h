#ifndef VIDEO_GRABBER_H
#define VIDEO_GRABBER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <thread>
#include "UserControl.h"

class VideoGrabber
{
    public:
    
    /** Constructor needs a reference to a UserControl for the exit condition.
     *
     */
    VideoGrabber(UserControl& userControl);
    ~VideoGrabber();
    
    /** Initialize structures.
     *
     * @return True if succeeded.
     *
     * @todo To be filled.
     */
    bool initialize();
    
    /** Start streaming video feed.
     *
     * @todo add configuration structure or specialize.
     * Need to differentiate between PiCam or Webcam.
     */
    std::thread start();
    
    /** Stream Webcam video feed continuously.
     *
     * @note This function does not appear to work when called in a thread.
     */
    void streamWebcam();
    
    UserControl& mUserControl; /**< Reference to a UserControl instance */
    
};

#endif
