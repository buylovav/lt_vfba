#include <cstdlib>

#include "frames.h"
#include "analyzer.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: lt_vfba <video_file> [N threads]" << std::endl;
        return 1;
    }
    auto NDef(3);//default
    auto N(NDef);
    if (argc > 2)
    {        
        try{
            N = atoi(argv[2]);
        }
        catch(...)
        { 
            N = NDef;
        }
        
        if (N <= 0||(N > NDef && N > std::thread::hardware_concurrency()))
        {
            N = NDef;            
        }        
    }
    std::cout << "Number of threads: " << N << std::endl;
    
    {
        Analyzer analyzer(argv[1], N);
        analyzer.wait();
    }
    std::cout << "Finished." << std::endl;
    return 0;
}

