#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <thread>
#include <memory>

#include "decoder.h"

class Analyzer {
public:
    Analyzer(const std::string& file, const int N);    
    virtual ~Analyzer();
        
    void wait();
private:
    void run();
    void measure(cv::Mat&& frame);
    void print(const std::string& text);
    void print(int min, double mean, int max);
    
    const std::string _file;   
    
    std::vector<std::thread> _threads;
    std::unique_ptr<Decoder> _decoder;
    Frames _frames;
    
    std::mutex _pm;
    std::atomic<bool> _finished;
};

#endif /* ANALYZER_H */

