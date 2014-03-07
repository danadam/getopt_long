#include "MyQtDebug.h"

#include "GetOpt.h"
#include "GetOptUsage.h"

/*
 * Sample implementation of GetOpt::Listener. Just print out detected option.
 */
class Printer : public GetOpt::Listener
{
public:
    Printer(const std::string & usage) : usage_(usage) { }
    virtual void onShortOption(char letter, const char * arg);
    virtual void onLongOption(const char * name, const char * arg);
private:
    const std::string usage_;
};

void Printer::onShortOption(char letter, const char * arg)
{
    TRACE("%1(): letter=%2, arg=%3").arg(__func__).arg(letter).arg(arg == NULL ? "NULL" : arg);
    if (letter == 'h' || letter == '?')
    {
        TRACE("\n%1").arg(usage_.c_str());
    }
}

void Printer::onLongOption(const char * name, const char * arg)
{
    TRACE("%1(): name=%2, arg=%3").arg(__func__).arg(name).arg(arg == NULL ? "NULL" : arg);
}

int main(int argc, char * argv[])
{
    prepareQtDebug();
    TRACE("BEGIN");

    // add options
    GetOpt go;
    go.addOption("both", 'b', GetOpt::noArgument, "", "both without arg");
    go.addOption("bothreq", 'c', GetOpt::requiredArgument, "", "both with required arg");
    go.addOption("bothopt", 'd', GetOpt::optionalArgument, "", "both with optional arg");
    go.addOption("", 's', GetOpt::noArgument, "", "only short without arg");
    go.addOption("", 't', GetOpt::requiredArgument, "", "only short with required arg");
    go.addOption("", 'u', GetOpt::optionalArgument, "", "only short with optional arg");
    go.addOption("long", 0, GetOpt::noArgument, "", "only long without arg");
    go.addOption("longreq", 0, GetOpt::requiredArgument, "", "only long with required arg");
    go.addOption("longopt", 0, GetOpt::optionalArgument, "", "only long with optional arg");

    // prepare usage string
    GetOptUsage u(go);

    // create listener
    Printer p(u());

    // parse options
    go.parse(argc, argv, &p);
    TRACE("First non option: %1").arg(go.getNonOptionPos());

    TRACE("END");
    return 0;
}
