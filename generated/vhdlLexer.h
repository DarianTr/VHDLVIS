
// Generated from ../vhdl.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  vhdlLexer : public antlr4::Lexer {
public:
  enum {
    ABS = 1, ACCESS = 2, ACROSS = 3, AFTER = 4, ALIAS = 5, ALL = 6, AND = 7, 
    ARCHITECTURE = 8, ARRAY = 9, ASSERT = 10, ATTRIBUTE = 11, BEGIN = 12, 
    BLOCK = 13, BODY = 14, BREAK = 15, BUFFER = 16, BUS = 17, CASE = 18, 
    COMPONENT = 19, CONFIGURATION = 20, CONSTANT = 21, DISCONNECT = 22, 
    DOWNTO = 23, END = 24, ENTITY = 25, ELSE = 26, ELSIF = 27, EXIT = 28, 
    FILE = 29, FOR = 30, FUNCTION = 31, GENERATE = 32, GENERIC = 33, GROUP = 34, 
    GUARDED = 35, IF = 36, IMPURE = 37, IN = 38, INERTIAL = 39, INOUT = 40, 
    IS = 41, LABEL = 42, LIBRARY = 43, LIMIT = 44, LINKAGE = 45, LITERAL = 46, 
    LOOP = 47, MAP = 48, MOD = 49, NAND = 50, NATURE = 51, NEW = 52, NEXT = 53, 
    NOISE = 54, NOR = 55, NOT = 56, NULL_ = 57, OF = 58, ON = 59, OPEN = 60, 
    OR = 61, OTHERS = 62, OUT = 63, PACKAGE = 64, PORT = 65, POSTPONED = 66, 
    PROCESS = 67, PROCEDURE = 68, PROCEDURAL = 69, PURE = 70, QUANTITY = 71, 
    RANGE = 72, REVERSE_RANGE = 73, REJECT = 74, REM = 75, RECORD = 76, 
    REFERENCE = 77, REGISTER = 78, REPORT = 79, RETURN = 80, ROL = 81, ROR = 82, 
    SELECT = 83, SEVERITY = 84, SHARED = 85, SIGNAL = 86, SLA = 87, SLL = 88, 
    SPECTRUM = 89, SRA = 90, SRL = 91, SUBNATURE = 92, SUBTYPE = 93, TERMINAL = 94, 
    THEN = 95, THROUGH = 96, TO = 97, TOLERANCE = 98, TRANSPORT = 99, TYPE = 100, 
    UNAFFECTED = 101, UNITS = 102, UNTIL = 103, USE = 104, VARIABLE = 105, 
    WAIT = 106, WITH = 107, WHEN = 108, WHILE = 109, XNOR = 110, XOR = 111, 
    BASE_LITERAL = 112, BIT_STRING_LITERAL = 113, BIT_STRING_LITERAL_BINARY = 114, 
    BIT_STRING_LITERAL_OCTAL = 115, BIT_STRING_LITERAL_HEX = 116, REAL_LITERAL = 117, 
    BASIC_IDENTIFIER = 118, EXTENDED_IDENTIFIER = 119, LETTER = 120, COMMENT = 121, 
    TAB = 122, SPACE = 123, NEWLINE = 124, CR = 125, CHARACTER_LITERAL = 126, 
    STRING_LITERAL = 127, OTHER_SPECIAL_CHARACTER = 128, DOUBLESTAR = 129, 
    ASSIGN = 130, LE = 131, GE = 132, ARROW = 133, NEQ = 134, VARASGN = 135, 
    BOX = 136, DBLQUOTE = 137, SEMI = 138, COMMA = 139, AMPERSAND = 140, 
    LPAREN = 141, RPAREN = 142, LBRACKET = 143, RBRACKET = 144, COLON = 145, 
    MUL = 146, DIV = 147, PLUS = 148, MINUS = 149, LOWERTHAN = 150, GREATERTHAN = 151, 
    EQ = 152, BAR = 153, DOT = 154, BACKSLASH = 155, EXPONENT = 156, HEXDIGIT = 157, 
    INTEGER = 158, DIGIT = 159, BASED_INTEGER = 160, EXTENDED_DIGIT = 161, 
    APOSTROPHE = 162
  };

  explicit vhdlLexer(antlr4::CharStream *input);

  ~vhdlLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

