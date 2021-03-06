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
    GetOpt::OptionListCIt itOptions = go.options_.begin(), endOptions = go.options_.end();
    StringListCIt itLines = lines.begin(), endLines = lines.end();
    std::ostringstream usage;
    for (; itOptions != endOptions && itLines != endLines; ++itOptions, ++itLines)
    {
        if (itOptions != go.options_.begin())
            usage << '\n';

        const GetOpt::Option & option = *itOptions;
        const std::string & line = *itLines;

        const int alignSize = maxLength - line.size();
        usage << line << std::string(alignSize, ' ') << midSpace << option.description;
    }

    usage_ = usage.str();
}

std::string GetOptUsage::operator()() const
{
    return usage_;
}

