#ifndef GetOpt_h_GUARD
#define GetOpt_h_GUARD

#include <string>
#include <vector>

#include <getopt.h>

/*
 * Encapsulates options and parses them.
 */
class GetOpt
{
public:
    /*
     * Interface for listner for parsed options.
     */
    class Listener
    {
    public:
        virtual void onShortOption(char letter, const char * arg) = 0;
        virtual void onLongOption(const char * name, const char * arg) = 0;
    };

    GetOpt();

    // wrapper around values defined in getopt.h
    enum ArgType
    {
        noArgument = no_argument,
        requiredArgument = required_argument,
        optionalArgument = optional_argument
    };

    /*
     * Add new option.
     *
     * name - long name of the option
     * letter - short name of the option
     * argType - indicates if option has an argument
     * argName - argument name if option accepts parameters (--name=argName or -n argName)
     * description - description for usage string
     */
    bool addOption(const std::string & name, int letter, ArgType argType, const std::string & argName, const std::string & description);

    /*
     * Parse options and call listener on every valid option.
     *
     * argc - options counter (standard one, passed to main() function)
     * argv - options array (standard one, passed to main() function)
     * listener - the listener that will be called every time valid option is found
     */
    void parse(int argc, char * argv[], Listener * listener);

    int getNonOptionPos() const;

    const struct option * sysOptions() const;

private:
    friend class GetOptUsage;
    struct Option
    {
        std::string name;
        int letter;
        ArgType argType;
        std::string argName;
        std::string description;
    };

    void finalize() ;

    typedef std::vector<Option> OptionList;
    typedef OptionList::iterator OptionListIt;
    typedef OptionList::const_iterator OptionListCIt;
    OptionList options_;

    typedef std::vector<struct option> SysOptionList;
    SysOptionList sys_options_;

    std::string opt_string_;

    int first_non_option_pos_;
};

#endif

