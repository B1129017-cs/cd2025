#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====== HW#1 scanner 中的 token 定義 ======
typedef enum {
    LITERAL_TOKEN,
    PLUS_TOKEN,
    LEFTPAREN_TOKEN,
    RIGHTPAREN_TOKEN,
    EOF_TOKEN,
    UNKNOWN_TOKEN
} TokenType;

const char *token_names[] = {
    "LITERAL_TOKEN", "PLUS_TOKEN", "LEFTPAREN_TOKEN", "RIGHTPAREN_TOKEN", "EOF_TOKEN", "UNKNOWN_TOKEN"
};

// ====== 模擬 Scanner 輸出（暫時使用靜態陣列） ======
TokenType tokens[100];
int token_index = 0;
int token_size = 0;

// ====== Parser 使用的變數 ======
TokenType lookahead;

// ====== 模擬 Scanner 的 next token 函數 ======
TokenType next_token() {
    if (token_index >= token_size)
        return EOF_TOKEN;
    return tokens[token_index++];
}

// ====== ParseError 函數 ======
void parse_error(const char *msg) {
    printf("ParseError: %s\n", msg);
    exit(1);
}

// ====== 文法函數實作 ======

void parse_S();   // S → E S'
void parse_S_();  // S' → ε | + S
void parse_E();   // E → num | ( S )

void parse_S() {
    parse_E();
    parse_S_();
}

void parse_S_() {
    if (lookahead == PLUS_TOKEN) {
        lookahead = next_token();  // consume '+'
        parse_S();
    }
    // else: ε production
}

void parse_E() {
    if (lookahead == LITERAL_TOKEN) {
        lookahead = next_token();  // consume num
    }
    else if (lookahead == LEFTPAREN_TOKEN) {
        lookahead = next_token();  // consume '('
        parse_S();
        if (lookahead != RIGHTPAREN_TOKEN)
            parse_error("Expected ')'");
        lookahead = next_token();  // consume ')'
    }
    else {
        parse_error("Expected number or '('");
    }
}

// ====== 主程式（測試用） ======
int main() {
    // 測資：對應 (1+2)+3
    TokenType sample[] = {
        LEFTPAREN_TOKEN, LITERAL_TOKEN, PLUS_TOKEN, LITERAL_TOKEN, RIGHTPAREN_TOKEN,
        PLUS_TOKEN, LITERAL_TOKEN,
        EOF_TOKEN
    };
    memcpy(tokens, sample, sizeof(sample));
    token_size = sizeof(sample) / sizeof(TokenType);

    lookahead = next_token();
    parse_S();

    if (lookahead != EOF_TOKEN) {
        parse_error("Unexpected token after parsing");
    }

    printf("Parsing successful!\n");
    return 0;
}
