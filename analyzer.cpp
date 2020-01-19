#include <unistd.h>
#include <iomanip>

#include "analyzer.h"

Analyzer::Analyzer(const std::string& file, const int N)
    : _file(file) 
    , _finished(false)
{    
    for (int i = 0; i < N; i++)
    {
        _threads.emplace_back(std::thread(&Analyzer::run, this));        
    }
    _decoder = std::make_unique<Decoder>(file, _frames, 
                        std::bind(static_cast<void(Analyzer::*)(const std::string&)>(&Analyzer::print), this, std::placeholders::_1));
}

Analyzer::~Analyzer()
{

}

void Analyzer::wait()
{
    _decoder->wait();//waiting decoder to finish its job
    _finished = true;//threads may break the loop if the queue is empty
    for (auto& th : _threads)
    {
        th.join();
    }     
}

void Analyzer::print(const std::string& text)
{
    std::lock_guard<std::mutex> lock(_pm);
    std::cout << text << std::endl;
}

void Analyzer::print(int min, double mean, int max)
{
    std::lock_guard<std::mutex> lock(_pm);   
    std::cout << std::setiosflags (std::ios::showpoint | std::ios::fixed | std::ios::left);
    static unsigned cnt (0);
    std::cout << " min: " << std::setw(3) <<  min 
              << " mean: " << std::setprecision(2) << std::setw(6) << mean 
              << " max: " << std::setw(3) << max 
              << " frames processed: " << std:: setw(6) << ++cnt
              << std::endl;
}

void Analyzer::run()
{
    while (true)
    {
        thread_local int cnt;        
        
        auto frame = _frames.get();        
        if (!frame.empty()) //there is a frame
        {
            measure(std::move(frame));
        }
        else //there is not
            if (_finished)
                break;        
    }
    print("A thread has just finished its job");
}

void Analyzer::measure(cv::Mat&& frame)
{
    cv::Mat gray;
    cv::cvtColor(frame, gray, CV_RGB2GRAY);
    
    auto mean = cv::mean(gray);
    double min, max;
    cv::minMaxIdx(gray, &min, &max);
    
    print(static_cast<int>(min), mean[0], static_cast<int>(max));
}

