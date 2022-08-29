/**
 * @file argparse.h
 * @brief メインヘッダ
 */

#ifndef ARGPARSE_ARGPARSE_H
#define ARGPARSE_ARGPARSE_H

#include <vector>

extern "C" {
#include <getopt.h>
}

#include "argument.h"

namespace argparse {

class ArgumentParser final {
   private:
    std::vector<Option> options;
    std::vector<Operand> operands;

    int isOptionRequiresArgument(const Option &option) const;
    std::optional<struct option> createOptionStruct(const Option &option) const;
    std::string createOptString() const;

   public:
    ArgumentParser() = default;
    ~ArgumentParser() = default;

    void add(const Option &option);
    void add(const Operand &operand);

    void parse(const int argc, char *const *argv);
};

}  // namespace argparse

#endif /* ARGPARSE_ARGPARSE_H */
