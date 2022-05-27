#include "source/parsing/obj_wavefront/Lexer.hpp"

#include <iostream>

template <typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

int main(void) {
  std::cout << "lexing result:" << as_integer(Lexer::lex(std::string()).first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("").first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("bruh").first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("ffff").first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("vr sss").first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("a").first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("vt").first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("\t  \nvn vn vn").first) << std::endl;
  std::cout << "lexing result:" << as_integer(Lexer::lex("f 1 2 3").first) << std::endl;
  std::cout << "lexing result:"
            << as_integer(Lexer::lex("  v wrewa b 3 a 2 uyhfs duigfy4b uwhbf h").first)
            << std::endl;
}