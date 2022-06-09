#include "source/parsing/obj_wavefront/Parser.hpp"

#include <cassert>
#include <iostream>

#include "source/parsing/obj_wavefront/Lexer.hpp"

using PToken = Parser::Token;
using LToken = Lexer::Token;

template <typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

int main(void) {
  PToken sink;
  const char* error_tests[] = {"",
                               "wrongtoken a a a",
                               "1 wrong token",
                               "f",
                               "v 1. 1 1",
                               "v 1",
                               "vt 22.1 33.2 44.3 55.4",
                               "vn 3. 22.665765",
                               "v a 43.2 32.4"};

  std::cout << "error input test:" << std::endl;
  for (auto& test : error_tests) {
    std::cout << "testing case \"" << test << "\" ... ";
    sink = Parser::parse(Lexer::lex(test));
    assert(sink.type == Lexer::TokenType::kUnknown);
    assert(sink.data == nullptr);
    std::cout << "OK" << std::endl;
  }
}