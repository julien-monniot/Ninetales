#include "printer_config.h"

#include <iostream>

#ifdef DEBUG
#define DEBUGERR(err) \
    std::cerr << STYLE_ERR_T << "[Debug]: " \
    << STYLE_ERR << err \
    << std::endl << STYLE_DEFAULT;
#define DEBUGWARN(warn) \
    std::cerr << STYLE_WARN_T << "[Debug]: " \
    << STYLE_WARN << warn \
    << std::endl << STYLE_DEFAULT;
#define DEBUGINFO(info) \
    std::cout << STYLE_INFO_T << "[Debug]: " \
    << STYLE_INFO << info \
    << std::endl << STYLE_DEFAULT;
#define DEBUGTRACE(flux) \
    std::cout << flux;
#else
#define DEBUGERR(err)
#define DEBUGWARN(warn)
#define DEBUGINFO(info)
#define DEBUGTRACE(flux)
#endif
