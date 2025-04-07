#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

typedef enum {
    TYPE_TOKEN, MAIN_TOKEN, IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN,
    ID_TOKEN, LITERAL_TOKEN,
    ASSIGN_TOKEN, EQUAL_TOKEN, GREATER_TOKEN, LESS_TOKEN,
    GREATEREQUAL_TOKEN, LESSEQUAL_TOKEN,
    LEFTPAREN_TOKEN, RIGHTPAREN_TOKEN, LEFTBRACE_TOKEN, RIGHTBRACE_TOKEN,
    SEMICOLON_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
    UNKNOWN_TOKEN
} TokenType;

const char* token_names[] = {
    "TYPE_TOKEN", "MAIN_TOKEN", "IF_TOKEN", "ELSE_TOKEN", "WHILE_TOKEN",
    "ID_TOKEN", "LITERAL_TOKEN",
    "ASSIGN_TOKEN", "EQUAL_TOKEN", "GREATER_TOKEN", "LESS_TOKEN",
    "GREATEREQUAL_TOKEN", "LESSEQUAL_TOKEN",
    "LEFTPAREN_TOKEN", "RIGHTPAREN_TOKEN", "LEFTBRACE_TOKEN", "RIGHTBRACE_TOKEN",
    "SEMICOLON_TOKEN", "PLUS_TOKEN", "MINUS_TOKEN",
    "UNKNOWN_TOKEN"
};

// 函數檢查字元是否為字母或底線
int is_alpha(char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_');
}

// 函數檢查字元是否為數字
int is_digit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// 函數檢查字元是否為字母、數字或底線
int is_alnum(char ch) {
    return (is_alpha(ch) || is_digit(ch));
}

// 函數檢查字元是否為空白字元
int is_space(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}

// 檢查關鍵字
TokenType check_keyword(const char *str) {
    if (strcmp(str, "int") == 0) return TYPE_TOKEN;
    if (strcmp(str, "main") == 0) return MAIN_TOKEN;
    if (strcmp(str, "if") == 0) return IF_TOKEN;
    if (strcmp(str, "else") == 0) return ELSE_TOKEN;
    if (strcmp(str, "while") == 0) return WHILE_TOKEN;
    return ID_TOKEN;
}

void print_token(TokenType type, const char *lexeme) {
    printf("%s: %s\n", lexeme, token_names[type]);
}

int main() {
    FILE *file = fopen("main.c", "r");
    if (!file) {
        perror("File open failed");
        return 1;
    }

    char ch, token[MAX_TOKEN_LEN];
    int i = 0;

    while ((ch = fgetc(file)) != EOF) {
        // 跳過空白字元
        if (is_space(ch)) continue;

        // 識別符和關鍵字
        if (is_alpha(ch)) {
            i = 0;
            token[i++] = ch;
            while ((ch = fgetc(file)) != EOF && is_alnum(ch)) {
                token[i++] = ch;
            }
            token[i] = '\0';
            ungetc(ch, file);
            print_token(check_keyword(token), token);
        }
        // 數字
        else if (is_digit(ch)) {
            i = 0;
            token[i++] = ch;
            while ((ch = fgetc(file)) != EOF && is_digit(ch)) {
                token[i++] = ch;
            }
            token[i] = '\0';
            ungetc(ch, file);
            print_token(LITERAL_TOKEN, token);
        }
        // 運算符和符號
        else {
            switch (ch) {
                case '=':
                    if ((ch = fgetc(file)) == '=') print_token(EQUAL_TOKEN, "==");
                    else {
                        ungetc(ch, file);
                        print_token(ASSIGN_TOKEN, "=");
                    }
                    break;
                case '>':
                    if ((ch = fgetc(file)) == '=') print_token(GREATEREQUAL_TOKEN, ">=");
                    else {
                        ungetc(ch, file);
                        print_token(GREATER_TOKEN, ">");
                    }
                    break;
                case '<':
                    if ((ch = fgetc(file)) == '=') print_token(LESSEQUAL_TOKEN, "<=");
                    else {
                        ungetc(ch, file);
                        print_token(LESS_TOKEN, "<");
                    }
                    break;
                case '+':
                    print_token(PLUS_TOKEN, "+");
                    break;
                case '-':
                    print_token(MINUS_TOKEN, "-");
                    break;
                case '(':
                    print_token(LEFTPAREN_TOKEN, "(");
                    break;
                case ')':
                    print_token(RIGHTPAREN_TOKEN, ")");
                    break;
                case '{':
                    print_token(LEFTBRACE_TOKEN, "{");
                    break;
                case '}':
                    print_token(RIGHTBRACE_TOKEN, "}");
                    break;
                case ';':
                    print_token(SEMICOLON_TOKEN, ";");
                    break;
                default:
                    // 忽略不需要辨識的符號
                    break;
            }
        }
    }

    fclose(file);
    return 0;
}
