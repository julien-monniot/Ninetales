// ---------------------------------------------
//  printer_config.h
//
//	Created	 :
//		by 	 : Samuel MAGNAN
//		date : 07/03/2015
//
// ---------------------------------------------

// http://en.wikipedia.org/wiki/ANSI_escape_code
// http://ascii-table.com/ansi-escape-sequences.php

#include "keywords.h"

// ================================ MESSAGES STYLES

const std::string STYLE_DEFAULT = 	"\033[0m";	  	// White
const std::string STYLE_DEFAULT_T =	"\033[1m";	  	// White bold (Title, highlight)
const std::string STYLE_ERROR = 	"\033[0;31m"; 	// Red
const std::string STYLE_ERROR_T = 	"\033[1;31m"; 	// Red bold (Title)
const std::string STYLE_WARN = 		"\033[0;33m"; 	// Yellow
const std::string STYLE_WARN_T =	"\033[1;33m"; 	// Yellow bold (Title)
const std::string STYLE_INFO = 		"\033[0;34m"; 	// Blue	
const std::string STYLE_INFO_T =	"\033[1;34m"; 	// Blue bold (Title)

// ================================ ALL STYLES

const std::string STYLE_WHITE = 	"\033[0m";	  	// White
const std::string STYLE_WHITE_B =	"\033[1m";	  	// White bold	
const std::string STYLE_RED = 		"\033[0;31m"; 	// Red
const std::string STYLE_RED_B = 	"\033[1;31m"; 	// Red bold
const std::string STYLE_GREEN =		"\033[0;32m"; 	// Green
const std::string STYLE_GREEN_B =	"\033[1;32m"; 	// Green bold
const std::string STYLE_YELLOW = 	"\033[0;33m"; 	// Yellow
const std::string STYLE_YELLOW_B =	"\033[1;33m"; 	// Yellow bold
const std::string STYLE_BLUE = 		"\033[0;34m"; 	// Blue
const std::string STYLE_BLUE_B = 	"\033[1;34m"; 	// Blue bold
const std::string STYLE_MAGEN = 	"\033[0;35m"; 	// Magenta
const std::string STYLE_MAGEN_B = 	"\033[1;35m"; 	// Magenta bold
const std::string STYLE_CYAN = 		"\033[0;36m"; 	// Cyan	
const std::string STYLE_CYAN_B =	"\033[1;36m"; 	// Cyan bold

// ================================ KEYWORDS STYLES

const std::string STYLE_VAR = 		STYLE_YELLOW_B;
const std::string STYLE_CONST = 	STYLE_YELLOW_B;
const std::string STYLE_VALUE = 	STYLE_YELLOW_B; // not a real keyword XXX
const std::string STYLE_EQ = 		STYLE_YELLOW;
const std::string STYLE_PLUS = 		STYLE_YELLOW;
const std::string STYLE_MINUS = 	STYLE_YELLOW;
const std::string STYLE_MULT = 		STYLE_YELLOW;
const std::string STYLE_DIV = 		STYLE_YELLOW;
const std::string STYLE_LPAR = 		STYLE_YELLOW;
const std::string STYLE_RPAR = 		STYLE_YELLOW;
const std::string STYLE_ASSIGN = 	STYLE_RED_B;
const std::string STYLE_READ = 		STYLE_RED_B;
const std::string STYLE_WRITE = 	STYLE_RED_B;
const std::string STYLE_END = 		STYLE_WHITE;
const std::string STYLE_SPACE = 	STYLE_CYAN;		// ... just in case we change the spacing character
const std::string STYLE_DOT = 		STYLE_YELLOW;
const std::string STYLE_COMA = 		STYLE_RED;
const std::string STYLE_OTHER = 	STYLE_WHITE;
const std::string STYLE_NUM = 		STYLE_GREEN_B;

// ================================ MESSAGES

const std::string MSG_ERROR = 		"ERROR: ";
const std::string MSG_WARN = 		"WARNING: ";
const std::string MSG_INFO = 		"INFO: ";
const std::string MSG_DEFAULT = 	"";

// ================================ ARG COUNT

const int NB_ARGS_PRINT_STR = 		6;