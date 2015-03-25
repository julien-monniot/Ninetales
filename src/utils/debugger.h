// ---------------------------------------------
//  debugger.h
//
//	Created	 :
//		by 	 : Samuel MAGNAN
//		date : 18/03/2015
//
// ---------------------------------------------

#include "printer.h"

extern Printer global_debug_printer;

#ifdef DEBUG
#define DEBUGERR(err) global_debug_printer.printerr("[Debug] ",err);
#define DEBUGWARN(warn) global_debug_printer.printwarn("[Debug] ",warn);
#define DEBUGINFO(info) global_debug_printer.printinfo("[Debug] ",info);
#define TRACE(flux) std::cout << flux;
#else
#define DEBUGERR(err)
#define DEBUGWARN(warn)
#define DEBUGINFO(info)
#define TRACE(flux)
#endif
