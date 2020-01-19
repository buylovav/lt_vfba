#include "decoder.h"
#include "opencv2/opencv.hpp"

Decoder::Decoder(const std::string& file, Frames& frames)
    : _file(file)
    , _frames(frames)    
{
    _res = std::async(&Decoder::run, this);
}

Decoder::~Decoder()
{    
}

void Decoder::wait()
{
    _res.get();
}

void Decoder::run()
{
    cv::VideoCapture cap(_file);
    if (!cap.isOpened())
    {
        std::cerr << "File \"" << _file << "\" couldn't be opened" << std::endl;
        return;
    }
    
    while (true)
    {
        cv::Mat mat;
        cap >> mat;
        if (mat.empty())
            break;        
        _frames.put(std::move(mat));        
    }
    
    cap.release();    
}
