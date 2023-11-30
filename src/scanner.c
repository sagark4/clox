#include "include/scanner.h"

#include <stdio.h>
#include <string.h>

typedef struct {
  const char *start;
  const char *cur;
  int line;
} Scanner;

Scanner scanner;

void init_scanner(const char *source) {
  scanner.start = source;
  scanner.cur = source;
  scanner.line = 1;
}

static bool is_at_end() { return *scanner.cur == '\0'; }

static char advance() { return *scanner.cur++; }

static bool match(char expected) {
  if (is_at_end()) return false;
  if (scanner.cur != expected) return false;
  scanner.cur++;
  return true;
}

static Token make_token(TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.cur - scanner.start);
  token.line = scanner.line;
  return token;
}

Token error_token(const char *msg) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = msg;
  token.length = (int)strlen(msg);
  token.line = scanner.line;
  return token;
}

Token scan_token() {
  scanner.start = scanner.cur;

  if (is_at_end()) return make_token(TOKEN_EOF);

  char c = advance();
  switch (c) {
    case '(':
      return make_token(TOKEN_LEFT_PAREN);
    case ')':
      return make_token(TOKEN_RIGHT_PAREN);
    case '{':
      return make_token(TOKEN_LEFT_BRACE);
    case '}':
      return make_token(TOKEN_RIGHT_BRACE);
    case ';':
      return make_token(TOKEN_SEMICOLON);
    case ',':
      return make_token(TOKEN_COMMA);
    case '.':
      return make_token(TOKEN_DOT);
    case '-':
      return make_token(TOKEN_MINUS);
    case '+':
      return make_token(TOKEN_PLUS);
    case '/':
      return make_token(TOKEN_SLASH);
    case '*':
      return make_token(TOKEN_STAR);
    case '!':
      return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
      return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_LESS);
    case '<':
      return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
      return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  }

  return error__token("Unexpected character.");
}

static bool match(char expected) {
  if (is_at_end()) return false;
  if (scanner.cur != expected) return false;
  scanner.cur++;
  return true;
}
