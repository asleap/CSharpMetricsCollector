//
// Created by asleap on 07.11.2016.
//

#ifndef CSHARPMETRICS_CSLEXER_HPP
#define CSHARPMETRICS_CSLEXER_HPP

#include <istream>
#include <iostream>
#include <vector>
#include <c++/deque>

#include "Token.hpp"

namespace CSMetrics {

    /**
     * Simple lexer implementation.
     * Written in correspondance to language standard.
     * However, supports only ASCII characters since
     * weak C++ Unicode support.
     */
    class Lexer {
    public:

        /**
         * @param input - character stream that represents source code
         * @param number_of_lines - size of the _chars_in_line buffer
         */
        Lexer(std::istream &input, size_t number_of_lines);

        void TestFunc() {
            skip_whitespaces();
            Token tok = scan_comment();
            span tokspan = tok.get_span();
            std::cout << tok.get_attribute();
            std::cout << ", begin:" << tokspan.begin.lineno << ":" << tokspan.begin.charno;
            std::cout << ", end:" << tokspan.end.lineno << ":" << tokspan.end.charno << std::endl;

            skip_whitespaces();
            Token tok2 = scan_comment();
            span tok2span = tok2.get_span();
            std::cout << tok2.get_attribute();
            std::cout << ", begin:" << tok2span.begin.lineno << ":" << tok2span.begin.charno;
            std::cout << ", end:" << tok2span.end.lineno << ":" << tok2span.end.charno << std::endl;

            skip_whitespaces();
            Token tok3 = scan_integer_literal();
            span tok3span = tok3.get_span();
            std::cout << tok3.get_attribute();
            std::cout << ", begin:" << tok3span.begin.lineno << ":" << tok3span.begin.charno;
            std::cout << ", end:" << tok3span.end.lineno << ":" << tok3span.end.charno << std::endl;

            skip_whitespaces();
            Token tok4 = scan_real_literal();
            span tok4span = tok4.get_span();
            std::cout << tok4.get_attribute();
            std::cout << ", begin:" << tok4span.begin.lineno << ":" << tok4span.begin.charno;
            std::cout << ", end:" << tok4span.end.lineno << ":" << tok4span.end.charno << std::endl;

            skip_whitespaces();
            Token tok5 = scan_character_literal();
            span tok5span = tok5.get_span();
            std::cout << tok5.get_attribute();
            std::cout << ", begin:" << tok5span.begin.lineno << ":" << tok5span.begin.charno;
            std::cout << ", end:" << tok5span.end.lineno << ":" << tok5span.end.charno << std::endl;

            skip_whitespaces();
            Token tok6 = scan_string_literal();
            span tok6span = tok6.get_span();
            std::cout << tok6.get_attribute();
            std::cout << ", begin:" << tok6span.begin.lineno << ":" << tok6span.begin.charno;
            std::cout << ", end:" << tok6span.end.lineno << ":" << tok6span.end.charno << std::endl;

            skip_whitespaces();
        }

    private:
        std::istream &_input;               // Input stream of the source code
        char _ch;                           // Last read character (use current() to get)
        location _loc;                      // Current _location in source
        std::vector<int> _chars_in_line;    // Stores number of chars in a given line

        /**
         * Outputs scanning error message to std::cerr and throws exception
         * @param message - error message
         */
        void scanning_error(std::string message);

        /**
         * Reads and advances one position in _input, including whitespaces.
         * Read character is pushed back to _char_buf.
         * Updates _loc, honouring CRLF.
         * @return - scanned char
         */
        char get_char();

        /**
         * Returns the character that is currently processed.
         * @return - currently processed character
         */
        char current();

        /**
         * Peeks n characters after the current from the _input without advancing.
         * Peeking more than 1 characters might be slowed down due to std::istream.peek() limitations.
         * @param n - index of the following character (n >= 0, 0 - current character)
         * @return - string that contains n characters after current
         */
        std::string get_after(int n = 1);

        /**
         * Rolls one character back in the _input.
         * Updates _loc and _char_buf, resets _ch to '\0'.
         */
        void unget_char();

