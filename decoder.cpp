#include "decoder.h"
#include "opencv2/opencv.hpp"

Decoder::Decoder(const std::string& file, Frames& frames, std::function<void(const std::string&)>  print)
    : _file(file)
    , _frames(frames)
    , _print(print)
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
    unsigned cnt(0);
    while (true)
    {
        try
        {
            cv::Mat mat;
            cap >> mat;
            if (mat.empty())                
                break;        
            _frames.put(std::move(mat));
            _print("Decoder put its "+std::to_string(++cnt)+" frame");
        } 
        catch (std::exception& e)
        {
            std::cerr << "An error occurred: "  << e.what()  << std::endl;
        }
        catch (...)
        {
            std::cerr << "An undefined error occurred" << std::endl;            
        }        
    }
    
    cap.release();    
    _print("The decoder has just finished its job");
}
