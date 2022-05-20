#include "./Lexer.hpp"

#include <string>
#include <utility>

Lexer::Token Lexer::lex(std::string line) {  // todo: lex the line
  return {Lexer::TokenType::kVert, std::move(line)};
};