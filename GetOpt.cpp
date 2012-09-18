#include "GetOpt.h"

GetOpt::GetOpt()
{
    struct option sysOption = {
        NULL, false, NULL, 0
    };
    sys_options_.push_back(sysOption);
}

bool GetOpt::addOption(const char * name, int letter, int hasArg, const char * argName, const char * description)
{
    Option option;
    option.name = name;
    option.letter = isalnum(letter) ? letter : 0;
    option.hasArg = hasArg;
    option.argName = argName;
    option.description = description;

    if (option.name.empty() && option.letter == 0)
        return false;

    if (option.argName.empty())
        option.argName = "ARG";

    options_.push_back(option);

    if (option.letter > 0)
    {
        opt_string_ += option.letter;
        if (hasArg == required_argument)
            opt_string_ += ":";
        else if (hasArg == optional_argument)
            opt_string_ += "::";
    }

    struct option sysOption = {
        option.name.c_str(), option.hasArg, NULL, option.letter
    };
    struct option terminator = sys_options_.back();
    sys_options_.back() = sysOption;
    sys_options_.push_back(terminator);

    return true;
}

void GetOpt::parse(int argc, char * argv[], Listener * listener)
{
    if (!listener)
        return;

    int longIndex = 0;
    int rc = 0;
    while ((rc = getopt_long(argc, argv, opt_string_.c_str(), &sys_options_[0], &longIndex)) != -1)
    {
        if (rc == 0)
            listener->onLongOption(sys_options_[longIndex].name, optarg);
        else
            listener->onShortOption(rc, optarg);
    }
}

const struct option * GetOpt::sysOptions() const
{
    return &sys_options_[0];
}

