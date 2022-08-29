//
//
//
#include <argparse.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace argparse;

TEST(Argparse_Test, testConfigureArguments) {
    auto parser = ArgumentParser();

    // 例えば、こんなかんじのオプションを受け取れるようにしたいとする
    OptionValue isHelpRequired = false;
    OptionValue isVerboseEnabled = false;
    OptionValue isVersionInfoRequired = false;

    parser.add(Option("help", "show this help and exit", OptNameType::Long, isHelpRequired));
    parser.add(Option("verbose", "enable verbose output", OptNameType::ShortAndLong, isVerboseEnabled));

    // ハイフンで始める必要はない
    EXPECT_DEATH(parser.add(Option("--option", "I don't want initial hyphens", OptNameType::Long, isHelpRequired)), "");

    // 空白を含んではいけない
    EXPECT_DEATH(parser.add(Option("Space X", "imagine you specify him as 'option'", OptNameType::Long, isHelpRequired)), "");

    // 名前が全く同じオプションを追加することはできない
    EXPECT_DEATH(parser.add(Option("help", "FAKE HELP!", OptNameType::Long, isHelpRequired)), "");

    // ショートオプションを受け入れられるオプション同士の頭文字は一致してはならない
    // ロングしか受け取らないようにすればOK
    EXPECT_DEATH(parser.add(Option("version", "It will conflict with option verbose", OptNameType::ShortAndLong, isVersionInfoRequired)), "");
    parser.add(Option("version", "show version information and exit", OptNameType::Long, isVersionInfoRequired));
}

TEST(Argparse_Test, testConfigureOperands) {
    auto parser = ArgumentParser();

    OperandValue source = std::string();
    OperandValue sources = std::vector<std::string>();

    // オペランドは名前の重複以外はなんでもあり
    parser.add(Operand("source", "medama-yaki ni kakeruto ronsou ni hatten suru yatsu", source));
    EXPECT_DEATH(parser.add(Operand("source", "But actually source is not sauce", source)), "");

    parser.add(Operand("my favorite source", "the name of operand can include spaces", source));

    // ただし、std::vectorが来た後はオペランドは追加できない
    parser.add(Operand("sources", "source file paths to process", sources));
    EXPECT_DEATH(parser.add(Operand("other_source", "for example: soy sauce", source)), "");
}
