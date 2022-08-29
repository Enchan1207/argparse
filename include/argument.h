/**
 * @file argument.h
 * @brief 実行引数、オプション、オペランド
 */

#ifndef ARGPARSE_ARGUMENT_H
#define ARGPARSE_ARGUMENT_H

#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace argparse {

class Argument {
   public:
    const std::string name;
    const std::string description;

    Argument(const std::string &name, const std::string &description) : name(name), description(description){};
    ~Argument() = default;
};

enum class OptNameType {
    Short,
    Long,
    ShortAndLong
};

using OptionValue = std::variant<
    std::string,
    std::optional<std::string>,
    bool>;

class Option final : public Argument {
   public:
    const OptNameType nametype;
    const std::reference_wrapper<OptionValue> value;

    Option(const std::string &name, const std::string &description, OptNameType nametype, OptionValue &value) : Argument(name, description), nametype(nametype), value(value){};
    ~Option() = default;
};

using OperandValue = std::variant<
    std::string,
    std::optional<std::string>,
    std::vector<std::string>,
    std::optional<std::vector<std::string>>>;

class Operand final : public Argument {
   public:
    const std::reference_wrapper<OperandValue> value;

    Operand(const std::string &name, const std::string &description, OperandValue &value) : Argument(name, description), value(value){};
    ~Operand() = default;
};

}  // namespace argparse

#endif /* ARGPARSE_ARGUMENT_H */
