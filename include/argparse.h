/**
 * @file argparse.h
 * @brief メインヘッダ
 */

#ifndef ARGPARSE_ARGPARSE_H
#define ARGPARSE_ARGPARSE_H

#include <vector>

#include "argument.h"

namespace argparse {

class ArgumentParser final {
   private:
    std::vector<Option> options;
    std::vector<Operand> operands;

   public:
    ArgumentParser() = default;
    ~ArgumentParser() = default;

    void add(const Option &option);
    void add(const Operand &operand);

    void parse(const int argc, char const *argv[]);
};

}  // namespace argparse

#endif /* ARGPARSE_ARGPARSE_H */
