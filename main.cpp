//
// Created by darian on 08.04.25.
//


#include "antlr4-runtime.h"
#include "vhdlLexer.h"
#include "vhdlParser.h"
#include "vhdlBaseListener.h"

#include <iostream>
#include <map>

using namespace antlr4;

enum DeclarationTypes {
    Entity,
};

std::map<std::string, std::set<DeclarationTypes>> global_declaration_table;

class GlobalDeclarationListener : public vhdlBaseListener {

    void exitEntity_declaration(vhdlParser::Entity_declarationContext * ctx) override {
        global_declaration_table[ctx->identifier().back()->getText()].insert(Entity);
        if (ctx->identifier()[0]->getText() != ctx->identifier().back()->getText()) {
            std::cerr << "Start and End Identifier aren't matching. Start is " << ctx->identifier()[0]->getText() << " and End ist " << ctx->identifier().back()->getText() << std::endl;
        }
    }

    void exitArchitecture_body(vhdlParser::Architecture_bodyContext * ctx) override {
        if (ctx->identifier()[0]->getText() != ctx->identifier().back()->getText()) {
            std::cerr << "Start and End Identifier aren't matching. Start is " << ctx->identifier()[0]->getText() << " and End ist " << ctx->identifier().back()->getText() << std::endl;
        }
    }

};

class DeclaredBeforeUsedListener : public vhdlBaseListener {
    void exitArchitecture_body(vhdlParser::Architecture_bodyContext * ctx) override {
        if (!global_declaration_table[ctx->identifier()[1]->getText()].count(Entity)) {
            std::cerr << "No Entity " << ctx->identifier()[1]->getText() << std::endl;
        }
    }
};

void printTree(antlr4::tree::ParseTree *tree, const std::string &indent = "", bool last = true) {
    std::string marker = last ? "└── " : "├── ";
    std::cout << indent << marker << tree->getText() << std::endl;

    auto children = tree->children;
    for (size_t i = 0; i < children.size(); ++i) {
        printTree(children[i], indent + (last ? "    " : "│   "), i == children.size() - 1);
    }
}


int main() {
    std::ifstream stream;
    stream.open("../input.txt");

    if (stream.is_open()) {
        std::cout << "opened" << std::endl;
    }

    // First pass - fill declaration table
    {
        std::ifstream stream("../input.txt");
        ANTLRInputStream input(stream);
        vhdlLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        vhdlParser parser(&tokens);
        auto L = new GlobalDeclarationListener();
        parser.addParseListener(L);
        tree::ParseTree *tree = parser.design_file();
    }

    // Second pass - check for declaration before use
    {
        std::ifstream stream("../input.txt");
        ANTLRInputStream input(stream);
        vhdlLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        vhdlParser parser(&tokens);
        auto L = new DeclaredBeforeUsedListener();
        parser.addParseListener(L);
        tree::ParseTree *tree = parser.design_file();
    }


    return 0;
}
