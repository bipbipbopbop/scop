#include "./Lexer.hpp"

#include <map>
#include <sstream>
#include <string>
#include <utility>

static std::map<std::string, Lexer::TokenType> lexer = {
    {"v", Lexer::TokenType::kVert},
    {"vn", Lexer::TokenType::kVertNorm},
    {"vt", Lexer::TokenType::kVertText},
    {"f", Lexer::TokenType::kFace},
};

Lexer::Token Lexer::lex(std::string line) {
  std::istringstream stream(line);
  std::string id;
  stream >> id;
  return {lexer[id], std::move(line)};
};