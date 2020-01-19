#include "frames.h"

Frames::Frames()
{
}

Frames::~Frames()
{
}

void Frames::put(cv::Mat&& mat)
{
    std::lock_guard<std::mutex> lock(_m);    
    _queue.emplace_back(std::move(mat));    
}

cv::Mat Frames::get()
{
    std::lock_guard<std::mutex> lock(_m);    
    if (_queue.empty())
        return std::move(cv::Mat());//empty 
    cv::Mat mat = std::move(_queue.front());    
    _queue.pop_front();    
    return std::move(mat);
}

