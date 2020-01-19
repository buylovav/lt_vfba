#include <unistd.h>

#include "analyzer.h"

Analyzer::Analyzer(const std::string& file, const int N)
    : _file(file) 
    , _finished(false)
{    
    for (int i = 0; i < N; i++)
    {
        _threads.emplace_back(std::thread(&Analyzer::run, this));
        //_threads[i].detach();
    }
    _decoder = std::make_unique<Decoder>(file, _frames);
}

Analyzer::~Analyzer()
{

}

void Analyzer::wait()
{
    _decoder->wait();
    _finished = true;
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

void Analyzer::run()
{
    while (true)
    {
        thread_local int cnt;        
        
        auto frame = _frames.get();
        //std::cout << "empty:" <<frame.empty();
        if (!frame.empty()) //there is a frame
        {
            
            std::stringstream str;
            str << std::hex << std::this_thread::get_id(); 
            print(str.str()+" frames: "+std::to_string(++cnt));
        }
        else //there is not
            if (_finished)
                break;        
    }
}

