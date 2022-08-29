//
//
//
#include <argparse.h>
#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

extern "C" {
#include <tinystr.h>
}
#define ADD_ARGUMENT(list, arg) add_string_list(list, arg)

using namespace argparse;

/**
 * @brief パーサにvectorを矯正的に押し付ける
 *
 * @param parser パーサ
 * @param args 引数
 */
void parseWrapper(ArgumentParser parser, std::vector<std::string> args) {
    size_t size = args.size();
    auto args_ptr = std::make_unique<std::unique_ptr<char[]>[]>(size);
    for (auto i = 0; i < size; i++) {
        args_ptr[i] = std::make_unique<char[]>(args[i].size() + 1);
        std::strcpy(args_ptr[i].get(), args[i].c_str());
    }
    void const *args_ptr_c = args_ptr.get();
    parser.parse(static_cast<int>(size), static_cast<char *const *>(args_ptr_c));
}

TEST(Argparse_Test, testParseArgs) {
    auto parser = ArgumentParser();

    OptionValue isHelpRequired = false;
    OptionValue isVerboseEnabled = false;
    OptionValue isVersionInfoRequired = false;

    parser.add(Option("help", "show this help and exit", OptNameType::Long, isHelpRequired));
    parser.add(Option("verbose", "enable verbose output", OptNameType::ShortAndLong, isVerboseEnabled));
    parser.add(Option("version", "show version information and exit", OptNameType::Long, isVersionInfoRequired));

    std::vector<std::string> args = {
        "(progname)",
        "--help",
        "-v"};
    parseWrapper(parser, args);
}
