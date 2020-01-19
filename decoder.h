#ifndef DECODER_H
#define DECODER_H


#include <future>
#include <condition_variable>
#include "frames.h"

class Decoder {
public:
    //Decoder() = delete;
    //Decoder(const Decoder& orig) = delete;
    Decoder(const std::string& file, Frames& frames);
    virtual ~Decoder();
    
    void wait();
private:
    const std::string _file;
    Frames& _frames;
    std::future<void> _res;
    
    void run();    
};

#endif /* DECODER_H */

