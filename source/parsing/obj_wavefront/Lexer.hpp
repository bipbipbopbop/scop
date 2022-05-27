#ifndef PARSING_OBJ_WAVEFRONT_LEXER_HPP
#define PARSING_OBJ_WAVEFRONT_LEXER_HPP

#include <string>
#include <utility>

namespace Lexer {
enum class TokenType { kUnknown = 0, kVert, kVertText, kVertNorm, kFace };

// first is the token type, second is the lex'd line
using Token = std::pair<TokenType, std::string>;

Token lex(std::string line);
};  // namespace Lexer

#endif  // PARSING_OBJ_WAVEFRONT_LEXER_HPP
