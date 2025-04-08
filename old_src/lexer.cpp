//
// Created by darian on 08.04.25.
//

#include "lexer.h"
#include <string>
#include <optional>
#include "antlr4-runtime/antlr4-runtime.h"

enum class ReservedToken {
    // Keyword tokens
    KEYWORD_ACCESS, KEYWORD_AFTER, KEYWORD_ALIAS,
    KEYWORD_ALL, KEYWORD_ARCHITECTURE, KEYWORD_ARRAY,
    KEYWORD_ASSERT, KEYWORD_ATTRIBUTE, KEYWORD_BEGIN, KEYWORD_BLOCK,
    KEYWORD_BODY, KEYWORD_BUFFER, KEYWORD_BUS, KEYWORD_CASE,
    KEYWORD_COMPONENT, KEYWORD_CONFIGURATION, KEYWORD_CONSTANT, KEYWORD_DISCONNECT,
    KEYWORD_DOWNTO, KEYWORD_ELSE, KEYWORD_ELSIF, KEYWORD_END,
    KEYWORD_ENTITY, KEYWORD_EXIT, KEYWORD_FILE, KEYWORD_FOR,
    KEYWORD_FUNCTION, KEYWORD_GENERATE, KEYWORD_GENERIC, KEYWORD_GROUP,
    KEYWORD_GUARDED, KEYWORD_IF, KEYWORD_IMPURE, KEYWORD_IN,
    KEYWORD_INERTIAL, KEYWORD_INOUT, KEYWORD_IS, KEYWORD_LABEL,
    KEYWORD_LIBRARY, KEYWORD_LINKAGE, KEYWORD_LITERAL, KEYWORD_LOOP,
    KEYWORD_MAP, KEYWORD_NEW, KEYWORD_NEXT, KEYWORD_NULL,
    KEYWORD_OF, KEYWORD_ON, KEYWORD_OPEN, KEYWORD_OTHERS,
    KEYWORD_OUT, KEYWORD_PACKAGE, KEYWORD_PORT, KEYWORD_POSTPONED,
    KEYWORD_PROCEDURE, KEYWORD_PROCESS, KEYWORD_PURE, KEYWORD_RANGE,
    KEYWORD_RECORD, KEYWORD_REGISTER, KEYWORD_REJECT, KEYWORD_REPORT,
    KEYWORD_RETURN, KEYWORD_SELECT, KEYWORD_SEVERITY, KEYWORD_SIGNAL,
    KEYWORD_SHARED, KEYWORD_SUBTYPE, KEYWORD_THEN, KEYWORD_TO,
    KEYWORD_TRANSPORT, KEYWORD_TYPE, KEYWORD_UNAFFECTED, KEYWORD_UNITS,
    KEYWORD_UNTIL, KEYWORD_USE, KEYWORD_VARIABLE, KEYWORD_WAIT,
    KEYWORD_WHEN, KEYWORD_WHILE, KEYWORD_WITH,

    // Operator tokens
    OPERATOR_ABS, OPERATOR_AND, OPERATOR_MOD, OPERATOR_NAND,
    OPERATOR_NOR, OPERATOR_NOT, OPERATOR_OR, OPERATOR_REM,
    OPERATOR_ROL, OPERATOR_ROR, OPERATOR_SLA, OPERATOR_SLL,
    OPERATOR_SRA, OPERATOR_SRL, OPERATOR_XNOR, OPERATOR_XOR,
    OPERATOR_EXP, OPERATOR_MUL, OPERATOR_DIV, OPERATOR_PLUS,
    OPERATOR_MINUS, OPERATOR_CONCAT, OPERATOR_EQ, OPERATOR_INEQ,
    OPERATOR_LT, OPERATOR_LEQ, OPERATOR_GT, OPERATOR_GEQ
};

struct Token {
    ReservedToken type;
};

