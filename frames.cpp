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
    //std::cerr << "before put frames: " << _queue.size() << std::endl;
    _queue.emplace_back(std::move(mat));
    //std::cerr << "after put frames: " << _queue.size() << std::endl;
}

cv::Mat Frames::get()
{
    std::lock_guard<std::mutex> lock(_m);    
    if (_queue.empty())
        return std::move(cv::Mat());//empty 
    cv::Mat mat;
    std::swap(_queue.front(), mat);
    //std::cout << " B: " << mat.empty();    
    //std::cerr << "before get frames: " << _queue.size() << std::endl;
    _queue.pop_front();
    //std::cerr << "after get frames: " << _queue.size() << std::endl;
    //std::cout << " A: " << mat.empty();
    return std::move(mat);
}

