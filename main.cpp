//
// Created by darian on 08.04.25.
//


#include "antlr4-runtime.h"
#include "vhdlLexer.h"
#include "vhdlParser.h"
#include <iostream>

using namespace antlr4;

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

    ANTLRInputStream input(stream);
    vhdlLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    vhdlParser parser(&tokens);

    tree::ParseTree *tree = parser.design_file();
    // std::cout << tree->toStringTree(&parser) << std::endl;
    printTree(tree);

    return 0;
}
