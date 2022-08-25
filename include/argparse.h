//
//
//

#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

enum class OptArgType {
    kNone,
    kRequired,
    kOptional
};

class Argument {
   private:
    const std::optional<std::string> longname;
    const std::optional<char> shortname;
    const OptArgType optargtype;
    const std::string description;

   public:
    Argument(std::optional<std::string> const& longname, std::optional<char> shortname, OptArgType optargtype, std::string const& description)
        : longname(longname),
          shortname(shortname),
          optargtype(optargtype),
          description(description) {}

    ~Argument();
};

class ArgumentParser {
   private:
    std::vector<Argument> arguments;

   public:
    ArgumentParser();
    explicit ArgumentParser(std::vector<Argument> const& arguments)
        : arguments(arguments) {}
    ~ArgumentParser();

    void addArgument(std::string longname, char shortname, std::string const& description);
    void addArgument(std::string longname, char shortname, OptArgType type, std::string const& description);

    void addArgument(std::string longname, std::string const& description);
    void addArgument(std::string longname, OptArgType type, std::string const& description);

    void addArgument(char shortname, std::string const& description);
    void addArgument(char shortname, OptArgType type, std::string const& description);

    std::map<std::string, std::string, std::less<>> parse(int argc, char* argv[]) const;
    std::map<std::string, std::string, std::less<>> parse(const std::vector<std::string>& args) const;

    std::string getUsage() const;
};
