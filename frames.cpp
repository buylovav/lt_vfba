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

std::pair<bool, cv::Mat> Frames::get(bool finished)
{
    std::lock_guard<std::mutex> lock(_m);    
    if (_queue.empty())
        return std::make_pair(finished, cv::Mat());//empty 
    cv::Mat mat = std::move(_queue.front());    
    _queue.pop_front();    
    return std::make_pair(finished, std::move(mat));
}

