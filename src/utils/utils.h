#ifndef UTILS_H
#define UTILS_H

#define TRACE(flux) \
    std::cout << flux << std::endl;
#define DISPLAY(header, flux) \
    std::cout << "\033[1m[" << header << "]\033[0m " << flux << std::endl;

namespace Utils
{
    
}

#endif
