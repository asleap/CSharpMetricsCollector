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

            // Keywords
                    ABSTRACT,
            AS,
            BASE,
            BOOL,
            BREAK,
            BYTE,
            CASE,
            CATCH,
            CHAR,
            CHECKED,
            CLASS,
            CONST,
            CONTINUE,
            DECIMAL,
            DEFAULT,
            DELEGATE,
            DO,
            DOUBLE,
            ELSE,
            ENUM,
            EVENT,
            EXPLICIT,
            EXTERN,
            FALSE,
            FINALLY,
            FIXED,
            FLOAT,
            FOR,
            FOREACH,
            GOTO,
            IF,
            IMPLICIT,
            IN,
            INT,
            INTERFACE,
            INTERNAL,
            IS,
            LOCK,
            LONG,
            NAMESPACE,
            NEW,
            Null,
            OBJECT,
            OPERATOR,
            OUT,
            OVERRIDE,
            PARAMS,
            PRIVATE,
            PROTECTED,
            PUBLIC,
            READONLY,
            REF,
            RETURN,
            SBYTE,
            SEALED,
            SHORT,
            SIZEOF,
            STACKALLOC,
            STATIC,
            STRING,
            STRUCT,
            SWITCH,
            THIS,
            THROW,
            TRUE,
            TRY,
            TYPEOF,
            UINT,
            ULONG,
            UNCHECKED,
            UNSAFE,
            USHORT,
            USING,
            VIRTUAL,
            VOID,
            VOLATILE,
            WHILE,
            YIELD,

            // Literals
                    INTEGER_LITERAL,
            REAL_LITERAL,
            CHARACTER_LITERAL
        };

        Token(const span &_span, const std::string &_attribute, Type _type);

        const span &get_span() const;

        const std::string &get_attribute() const;

        Type get_type() const;

    private:
        span _span;
        std::string _attribute;
        Type _type;
    };

}

#endif //CSHARPMETRICS_TOKEN_HPP
