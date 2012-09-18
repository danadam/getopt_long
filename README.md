
Public interface:

```
class GetOpt
{
public:
    class Listener
    {
    public:
        virtual void onShortOption(char letter, const char * arg) = 0;
        virtual void onLongOption(const char * name, const char * arg) = 0;
    };

    bool addOption(const char * name, int letter, int hasArg, const char * argName, const char * description);

    void parse(int argc, char * argv[], Listener * listener);
};
```

```
class GetOptUsage
{
public:
    GetOptUsage(const GetOpt & go, int leftSpaceSize = 2, int midSpaceSize = 2);

    std::string operator()()
}
```


Sample usage:

- implement listener:

```
class Printer : public GetOpt::Listener
{
public:
    Printer(const std::string & usage) : usage_(usage) { }

    virtual void onShortOption(char letter, const char * arg)      { std::cout << letter << std::endl; }
    virtual void onLongOption(const char * name, const char * arg) { std::cout << name   << std::endl; }
private:
    const std::string usage_;
};
```

- add options:

```
GetOpt options;
options.addOption("option", 'o', no_argument, "", "option with long name and letter and no argument");
[...]
```

- prepare usage string:

```
GetOptUsage usage(options);
```

- create our listener

```
Printer printer(usage());
```

- parse options

```
options.parse(argc, argv, &printer);
```
