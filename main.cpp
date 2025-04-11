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

enum SignalDirection {
    Outgoing,
    Ingoing,
    Bidirectional,
};

SignalDirection string_to_enum_signal_direction(const std::string &in) {
    if (in == "in") return Ingoing;
    if (in == "out") return Outgoing;
    return Bidirectional;
}

struct IdentifierAttributes {
    SignalDirection direction;
    std::string type;
};

class GlobalDeclarationListener final : public vhdlBaseListener {
public:
    std::map<std::string, std::set<DeclarationTypes>> global_declaration_table;

    void exitEntity_declaration(vhdlParser::Entity_declarationContext * ctx) override {
        global_declaration_table[ctx->identifier().back()->getText()].insert(Entity);
        if (ctx->identifier()[0]->getText() != ctx->identifier().back()->getText()) {
            std::cerr << "Line " << ctx->start->getLine() << ": Start and End Identifier aren't matching. Start is " << ctx->identifier()[0]->getText() << " and End ist " << ctx->identifier().back()->getText() << std::endl;
        }
    }

    void exitArchitecture_body(vhdlParser::Architecture_bodyContext * ctx) override {
        if (ctx->identifier()[0]->getText() != ctx->identifier().back()->getText()) {
            std::cerr << "Line " << ctx->start->getLine() << ": Start and End Identifier aren't matching. Start is " << ctx->identifier()[0]->getText() << " and End ist " << ctx->identifier().back()->getText() << std::endl;
        }
    }

    void exitComponent_declaration(vhdlParser::Component_declarationContext * ctx) override {
        if (ctx->identifier().size() > 1) {
            if (ctx->identifier()[0]->getText() != ctx->identifier().back()->getText()) {
            std::cerr << "Line " << ctx->start->getLine() << ": Start and End Identifier aren't matching. Start is " << ctx->identifier()[0]->getText() << " and End ist " << ctx->identifier().back()->getText() << std::endl;
            }
        }
    }


};

class DeclaredBeforeUsedListener final : public vhdlBaseListener {
public: GlobalDeclarationListener* gdl;

    explicit DeclaredBeforeUsedListener(GlobalDeclarationListener* gdl) : gdl(gdl) {}

    void exitArchitecture_body(vhdlParser::Architecture_bodyContext * ctx) override {
        if (!gdl->global_declaration_table[ctx->identifier()[1]->getText()].count(Entity)) {
            std::cerr << "Line " << ctx->start->getLine() << ": No Entity " << ctx->identifier()[1]->getText() << std::endl;
        }
    }

    void exitComponent_declaration(vhdlParser::Component_declarationContext * ctx) override { //components are for entities from different files. This does of course not work
          if (!gdl->global_declaration_table[ctx->identifier()[0]->getText()].count(Entity)) {
              std::cerr << "Line " << ctx->start->getLine() << ": No Entity " << ctx->identifier()[0]->getText() << std::endl;
          }
    }
};


class DeclarationPortsListener final : public vhdlBaseListener {
public:
    std::map<std::string, std::map<std::string, IdentifierAttributes>> entity_to_identifiers_with_type;
private:
    std::string current_entity;

    void enterEntity_declaration(vhdlParser::Entity_declarationContext * ctx) override {
        current_entity = (ctx->identifier().size()) ? ctx->identifier()[0]->getText() : "";
    }

    void exitEntity_declaration(vhdlParser::Entity_declarationContext * ctx) override {
      current_entity = "";
    }

    void exitPort_clause(vhdlParser::Port_clauseContext * ctx) override { //port names
        for (const auto & declaration: ctx->port_list()->interface_port_list()->interface_port_declaration()) {
            auto direction = string_to_enum_signal_direction(declaration->signal_mode()->getText());
            for (int i{}; i < declaration->identifier_list()->identifier().size(); i++) {
                auto iden = declaration->identifier_list()->identifier()[i]->getText();
                const auto type = declaration->subtype_indication()->selected_name()[i]->getText();
                entity_to_identifiers_with_type[current_entity][iden] = {direction, type};
            }

        }
    }

};

