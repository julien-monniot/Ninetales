// ---------------------------------------------
//  printer.cpp
//
//	Created	 :
//		by 	 : Samuel MAGNAN
//		date : 04/03/2015
//
// ---------------------------------------------

#include <iostream>
#include <vector>
#include <iterator>

#include "printer.h"
#include "printer_config.h"
#include "utils.h"

using std::cout;
using std::endl;
using Utils::split;

// ==================================================== PUBLIC

// Printer constructor
Printer::Printer() 
{

}

Printer::~Printer()
{

}

void Printer::print(std::ostream& out,std::string str)
{
	// TODO to change? will depens on an external file and will not be hardcoded?
	std::vector<std::string> lines;
	std::vector<std::string> metawords;
	std::vector<std::string> words;
	split(str,lines,'\n',false); // split text into lines
	for(std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
		metawords.clear();
	    split(*it,metawords,' ',false);	// split lines in words by spaces (delete spaces)
	    for(std::vector<std::string>::iterator it2 = metawords.begin(); it2 != metawords.end(); ++it2) {
	    	words.clear();
	    	split(*it2,words,"+-*/=(),;:"); // split at special chars and keep them
	    	for(std::vector<std::string>::iterator it3 = words.begin(); it3 != words.end(); ++it3) {
	    		if(!(*it3).empty())
	    			out << selectStyle(*it3) <<*it3 ;
	    	}
	    	out << ' ';
	    }	
	    if (it != lines.begin())	// do not jump if one line only with no end of line char
	    	out << endl;    
	}	
}

void Printer::print(std::ostream& out,double value)
{
	out << STYLE_NUM << value << ' ';
}

void Printer::printerr(std::string error, std::string desc)
{
	printString(NB_ARGS_PRINT_STR,STYLE_ERROR_T.c_str(),MSG_ERROR.c_str(),STYLE_ERROR_T.c_str(),error.c_str(),STYLE_ERROR.c_str(),desc.c_str());
	cout << STYLE_DEFAULT << endl;
}

void Printer::printwarn(std::string warn, std::string desc)
{
	printString(NB_ARGS_PRINT_STR,STYLE_WARN_T.c_str(),MSG_WARN.c_str(),STYLE_WARN_T.c_str(),warn.c_str(),STYLE_WARN.c_str(),desc.c_str());
	cout << STYLE_DEFAULT << endl;
}

void Printer::printinfo(std::string info, std::string desc)
{
	printString(NB_ARGS_PRINT_STR,STYLE_INFO_T.c_str(),MSG_INFO.c_str(),STYLE_INFO_T.c_str(),info.c_str(),STYLE_INFO.c_str(),desc.c_str());
	cout << STYLE_DEFAULT << endl;
}
void Printer::print(std::string def, std::string desc)
{
	printString(NB_ARGS_PRINT_STR,STYLE_DEFAULT_T.c_str(),MSG_DEFAULT.c_str(),STYLE_DEFAULT_T.c_str(),def.c_str(),STYLE_DEFAULT.c_str(),desc.c_str());
	cout << STYLE_DEFAULT << endl;
}

void Printer::endline()
{
	cout << STYLE_END << ";" << STYLE_DEFAULT <<  endl;
}

// ==================================================== PRIVATE

void Printer::printString(int count, ...)
{
	va_list ap;
    int j;
    va_start(ap, count);
    for(j = 0; j < count; j++)
        cout << va_arg(ap, char*); 
    va_end(ap);
}

