/**
 * @file parser.cpp
 * @brief パース処理
 */
#include <argparse.h>

#include <cassert>
#include <string>

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

void ArgumentParser::parse(const int argc, char const *argv[]) {
    // TODO: implement
}

}  // namespace argparse
