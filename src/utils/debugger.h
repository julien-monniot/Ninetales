// ---------------------------------------------
//  debugger.h
//
//	Created	 :
//		by 	 : Samuel MAGNAN
//		date : 18/03/2015
//
// ---------------------------------------------

#include "printer.h"

#include <iostream>

extern Printer global_debug_printer;

#ifdef DEBUG
#define DEBUGERR(err) \
    std::cerr << STYLE_ERR_T << "ERR [Debug]:" \
    << STYLE_ERR << err \
    << std::endl << STYLE_DEFAULT;
#define DEBUGWARN(warn) \
    std::cerr << STYLE_WARN_T << "WARN [Debug]:" \
    << STYLE_WARN << warn \
    << std::endl << STYLE_DEFAULT;
#define DEBUGINFO(info) \
    std::cout << STYLE_INFO_T << "INFO [Debug]:" \
    << STYLE_INFO << info \
    << std::endl << STYLE_DEFAULT;
#define TRACE(flux) \
    std::cout << flux;
#else
#define DEBUGERR(err)
#define DEBUGWARN(warn)
#define DEBUGINFO(info)
#define TRACE(flux)
#endif
