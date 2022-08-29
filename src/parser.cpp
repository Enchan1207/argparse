/**
 * @file parser.cpp
 * @brief パース処理
 */
#include <argparse.h>

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace argparse {

void ArgumentParser::add(const Option &option) {
    // 空白を含まない
    assert(option.name.find(" ") == std::string::npos);

    // 先頭にハイフンがこない (nameにハイフンは必要ない)
    assert(option.name.find("-") != 0);

    std::for_each(options.begin(), options.end(), [&](const Option &opt) {
        assert(opt.name != option.name);

        // ショートオプションを受け入れ可能な場合、
        // 頭文字は重複してはならない
        if (option.nametype != OptNameType::Long) {
            assert(opt.name[0] != option.name[0]);
        }
    });

    options.push_back(option);
}

void ArgumentParser::add(const Operand &operand) {
    // オペランドの最後の型が std::vector<std::string>のとき、
    // 新たに追加することはできない
    if (!operands.empty()) {
        assert(!std::holds_alternative<std::vector<std::string>>(operands.back().value.get()));
    }

    std::for_each(operands.begin(), operands.end(), [&](const Operand &opr) {
        assert(opr.name != operand.name);
    });

    operands.push_back(operand);
}

int ArgumentParser::isOptionRequiresArgument(const Option &option) const {
    if (std::holds_alternative<std::string>(option.value.get())) {
        return required_argument;
    } else if (std::holds_alternative<std::optional<std::string>>(option.value.get())) {
        return optional_argument;
    }
    return no_argument;
}

std::optional<struct option> ArgumentParser::createOptionStruct(const Option &option) const {
    if (option.nametype == OptNameType::Short) {
        return std::nullopt;
    }

    struct option opt;

    // name: そのまま
    opt.name = option.name.c_str();

    // has_arg: valueの型による
    opt.has_arg = isOptionRequiresArgument(option);

    // flag: フラグとして扱うと面倒なのでnull
    opt.flag = nullptr;

    // val: nameの一文字目
    opt.val = option.name[0];

    return opt;
}

std::string ArgumentParser::createOptString() const {
    std::string result = "";
    std::for_each(options.begin(), options.end(), [&](const Option &option) {
        if (option.nametype == OptNameType::Long) {
            return;
        }
        std::string optchars = option.name.substr(0, 1);
        if (isOptionRequiresArgument(option) == required_argument) {
            optchars += ":";
        } else if (isOptionRequiresArgument(option) == optional_argument) {
            optchars += "::";
        }
        result += optchars;
    });

    return result;
}

void ArgumentParser::parse(const int argc, char *const *argv) {
    // ショートオプション文字列を作成
    std::string optstring = createOptString();
    auto c_optstring = std::make_unique<char[]>(optstring.length() + 1);
    std::strcpy(c_optstring.get(), optstring.c_str());

    // ロングオプションはまずvectorでまとめて
    auto long_options = std::vector<struct option>();
    std::for_each(options.begin(), options.end(), [&](const Option &option) {
        auto optstruct = createOptionStruct(option);
        if (!optstruct.has_value()) {
            return;
        }
        long_options.push_back(optstruct.value());
    });

    // option[]に変換する
    size_t longoptSize = long_options.size();
    auto optionStructs = std::make_unique<struct option[]>(longoptSize + 1);
    for (auto i = 0; i < longoptSize; i++) {
        optionStructs[i] = long_options[i];
    }

    // 最後にterminatorを入れる
    struct option terminator {
        nullptr, 0, nullptr, 0
    };
    optionStructs[longoptSize] = terminator;

    // getopt!
    int longIndex = 0;
    int result = getopt_long(argc, argv, c_optstring.get(), optionStructs.get(), &longIndex);
    while (result != -1) {
        //
        // TODO: パースのメイン処理
        //

        result = getopt_long(argc, argv, c_optstring.get(), optionStructs.get(), &longIndex);
    }
}

}  // namespace argparse
