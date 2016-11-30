//
// Created by asleap on 08.11.2016.
//

#ifndef CSHARPMETRICS_TOKEN_HPP
#define CSHARPMETRICS_TOKEN_HPP

#include <string>

namespace CSMetrics {

/**
 * Location type.
 * Points to some location in the source code file
 */
struct location {
    int lineno;
    int charno;

    location(int lineno, int charno) : lineno(lineno), charno(charno) {}
};


/**
 * Span type.
 * Used to designate some area in the source code
 */
struct span {
    location begin;
    location end;

    span(const location begin, const location end) : begin(begin), end(end) {}
};


/**
 * Token class
 */
class Token {
public:

    /**
     * All token types according to language specification
     */
    enum Type {
        END,

        COMMENT,

        // Literals
//        BOOLEAN_LITERAL,  (true, false) - scanned as keywords
        INTEGER_LITERAL,
        REAL_LITERAL

    };

    Token(const span &_span, const std::string &_attribute, Type _type);

    const span &get_span() const;

    const std::string &get_attribute() const;

    Type get_type() const;

private:
    span        _span;
    std::string _attribute;
    Type        _type;
};

}

#endif //CSHARPMETRICS_TOKEN_HPP
