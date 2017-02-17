//
// Created by Timofey Lysenko on 05.10.16.
//

#ifndef CSHARPMETRICS_CSSCANNER_H
#define CSHARPMETRICS_CSSCANNER_H 1

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <CSParser.hh>
#include <location.hh>

namespace Metrics {

class CSScanner : public yyFlexLexer {
public:
    int yylexret;

    CSScanner(std::istream *in)
        :
        yyFlexLexer(in) {
        loc = new Metrics::CSParser::location_type();
    }

    virtual ~CSScanner() {
        delete loc;
    }

    // Get rid of override function warning
    using FlexLexer::yylex;

    // YY_DECL defined in CSScanner.l
    // Method body created by flex in CSScanner.cc

    virtual int yylex(Metrics::CSParser::semantic_type *const lval, Metrics::CSParser::location_type *location);

    /**
     * Wrapper for yylex(), allows to store its output in yylexret
     * @return token code returned by yylex()
     */
    virtual int yylexwrap() {
        yylexret = yylex();
        return yylexret;
    }

    /**
     * Wrapper for yylex(), allows to store its output in yylexret
     * @return token code returned by yylex(lval, location)
     */
    virtual int yylexwrap(Metrics::CSParser::semantic_type *const lval, Metrics::CSParser::location_type *location) {
        yylexret = yylex(lval, location);
        return yylexret;
    }

private:
    // yylval pointer
    Metrics::CSParser::semantic_type *yylval = nullptr;
    // _location pointer
    Metrics::CSParser::location_type *loc = nullptr;
};

} // end namespace Metrics

#endif //CSHARPMETRICS_CSSCANNER_H