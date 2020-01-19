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
        std::stringstream str;
        str << argv[2];
        str >> N;
        if (N <= 0 )
            N = NDef;
    }
    
    {
        Analyzer analyzer(argv[1], N);
        analyzer.wait();
    }
    std::cout << "Finished" << std::endl;
    return 0;
}