std::optional<Token> check_for_keyword(const std::string &s) {
    switch (s[0]) {
        case 'a':
            if (s == "abs") return Token{ReservedToken::OPERATOR_ABS};
            if (s == "access") return Token{ReservedToken::KEYWORD_ACCESS};
            if (s == "after") return Token{ReservedToken::KEYWORD_AFTER};
            if (s == "alias") return Token{ReservedToken::KEYWORD_ALIAS};
            if (s == "all") return Token{ReservedToken::KEYWORD_ALL};
            if (s == "and") return Token{ReservedToken::OPERATOR_AND};
            if (s == "architecture") return Token{ReservedToken::KEYWORD_ARCHITECTURE};
            if (s == "array") return Token{ReservedToken::KEYWORD_ARRAY};
            if (s == "assert") return Token{ReservedToken::KEYWORD_ASSERT};
            if (s == "attribute") return Token{ReservedToken::KEYWORD_ATTRIBUTE};
            break;
        case 'b':
            if (s == "begin") return Token{ReservedToken::KEYWORD_BEGIN};
            if (s == "block") return Token{ReservedToken::KEYWORD_BLOCK};
            if (s == "body") return Token{ReservedToken::KEYWORD_BODY};
            if (s == "buffer") return Token{ReservedToken::KEYWORD_BUFFER};
            if (s == "bus") return Token{ReservedToken::KEYWORD_BUS};
            break;
        case 'c':
            if (s == "case") return Token{ReservedToken::KEYWORD_CASE};
            if (s == "component") return Token{ReservedToken::KEYWORD_COMPONENT};
            if (s == "configuration") return Token{ReservedToken::KEYWORD_CONFIGURATION};
            if (s == "constant") return Token{ReservedToken::KEYWORD_CONSTANT};
            break;
        case 'd':
            if (s == "disconnect") return Token{ReservedToken::KEYWORD_DISCONNECT};
            if (s == "downto") return Token{ReservedToken::KEYWORD_DOWNTO};
            break;
        case 'e':
            if (s == "else") return Token{ReservedToken::KEYWORD_ELSE};
            if (s == "elsif") return Token{ReservedToken::KEYWORD_ELSIF};
            if (s == "end") return Token{ReservedToken::KEYWORD_END};
            if (s == "entity") return Token{ReservedToken::KEYWORD_ENTITY};
            if (s == "exit") return Token{ReservedToken::KEYWORD_EXIT};
            break;
        case 'f':
            if (s == "file") return Token{ReservedToken::KEYWORD_FILE};
            if (s == "for") return Token{ReservedToken::KEYWORD_FOR};
            if (s == "function") return Token{ReservedToken::KEYWORD_FUNCTION};
            break;
        case 'g':
            if (s == "generate") return Token{ReservedToken::KEYWORD_GENERATE};
            if (s == "generic") return Token{ReservedToken::KEYWORD_GENERIC};
            if (s == "group") return Token{ReservedToken::KEYWORD_GROUP};
            if (s == "guarded") return Token{ReservedToken::KEYWORD_GUARDED};
            break;
        case 'i':
            if (s == "if") return Token{ReservedToken::KEYWORD_IF};
            if (s == "impure") return Token{ReservedToken::KEYWORD_IMPURE};
            if (s == "in") return Token{ReservedToken::KEYWORD_IN};
            if (s == "inertial") return Token{ReservedToken::KEYWORD_INERTIAL};
            if (s == "inout") return Token{ReservedToken::KEYWORD_INOUT};
            if (s == "is") return Token{ReservedToken::KEYWORD_IS};
            break;
        case 'l':
            if (s == "label") return Token{ReservedToken::KEYWORD_LABEL};
            if (s == "library") return Token{ReservedToken::KEYWORD_LIBRARY};
            if (s == "linkage") return Token{ReservedToken::KEYWORD_LINKAGE};
            if (s == "literal") return Token{ReservedToken::KEYWORD_LITERAL};
            if (s == "loop") return Token{ReservedToken::KEYWORD_LOOP};
            break;
        case 'm':
            if (s == "map") return Token{ReservedToken::KEYWORD_MAP};
            if (s == "mod") return Token{ReservedToken::OPERATOR_MOD};
            break;
        case 'n':
            if (s == "nand") return Token{ReservedToken::OPERATOR_NAND};
            if (s == "new") return Token{ReservedToken::KEYWORD_NEW};
            if (s == "next") return Token{ReservedToken::KEYWORD_NEXT};
            if (s == "nor") return Token{ReservedToken::OPERATOR_NOR};
            if (s == "not") return Token{ReservedToken::OPERATOR_NOT};
            if (s == "null") return Token{ReservedToken::KEYWORD_NULL};
            break;
        case 'o':
            if (s == "of") return Token{ReservedToken::KEYWORD_OF};
            if (s == "on") return Token{ReservedToken::KEYWORD_ON};
            if (s == "open") return Token{ReservedToken::KEYWORD_OPEN};
            if (s == "or") return Token{ReservedToken::OPERATOR_OR};
            if (s == "others") return Token{ReservedToken::KEYWORD_OTHERS};
            if (s == "out") return Token{ReservedToken::KEYWORD_OUT};
            break;
        case 'p':
            if (s == "package") return Token{ReservedToken::KEYWORD_PACKAGE};
            if (s == "port") return Token{ReservedToken::KEYWORD_PORT};
            if (s == "postponed") return Token{ReservedToken::KEYWORD_POSTPONED};
            if (s == "procedure") return Token{ReservedToken::KEYWORD_PROCEDURE};
            if (s == "process") return Token{ReservedToken::KEYWORD_PROCESS};
            if (s == "pure") return Token{ReservedToken::KEYWORD_PURE};
            break;
        case 'r':
            if (s == "range") return Token{ReservedToken::KEYWORD_RANGE};
            if (s == "record") return Token{ReservedToken::KEYWORD_RECORD};
            if (s == "register") return Token{ReservedToken::KEYWORD_REGISTER};
            if (s == "reject") return Token{ReservedToken::KEYWORD_REJECT};
            if (s == "rem") return Token{ReservedToken::OPERATOR_REM};
            if (s == "report") return Token{ReservedToken::KEYWORD_REPORT};
            if (s == "return") return Token{ReservedToken::KEYWORD_RETURN};
            if (s == "rol") return Token{ReservedToken::OPERATOR_ROL};
            if (s == "ror") return Token{ReservedToken::OPERATOR_ROR};
            break;
        case 's':
            if (s == "select") return Token{ReservedToken::KEYWORD_SELECT};
            if (s == "severity") return Token{ReservedToken::KEYWORD_SEVERITY};
            if (s == "signal") return Token{ReservedToken::KEYWORD_SIGNAL};
            if (s == "shared") return Token{ReservedToken::KEYWORD_SHARED};
            if (s == "sla") return Token{ReservedToken::OPERATOR_SLA};
            if (s == "sll") return Token{ReservedToken::OPERATOR_SLL};
            if (s == "sra") return Token{ReservedToken::OPERATOR_SRA};
            if (s == "srl") return Token{ReservedToken::OPERATOR_SRL};
            if (s == "subtype") return Token{ReservedToken::KEYWORD_SUBTYPE};
            break;
        case 't':
            if (s == "then") return Token{ReservedToken::KEYWORD_THEN};
            if (s == "to") return Token{ReservedToken::KEYWORD_TO};
            if (s == "transport") return Token{ReservedToken::KEYWORD_TRANSPORT};
            if (s == "type") return Token{ReservedToken::KEYWORD_TYPE};
            break;
        case 'u':
            if (s == "unaffected") return Token{ReservedToken::KEYWORD_UNAFFECTED};
            if (s == "units") return Token{ReservedToken::KEYWORD_UNITS};
            if (s == "until") return Token{ReservedToken::KEYWORD_UNTIL};
            if (s == "use") return Token{ReservedToken::KEYWORD_USE};
            break;
        case 'v':
            if (s == "variable") return Token{ReservedToken::KEYWORD_VARIABLE};
            break;
        case 'w':
            if (s == "wait") return Token{ReservedToken::KEYWORD_WAIT};
            if (s == "when") return Token{ReservedToken::KEYWORD_WHEN};
            if (s == "while") return Token{ReservedToken::KEYWORD_WHILE};
            if (s == "with") return Token{ReservedToken::KEYWORD_WITH};
            break;
        case 'x':
            if (s == "xnor") return Token{ReservedToken::OPERATOR_XNOR};
            if (s == "xor") return Token{ReservedToken::OPERATOR_XOR};
            break;
        case '*':
            if (s == "**") return Token{ReservedToken::OPERATOR_EXP};
            if (s == "*") return Token{ReservedToken::OPERATOR_MUL};
            break;
        case '/':
            if (s == "/") return Token{ReservedToken::OPERATOR_DIV};
            if (s == "/=") return Token{ReservedToken::OPERATOR_INEQ};
            break;
        case '+':
            return Token{ReservedToken::OPERATOR_PLUS};
        case '-':
            return Token{ReservedToken::OPERATOR_MINUS};
        case '&':
            return Token{ReservedToken::OPERATOR_CONCAT};
        case '=':
            return Token{ReservedToken::OPERATOR_EQ};
        case '<':
            if (s == "<") return Token{ReservedToken::OPERATOR_LT};
            if (s == "<=") return Token{ReservedToken::OPERATOR_LEQ};
            break;
        case '>':
            if (s == ">") return Token{ReservedToken::OPERATOR_GT};
            if (s == ">=") return Token{ReservedToken::OPERATOR_GEQ};
            break;
        default:
            return std::nullopt;
    }
}





int main() {
  return 0;
}