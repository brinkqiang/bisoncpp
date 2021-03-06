#ifndef Parser_h_included
#define Parser_h_included

// this file was originally generated by bisonc++, then modified and renamed
// to parser.h so that it was kept when the `run' script was executed. When
// executing `run', compare the contents of this file and those of Parser.h,
// to see what local modifications were made: only the Parser constructor was
// added (and this comment, of course)

// $insert scanner.h
#include "../scanner/scanner.h"

// $insert baseclass
#include "Parserbase.h"
#undef Parser

class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        Parser()
        :
            d_scanner(&d_loc__, &d_val__)
        {}
        
        int parse();

    private:
        void error();                   // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction__(int ruleNr);
        void errorRecovery__();
        void nextToken__();
        void nextCycle__();
        void print__();
};

inline void Parser::error()
{
    std::cerr << "Syntax error\n";
}

// $insert lex
inline int Parser::lex()
{
    return d_scanner.lex();
}

inline void Parser::print()         
{
    print__();           // displays tokens if --print was specified
}


#endif
