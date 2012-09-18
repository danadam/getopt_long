#include "GetOptUsage.h"

#include <ctype.h>
#include <sstream>
#include <vector>

#include "GetOpt.h"

GetOptUsage::GetOptUsage(const GetOpt & go, int leftSpaceSize /*= 2*/, int midSpaceSize /*= 2*/)
{
    const std::string leftSpace(leftSpaceSize, ' ');

    typedef std::vector<std::string> StringList;
    typedef StringList::iterator StringListIt;
    typedef StringList::const_iterator StringListCIt;
    StringList lines;

    unsigned int maxLength = 0;
    GetOpt::OptionListCIt ito = go.options_.begin();
    for (; ito != go.options_.end(); ++ito)
    {
        std::ostringstream line;
        line << leftSpace;

        const GetOpt::Option & option = *ito;
        const bool isLong = !option.name.empty();

        if (option.letter)
            line << "-" << (char)option.letter;
        else
            line << "  ";

        if (isLong)
            line << " --" << option.name;

        if (option.hasArg == required_argument || option.hasArg == optional_argument)
        {
            if (option.hasArg == optional_argument)
                line << "[";
            if (isLong)
                line << "=";
            line << option.argName;
            if (option.hasArg == optional_argument)
                line << "]";
        }

        lines.push_back(line.str());
        if (lines.back().size() > maxLength)
            maxLength = lines.back().size();
    }

    const std::string midSpace(midSpaceSize, ' ');
    ito = go.options_.begin();
    StringListIt itl = lines.begin();
    std::ostringstream usage;
    for (; ito != go.options_.end() && itl != lines.end(); ++ito, ++itl)
    {
        if (ito != go.options_.begin())
            usage << '\n';

        const GetOpt::Option & option = *ito;
        std::string & line = *itl;

        const int alignSize = maxLength - line.size();
        usage << line << std::string(alignSize, ' ') << midSpace << option.description;
    }

    usage_ = usage.str();
}

