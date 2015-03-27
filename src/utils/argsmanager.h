#ifndef ARGS_MANAGER_H
#define ARGS_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <boost/program_options.hpp>

// ================================ ERROR

extern const std::string OPTION_ERROR_MESSAGE;
extern const std::string OPTION_ERROR_FILE;
extern const std::string OPTION_ERROR_SEPARATOR;

// ================================ HELP MESSAGE

extern const std::string OPTION_SHORT_TEXT;
extern const std::string OPTION_USAGE_TEXT;

// ================================ STYLE

extern const std::string STYLE_DEFAULT; // Default: white
extern const std::string STYLE_ERROR; // Red
extern const std::string STYLE_IMPORTANT; // White Bold

namespace po = boost::program_options;

class ArgsManager
{
    public:
        ArgsManager(int argc, const char* argv[]);
        virtual ~ArgsManager();
        po::variable_value operator[] (std::string option);
        po::variables_map::size_type count(std::string option);
        friend std::ostream& operator<< (std::ostream& out, const ArgsManager& am);
        bool isError();
        
    protected:
    
    private:
        void manageError(std::string what);
    
        po::options_description desc;
        po::variables_map vm;
        bool error;
        std::string filePath;
};

#endif // ARGS_MANAGER_H
