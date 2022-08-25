//
//
//
#include <argparse.h>

ArgumentParser::ArgumentParser() = default;

ArgumentParser::~ArgumentParser() = default;

void ArgumentParser::addArgument(std::string longname, char shortname, std::string const& description) {
    arguments.emplace_back(longname, shortname, OptArgType::kNone, description);
}

void ArgumentParser::addArgument(std::string longname, char shortname, OptArgType type, std::string const& description) {
    arguments.emplace_back(longname, shortname, type, description);
}

void ArgumentParser::addArgument(std::string longname, std::string const& description) {
    arguments.emplace_back(longname, std::nullopt, OptArgType::kNone, description);
}

void ArgumentParser::addArgument(std::string longname, OptArgType type, std::string const& description) {
    arguments.emplace_back(longname, std::nullopt, type, description);
}

void ArgumentParser::addArgument(char shortname, std::string const& description) {
    arguments.emplace_back(std::nullopt, shortname, OptArgType::kNone, description);
}

void ArgumentParser::addArgument(char shortname, OptArgType type, std::string const& description) {
    arguments.emplace_back(std::nullopt, shortname, type, description);
}

std::map<std::string, std::string, std::less<>> ArgumentParser::parse(int argc, char* argv[]) const {
    // argvをvectorに変換して、parse(std::vector)を呼び出す
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }
    return parse(args);
}

std::map<std::string, std::string, std::less<>> ArgumentParser::parse(const std::vector<std::string>& args) const {
    /* パースのメイン部分 */
}

std::string ArgumentParser::getUsage() const {
    return "";
}
