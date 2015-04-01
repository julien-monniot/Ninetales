#include "argsmanager.h"
#include <fstream>

const std::string OPTION_ERROR_MESSAGE =    "Error";
const std::string OPTION_ERROR_FILE =       "Cannot open the file : ";
const std::string OPTION_ERROR_SEPARATOR =  " : ";
const std::string OPTION_SHORT_TEXT =       " Ninetales - Another VPN program";
const std::string OPTION_USAGE_TEXT =       "    Usage: ninetales [options]";
const std::string STYLE_DEFAULT =           "\033[0m";
const std::string STYLE_ERROR =             "\033[0;31m";
const std::string STYLE_IMPORTANT =         "\033[0;32m";


ArgsManager::ArgsManager(int argc, const char* argv[]) :
    desc("Allowed options"), vm(NULL), error(false), filePath("")
{
    
    try
    {
        // Set up the description of the options :
        desc.add_options()
            ("init,i", "Enable the initialization operations")
            ("server,s", "Launch a server")
            ("client,c", "Launch a client")
            ("address,a", po::value<std::string>(), "The connection ip")
            ("port,p", po::value<int>(), "The listen/connection port")
            ("no-encryption,n", "Disable the encryption");
        
        // Parse the options :
        po::store(po::command_line_parser(argc, argv).
              options(desc). // set the description
              run(), // Parse the options
              vm); // Variable map
        po::notify(vm);
        
    }
    
    // ERROR : too many "input_file" arguments
    catch (po::too_many_positional_options_error e)
    {
        manageError(e.what());
    }
    
    // ERROR : Unknown option
    catch (po::unknown_option e)
    {
        manageError(e.what());
    }
    
    // ERROR : Required "input_file" argument
    catch (po::required_option e)
    {
        manageError(e.what());
    }
    
    // ERROR : Required "input_file" argument
    catch (po::multiple_occurrences e)
    {
        manageError(e.what());
    }
    
    // ERROR : Default
    catch (po::error e)
    {
        manageError(e.what());
    }
}


ArgsManager::~ArgsManager()
{
}

po::variable_value ArgsManager::operator[] (std::string option)
{
    return vm[option];
}

po::variables_map::size_type ArgsManager::count(std::string option)
{
    return vm.count(option);
}

bool ArgsManager::isError()
{
    return error;
}

void ArgsManager::manageError(std::string what)
{
    std::cerr << STYLE_ERROR;
    std::cerr << OPTION_ERROR_MESSAGE << OPTION_ERROR_SEPARATOR
            << what << std::endl;
    std::cerr << STYLE_DEFAULT;
    error = true;
}


std::ostream& operator<< (std::ostream& out, const ArgsManager& am)
{
    return out << std::endl
    << STYLE_IMPORTANT << OPTION_SHORT_TEXT << STYLE_DEFAULT << std::endl
    << std::endl
    << OPTION_USAGE_TEXT << std::endl
    << std::endl
    << am.desc;
}

