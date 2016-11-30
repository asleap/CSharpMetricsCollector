//
// Created by asleap on 07.11.2016.
//

#ifndef CSHARPMETRICS_CSLEXER_HPP
#define CSHARPMETRICS_CSLEXER_HPP

#include <istream>
#include <iostream>
#include <vector>

#include "Token.hpp"

namespace CSMetrics {

/**
 * Simple lexer implementation.
 * Written in correspondance to langueage standard.
 * However, supports only ASCII characters since
 * weak C++ Unicode support.
 */
class Lexer {
public:

    /**
     * @param input - character stream that represents source code
     */
    Lexer(std::istream& input, size_t number_of_lines = 300);

    void TestFunc() {
        skip_whitespaces();
        Token tok = scan_comment(_loc);
        std::cout << tok.get_attribute() << std::endl;

        skip_whitespaces();
        Token tok2 = scan_comment(_loc);
        std::cout << tok2.get_attribute() << std::endl;

        skip_whitespaces();
        Token tok3 = scan_integer_literal(_loc);
        std::cout << tok3.get_attribute() << std::endl;

        skip_whitespaces();
        Token tok4 = scan_real_literal(_loc);
        std::cout << tok4.get_attribute() << std::endl;
    }

private:
    std::istream&       _input;
    char                _ch;            // Last read character
    location            _loc;           // Current location in source
    std::vector<int>    _chars_in_line; // Stores number of chars in a given line

    /**
     * Returns a single character from the source stream.
     * Updates _loc, taking into consideration CRLF.
     * @return - scanned char, including whitespaces
     */
    char get_char();

    /**
     * Moves one character back in the source stream.
     * Updates _loc.
     * @return - read character
     */
    void unget_char();

    /**
     * Skips whitespaces.
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
     *
     * @return scanned character
     */
    char skip_whitespaces();

    /**
     * Scans comments
     * - Single-line comment                    '// input_character*'
     * - Multi-line comment                     '/asterisk delimited_comment_section*  asterisk+/'
     *
     * @param position - current _loc
     * @return Comment token
     */
    Token scan_comment(location position);

    /**
     * Extract decimal or hexadecimal number from _input.
     * Auxilary method used in scan_integer_literal() and scan_real_literal
     * @param os - output stream to put number to
     * @param hex - set if scanning hexadecimal
     * @return - true if lexeme was extracted
     */
    void extract_number(std::ostream& os, bool hex = false);

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
     * @param position - current _loc
     * @return Integer literal token
     */
    Token scan_integer_literal(location position);

    /**
     * Scans real literals
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
     * @param position - current _loc
     * @return Real literal token
     */
    Token scan_real_literal(location position);
};

}

#endif //CSHARPMETRICS_CSLEXER_H
