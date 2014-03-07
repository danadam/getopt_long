#include "GetOptUsage.h"

#include <ctype.h>
#include <sstream>
#include <vector>

#include "GetOpt.h"

GetOptUsage::GetOptUsage(const GetOpt & go, int leftSpaceSize /*= 2*/, int midSpaceSize /*= 2*/)
{
    const std::string leftSpace(leftSpaceSize, ' ');

    typedef std::vector<std::string> StringList;
    typedef StringList::const_iterator StringListCIt;
    StringList lines;

    unsigned int maxLength = 0;
    for (GetOpt::OptionListCIt it = go.options_.begin(), end = go.options_.end();
            it != end;
            ++it
        )
    {
        std::ostringstream line;
        line << leftSpace;

        const GetOpt::Option & option = *it;
        const bool isLong = !option.name.empty();

        if (option.letter)
            line << "-" << (char)option.letter;
        else
            line << "  ";

        if (isLong)
            line << " --" << option.name;

        if (option.argType == GetOpt::requiredArgument || option.argType == GetOpt::optionalArgument)
        {
            if (option.argType == GetOpt::optionalArgument)
                line << "[";
            if (isLong)
                line << "=";
            line << option.argName;
            if (option.argType == GetOpt::optionalArgument)
                line << "]";
        }

        lines.push_back(line.str());
        if (lines.back().size() > maxLength)
            maxLength = lines.back().size();
    }

    const std::string midSpace(midSpaceSize, ' ');
    GetOpt::OptionListCIt ito = go.options_.begin();
    StringListCIt itl = lines.begin();
    std::ostringstream usage;
    for (; ito != go.options_.end() && itl != lines.end(); ++ito, ++itl)
    {
        if (ito != go.options_.begin())
            usage << '\n';

        const GetOpt::Option & option = *ito;
        const std::string & line = *itl;

        const int alignSize = maxLength - line.size();
        usage << line << std::string(alignSize, ' ') << midSpace << option.description;
    }

    usage_ = usage.str();
}

std::string GetOptUsage::operator()() const
{
    return usage_;
}

