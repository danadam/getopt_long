#ifndef GetOptUsage_h_GUARD
#define GetOptUsage_h_GUARD

#include <string>

class GetOpt;

/*
 * Generates usage string.
 */
class GetOptUsage
{
public:
    /*
     * Build usage string from GetOpt.
     *
     * leftSpaceSize - left padding of the usage string
     * midSpaceSize - minimal space between options and theirs description
     */
    GetOptUsage(const GetOpt & go, int leftSpaceSize = 2, int midSpaceSize = 2);

    /*
     * Return usage string.
     */
    std::string operator()()
    {
        return usage_;
    }

private:
    std::string usage_;
};

#endif