        /**
         * Skips whitespaces, calls unget_char() after first non-whitespace met.
         * Whitespaces according to C# standard (Unicode chars omitted):
         * - Unicode class Zs:
         *      * Space                             ' '   (U+0020)
         * - Horizontal tab character               '\t'  (U+0009)
         * - Vertical tab character                 '\v'  (U+000B)
         * - Form feed character                    '\f'  (U+000C)
         *
         * Additional characters:
         * - Carriage return (CR)                   '\r'  (U+000D)
         * - Line feed (LF)                         '\n'  (U+000A)
         * - Null                                   '\0'  (U+0000)
         */
        void skip_whitespaces();

        /**
         * Scans comments
         * - Single-line comment                    '// input_character*'
         * - Multi-line comment                     '/asterisk delimited_comment_section*  asterisk+/'
         *
         * @return - comment token
         */
        Token scan_comment();

        /**
         * Extract decimal or hexadecimal number from _input.
         * Auxilary method used in scan_integer_literal() and scan_real_literal()
         * @param os - output stream to put number to
         * @param hex - is set if scanning hexadecimal
         */
        void extract_number(std::ostream &os, bool hex = false);

        /**
         * Scans integer literals
         *
         * integer_literal ::=
         *      decimal_integer_literal
         *      hexadecimal_integer_literal
         *
         * decimal_integer_literal ::= decimal_digit+ integer_type_suffix?
         *
         * decimal_digit ::= [0-9]
         *
         * integer_type_suffic ::= U | u | L | l | UL | Ul | uL | ul | LU | Lu | lU | lu
         *
         * hexadecimal_integer_literal ::= ('0x' | '0X') hex_digit+ integer_type_suffix?
         *
         * hex_digit ::= [0-9] | [A-F] | [a-f]
         *
         * @return Integer literal token
         */
        Token scan_integer_literal();

        /**
         * Scans real literals. Warning: the correctness of scanning these literals is not guaranteed yet.
         *
         * real_literal ::=
         *      decimal_digit+ '.' decimal_digit+ exponent_part? real_type_suffix?
         *      .decimal_digit+ exponent_part? real_type_suffix?
         *      decimal_digit+ exponent_part real_type_suffix?
         *      decimal_digit+ real_type_suffix
         *
         * exponent_part ::= ('e' | 'E') sign? decimal_digit+
         *
         * real_type_suffix ::= F | f | D | d | M | m
         *
         * @return Real literal token
         */
        Token scan_real_literal();

        /**
         * Scans character literal. Warning: the full specification of character scanning isn't implemented yet.
         *
         * character_literal ::= ' character '
         * character ::=
         *      single_character
         *      simple_escape_sequence
         *      hexadecimal_escape_sequence
         *      unicode_escape_sequence
         *
         * single_character ::=
         *      any character except:   apostrophe (U+0027)
         *                              backslash (U+005C)
         *                              new_line_character: (U+000D), (U+000A), (U+0085)
         *
         * simple_escape_sequence ::= \'  \"  \\  \0  \a  \b  \f  \n  \r  \t  \v
         *
         * hexadecimal_escape_sequence ::= \x hex_digit hex_digit? hex_digit? hex_digit?
         *
         * unicode_escape_sequence ::=
         *      \u hex_digit hex_digit hex_digit hex_digit
         *      \U hex_digit hex_digit hex_digit hex_digit hex_digit hex_digit hex_digit hex_digit
         *
         * @return Character literal token
         */
        Token scan_character_literal();

        /**
         * Scans string literal
         *
         * string_literal ::=
         *      regular_string_literal ::= " regular_string_character* "
         *      verbatim_string_literal ::= @" verbatim_string_literal_character* "
         *              verbatim_string_literal_character :: = any character except " or quote escape sequence ""
         *
         * @return String literal token
         */
        Token scan_string_literal();

        /**
         * Scans identifiers
         *
         * identifier ::=
         *      available_identifier ::= an identifier_or_keyword that is not keyword
         *      @ identifier_or_keyword ::= identifier_start_character (_ or letter) identifier_part_character* ()
         *
         * identifier_part_character ::=
         *      letter_character
         *      decimal_digit_character
         *      connecting_character
         *      combining_character
         *      formatting_character
         *
         * @return Identifier token
         */
        Token scan_identifier();
    };

}

#endif //CSHARPMETRICS_CSLEXER_H
