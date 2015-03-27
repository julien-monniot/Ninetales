
// http://en.wikipedia.org/wiki/ANSI_escape_code
// http://ascii-table.com/ansi-escape-sequences.php


// ================================ MESSAGES STYLES

const std::string STYLE_DEFAULT =   "\033[0m";      // White
const std::string STYLE_DEFAULT_T = "\033[1m";      // White bold (Title, highlight)
const std::string STYLE_ERR =       "\033[0;31m";   // Red
const std::string STYLE_ERR_T =     "\033[1;31m";   // Red bold (Title)
const std::string STYLE_WARN =      "\033[0;33m";   // Yellow
const std::string STYLE_WARN_T =    "\033[1;33m";   // Yellow bold (Title)
const std::string STYLE_INFO =      "\033[0;34m";   // Blue 
const std::string STYLE_INFO_T =    "\033[1;34m";   // Blue bold (Title)

// ================================ ALL STYLES

const std::string STYLE_WHITE =     "\033[0m";      // White
const std::string STYLE_WHITE_B =   "\033[1m";      // White bold   
const std::string STYLE_RED =       "\033[0;31m";   // Red
const std::string STYLE_RED_B =     "\033[1;31m";   // Red bold
const std::string STYLE_GREEN =     "\033[0;32m";   // Green
const std::string STYLE_GREEN_B =   "\033[1;32m";   // Green bold
const std::string STYLE_YELLOW =    "\033[0;33m";   // Yellow
const std::string STYLE_YELLOW_B =  "\033[1;33m";   // Yellow bold
const std::string STYLE_BLUE =      "\033[0;34m";   // Blue
const std::string STYLE_BLUE_B =    "\033[1;34m";   // Blue bold
const std::string STYLE_MAGEN =     "\033[0;35m";   // Magenta
const std::string STYLE_MAGEN_B =   "\033[1;35m";   // Magenta bold
const std::string STYLE_CYAN =      "\033[0;36m";   // Cyan 
const std::string STYLE_CYAN_B =    "\033[1;36m";   // Cyan bold

// ================================ MESSAGES

const std::string MSG_ERROR =       "ERROR: ";
const std::string MSG_WARN =        "WARNING: ";
const std::string MSG_INFO =        "INFO: ";
const std::string MSG_DEFAULT =     "";