class DeclareUseScopedListener final : public vhdlBaseListener {
public:
    DeclarationPortsListener * dpl;
    explicit DeclareUseScopedListener(DeclarationPortsListener* dpl) : dpl(dpl) {};
private:
    bool inside_statement = false;

    std::string current_entity;

    void exitArchitecture_body(vhdlParser::Architecture_bodyContext * ctx) override {
        current_entity = "";
    }

    void enterArchitecture_body(vhdlParser::Architecture_bodyContext * ctx) override {
        current_entity = (!ctx->identifier().empty()) ? ctx->identifier()[0]->getText() : "";
    }

    void exitArchitecture_declarative_part(vhdlParser::Architecture_declarative_partContext * ctx) override {
        for (const auto &i: ctx->block_declarative_item()) {
            for (const auto identifier: i->signal_declaration()->identifier_list()->identifier()) {
                dpl->entity_to_identifiers_with_type[current_entity][identifier->getText()] = {Bidirectional, "signal"};
            }
        }
    }

    void enterConcurrent_signal_assignment_statement(vhdlParser::Concurrent_signal_assignment_statementContext * ctx) override {
        inside_statement = true;
    }
    void exitConcurrent_signal_assignment_statement(vhdlParser::Concurrent_signal_assignment_statementContext * ctx) override {
        inside_statement = false;
    }

    void exitIdentifier(vhdlParser::IdentifierContext *ctx) override {
       if (inside_statement) {
           if (!dpl->entity_to_identifiers_with_type[current_entity].count(ctx->getText())) {
               std::cerr << "Line " << ctx->start->getLine() << ": Unknown identifier name " << ctx->getText() << std::endl;
           }
       }
    }


};

void printTree(antlr4::tree::ParseTree *tree, antlr4::Parser *parser, const std::string &indent = "", bool last = true) {
    std::string marker = last ? "└── " : "├── ";

    // Get rule name if it's a rule context
    std::string ruleInfo = "";
    if (antlr4::ParserRuleContext *ruleContext = dynamic_cast<antlr4::ParserRuleContext*>(tree)) {
        int ruleIndex = ruleContext->getRuleIndex();
        if (ruleIndex >= 0 && parser != nullptr) {
            ruleInfo = " [" + parser->getRuleNames()[ruleIndex] + "]";
        }
    }

    std::cout << indent << marker << tree->getText() << ruleInfo << std::endl;

    auto children = tree->children;
    if (children.size() > 0) {
        for (size_t i = 0; i < children.size(); ++i) {
            printTree(children[i], parser, indent + (last ? "    " : "│   "), i == children.size() - 1);
        }
    }
}



int main() {
    // std::ifstream stream;
    // stream.open("../input.txt");
    //
    // if (stream.is_open()) {
    //     std::cout << "opened" << std::endl;
    // }


    // First pass - fill declaration table
    auto L1 = new GlobalDeclarationListener();
    auto L2 = new DeclarationPortsListener();
    {
        std::ifstream stream("../input.txt");
        ANTLRInputStream input(stream);
        vhdlLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        vhdlParser parser(&tokens);
        parser.addParseListener(L1);
        tree::ParseTree *tree = parser.design_file();
    }

    {
        std::ifstream stream("../input.txt");
        ANTLRInputStream input(stream);
        vhdlLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        vhdlParser parser(&tokens);
        parser.addParseListener(L2);
        tree::ParseTree *tree = parser.design_file();
    }

    // Second pass - check for declaration before use
    {
        std::ifstream stream("../input.txt");
        ANTLRInputStream input(stream);
        vhdlLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        vhdlParser parser(&tokens);
        auto L = new DeclaredBeforeUsedListener(L1);
        parser.addParseListener(L);
        tree::ParseTree *tree = parser.design_file();
    }

    {
        std::ifstream stream("../input.txt");
        ANTLRInputStream input(stream);
        vhdlLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        vhdlParser parser(&tokens);
        auto L = new DeclareUseScopedListener(L2);
        parser.addParseListener(L);
        tree::ParseTree *tree = parser.design_file();
        printTree(tree, &parser);
    }



    return 0;
}
