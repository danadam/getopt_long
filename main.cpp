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
    go.addOption("both", 'b', no_argument, "", "both without arg");
    go.addOption("bothreq", 'c', required_argument, "", "both with required arg");
    go.addOption("bothopt", 'd', optional_argument, "", "both with optional arg");
    go.addOption("", 's', no_argument, "", "only short without arg");
    go.addOption("", 't', required_argument, "", "only short with required arg");
    go.addOption("", 'u', optional_argument, "", "only short with optional arg");
    go.addOption("long", 0, no_argument, "", "only long without arg");
    go.addOption("longreq", 0, required_argument, "", "only long with required arg");
    go.addOption("longopt", 0, optional_argument, "", "only long with optional arg");

    // prepare usage string
    GetOptUsage u(go);

    // create listener
    Printer p(u());

    // parse options
    go.parse(argc, argv, &p);

    TRACE("END");
    return 0;
}
