#ifndef FRAMES_H
#define FRAMES_H

#include <mutex>
#include <opencv2/opencv.hpp>

class Frames {
public:
    Frames();    
    ~Frames();
    
    void put(cv::Mat&& mat);
    cv::Mat get();
private:
    std::deque<cv::Mat> _queue;
    std::mutex _m;
};

#endif /* FRAMES_H */

