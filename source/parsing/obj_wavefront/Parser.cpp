#include "./Parser.hpp"

#include <algorithm>
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#include "./Lexer.hpp"
#include "./data.hpp"

using PToken = Parser::Token;
using LToken = Lexer::Token;

PToken::~Token() {
  switch (this->type) {
    case Lexer::TokenType::kFace:
      delete static_cast<Face *>(this->data);
      break;
    case Lexer::TokenType::kVert:
      delete static_cast<Vertex *>(this->data);
      break;
    case Lexer::TokenType::kVertNorm:
      delete static_cast<VNormal *>(this->data);
      break;
    case Lexer::TokenType::kVertText:
      delete static_cast<VTexture *>(this->data);
      break;
    case Lexer::TokenType::kUnknown:
      break;
  }
};

PToken parseVert(LToken token) {
  std::istringstream stream(token.second);
  Vertex result{0., 0., 0., 1.};
  std::string sink;

  stream >> sink >> result[0] >> result[1] >> result[2];  // first word is the identifier
  if (!stream.eof()) {
    stream >> result[3];
  }
  return {new Vertex(std::move(result)), token.first};
};

PToken parseVNorm(LToken token) {
  std::istringstream stream(token.second);
  VNormal result{0., 0., 0.};
  std::string sink;

  stream >> sink >> result[0] >> result[1] >> result[2];  // first word is the identifier
  return {new VNormal(std::move(result)), token.first};
};

PToken parseVText(LToken token) {
  std::istringstream stream(token.second);
  VTexture result{0., 0., 0.};
  std::string sink;

  stream >> sink >> result[0] >> result[1];  // first word is the identifier
  if (!stream.eof()) {
    stream >> result[2];
  }
  return {new VTexture(std::move(result)), token.first};
};

static FaceIndex buildFaceIndex(std::string indices) {
  const ssize_t slash_nb = std::count(indices.cbegin(), indices.cend(), '/');

  switch (slash_nb) {
    case 0:
      // format: "v"
      return {std::stol(indices), 0, 0};
    case 1:
      // format: "v/vt"
      return {std::stol(indices.substr(0, indices.find_first_of('/'))),
              std::stol(indices.substr(indices.find_last_of('/') + 1)), 0};
    case 2:
      if (indices.find("//") != std::string::npos) {
        // format: "v//vn"
        return {std::stol(indices.substr(0, indices.find_first_of('/'))), 0,
                std::stol(indices.substr(indices.find_last_of('/') + 1))};
      } else {
        // format: "v/vt/vn"
        return {std::stol(indices.substr(0, indices.find_first_of('/'))),
                std::stol(indices.substr(indices.find_first_of('/'), indices.find_last_of('/'))),
                std::stol(indices.substr(indices.find_last_of('/') + 1))};
      }
    default:
      return {0, 0, 0};
  };
};

PToken parseFace(LToken token) {
  std::istringstream stream(token.second);
  Face result;
  std::string sink;

  stream >> sink;  // first word is the identifier
  while (!stream.eof()) {
    stream >> sink;
    result.push_back(buildFaceIndex(sink));
  }
  return {new Face(std::move(result)), token.first};
};

using ParserF = PToken(LToken);
static std::map<Lexer::TokenType, ParserF *> parser = {
    {Lexer::TokenType::kUnknown, nullptr},     {Lexer::TokenType::kVert, parseVert},
    {Lexer::TokenType::kVertNorm, parseVNorm}, {Lexer::TokenType::kVertText, parseVText},
    {Lexer::TokenType::kFace, parseFace},
};

PToken Parser::parse(LToken token) {
  if (parser[token.first] == nullptr) {
    return PToken();
  }
  return parser[token.first](token);
};