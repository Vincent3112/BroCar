/** Main program
 *
 * @detail The main function initiates every threads:
 *          Communication with the arduino board
 *          User input through keyboard
 *          More to come ..
 */

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "UserControl.h"
#include "VideoGrabber.h"

int main(int argc, const char * argv[]) {
    
    UserControl::ControlType c;
    
    UserControl userControl;
    VideoGrabber videoGrabber(userControl);
    
    std::thread userControlThread = userControl.start();
    
    videoGrabber.streamWebcam();
    
    userControlThread.join();
    
    return 0;
}
