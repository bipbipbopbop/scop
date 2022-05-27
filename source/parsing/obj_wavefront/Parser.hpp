#ifndef PARSING_OBJ_WAVEFRONT_PARSER_HPP
#define PARSING_OBJ_WAVEFRONT_PARSER_HPP

#include <type_traits>

#include "./Lexer.hpp"
#include "./data.hpp"

namespace Parser {
struct Token {
  void *data;
  const Lexer::TokenType type = Lexer::TokenType::kUnknown;
};

Token parse(Lexer::Token);
};  // namespace Parser

#endif  // PARSING_OBJ_WAVEFRONT_PARSER_HPP
