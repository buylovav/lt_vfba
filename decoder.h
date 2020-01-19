#ifndef DECODER_H
#define DECODER_H

#include <future>
#include <condition_variable>
#include "frames.h"

class Decoder {
public:        
    Decoder(const std::string& file, Frames& frames, std::function<void(const std::string&)>  print);
    virtual ~Decoder();
    
    void wait();
private:
    const std::string _file;
    Frames& _frames;
    std::function<void(const std::string&)>  _print;
    std::future<void> _res;
    
    void run();    
};

#endif /* DECODER_H */

