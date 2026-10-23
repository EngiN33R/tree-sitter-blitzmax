#include "tree_sitter/parser.h"

// Only the ASCII words Rem and EndRem are scanned here. Avoid libc locale
// functions so the grammar has no extra host imports in Zed's WASM runtime.
static int32_t lower(int32_t c) { return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c; }
static bool isword(int32_t c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'; }

enum TokenType { BLOCK_COMMENT, MULTILINE_STRING };
void *tree_sitter_blitzmax_external_scanner_create(void) { return NULL; }
void tree_sitter_blitzmax_external_scanner_destroy(void *payload) { (void)payload; }
unsigned tree_sitter_blitzmax_external_scanner_serialize(void *payload, char *buffer) { (void)payload; (void)buffer; return 0; }
void tree_sitter_blitzmax_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) { (void)payload; (void)buffer; (void)length; }
static bool word(TSLexer *lexer, const char *s) {
    while (*s) {
        if (lower(lexer->lookahead) != *s++) return false;
        lexer->advance(lexer, false);
    }
    return true;
}
bool tree_sitter_blitzmax_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid) {
    (void)payload;
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') lexer->advance(lexer, true);
    if (valid[MULTILINE_STRING] && lexer->lookahead == '"') {
        for (int i = 0; i < 3; ++i) {
            if (lexer->lookahead != '"') return false;
            lexer->advance(lexer, false);
        }
        int quotes = 0;
        while (!lexer->eof(lexer)) {
            quotes = lexer->lookahead == '"' ? quotes + 1 : 0;
            lexer->advance(lexer, false);
            if (quotes == 3) break;
        }
        lexer->mark_end(lexer);
        lexer->result_symbol = MULTILINE_STRING;
        return true;
    }
    if (!valid[BLOCK_COMMENT] || !word(lexer, "rem")) return false;
    if (isword(lexer->lookahead)) return false;
    bool line_start = false;
    while (!lexer->eof(lexer)) {
        if (line_start) {
            while (lexer->lookahead == ' ' || lexer->lookahead == '\t') lexer->advance(lexer, false);
            if (lower(lexer->lookahead) == 'e') {
                if (word(lexer, "end")) {
                    while (lexer->lookahead == ' ' || lexer->lookahead == '\t') lexer->advance(lexer, false);
                    if (word(lexer, "rem") && !isword(lexer->lookahead)) {
                        lexer->mark_end(lexer);
                        lexer->result_symbol = BLOCK_COMMENT;
                        return true;
                    }
                }
            }
        }
        line_start = lexer->lookahead == '\n';
        lexer->advance(lexer, false);
    }
    lexer->mark_end(lexer);
    lexer->result_symbol = BLOCK_COMMENT;
    return true;
}
