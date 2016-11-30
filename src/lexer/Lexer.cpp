//
// Created by asleap on 07.11.2016.
//

#include "Lexer.hpp"

#include <string>
#include <stdexcept>
#include <sstream>

CSMetrics::Lexer::Lexer(std::istream& input, size_t number_of_lines)
    : _input(input), _loc(location(1, 1)) {
    _chars_in_line.reserve(number_of_lines);
}

char CSMetrics::Lexer::get_char() {
    _input >> std::noskipws >> _ch;

    if (_input.eof()) {
        _ch = '\0';
    }

    if (_ch == '\n') {
        _loc.lineno++;
        _chars_in_line.push_back(_loc.charno + 1);
        _loc.charno = 1;
    } else if (_ch == '\r') {
        char tmp;
        _input >> std::noskipws >> tmp;
        if (tmp != '\n') {
            _loc.lineno++;
            _chars_in_line.push_back(_loc.charno + 1);
            _loc.charno = 1;
        } else {
            _input.unget();
        }
    } else {
        _loc.charno++;
    }

    return _ch;
}

void CSMetrics::Lexer::unget_char() {
    if (_loc.charno == 1 && _loc.lineno == 1)
        return;

    if (_loc.charno > 1)
        _loc.charno--;
    else if (_loc.charno == 1 && _loc.lineno > 1) {
        _loc.lineno--;
        _loc.charno = _chars_in_line[_loc.lineno - 1] - 1;
    }

    _ch = '\0';
    _input.unget();
}

char CSMetrics::Lexer::skip_whitespaces() {
    while (true) {
        char ch = get_char();

        switch (ch) {
            case '\0':
                std::cerr << "Met eos/eof, _loc:" << _loc.lineno << ":" << _loc.charno << std::endl;
                unget_char();
                return ch;

            case ' ':
            case '\t':
            case '\v':
            case '\f':
            case '\r':
            case '\n':
                continue;

            default:
                unget_char();
                return ch;
        }
    }
}

CSMetrics::Token CSMetrics::Lexer::scan_comment(location position) {
    std::ostringstream comment;
    comment << get_char();

    char ch = get_char();
    comment << ch;

    if (ch == '/') {
        // Handle one line comment
        while (true) {
            ch = get_char();

            if (ch == '\r') {
                char tmp = get_char();
                if (tmp != '\n')
                    break;
                else {
                    unget_char();
                    continue;
                }
            }

            if (ch == '\n' || _input.eof())
                break;

            comment << ch;
        }
    } else if (ch == '*') {
        // Handle multi line comment
        bool prev_asterisk = false;

        while (true) {
            ch = get_char();
            comment << ch;

            if (prev_asterisk && ch == '/')
                break;

            if (ch == '*')
                prev_asterisk = true;
        }
    } else {
        // Not a comment
        unget_char();

        throw std::runtime_error("Scanning not a comment, _loc:"
                                     + std::to_string(_loc.lineno)
                                     + ":"
                                     + std::to_string(_loc.charno));
    }

    return Token(span(position, _loc), comment.str(), Token::COMMENT);
}

void CSMetrics::Lexer::extract_number(std::ostream& os, bool hex) {
    while (true) {
        get_char();
        if (_ch >= '0' && _ch <= '9')
            // Scan decimal
            os << _ch;
        else if (hex && ( (_ch >= 'a' && _ch <= 'f') || (_ch >= 'A' && _ch <= 'F')) )
            // Scan hexadecimal right after ('0x' | '0X')
            os << _ch;
        else {
            unget_char();
            break;
        }
    }
}

CSMetrics::Token CSMetrics::Lexer::scan_integer_literal(CSMetrics::location position) {
    std::ostringstream literal;
    char ch = get_char();
    if (ch == '0') {
        literal << ch;
        char tmp = get_char();
        if (tmp == 'x' || tmp == 'X') {
            // Scan hexadecimal integer literal
            literal << tmp;  // ('0x' | '0X')
            extract_number(literal, true);
        } else {
            unget_char(); // Return not 'x' back to the stream
            // Scan decimal integer literal
            extract_number(literal);
        }
    } else {
        // Starts without 0
        unget_char();
        extract_number(literal);
    }

    // Scan type suffix
    ch = get_char();
    if (ch == 'U' || ch == 'u') {
        literal << ch;
        ch = get_char();
        if (ch == 'L' || ch == 'l') {
            literal << ch;
        } else
            unget_char();
    } else if (ch == 'L' || ch == 'l') {
        literal << ch;
        ch = get_char();
        if (ch == 'U' || ch == 'u') {
            literal << ch;
        } else
            unget_char();
    } else
        unget_char();
    return Token(span(position, _loc), literal.str(), Token::INTEGER_LITERAL);
}

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
 * sign ::= '-' | '+'
 *
 * real_type_suffix ::= F | f | D | d | M | m
 */
CSMetrics::Token CSMetrics::Lexer::scan_real_literal(CSMetrics::location position) {
    std::ostringstream literal;

    // Scan decimal
    extract_number(literal);

    // Try to extract '.'
    char ch = get_char();
    if (ch == '.') {
        literal << ch;

        // Scan decimal
        extract_number(literal);

        ch = get_char();

        // Scan possible exponent part
        if (ch == 'e' || ch == 'E') {
            literal << ch;
            // Scan possible sign
            ch = get_char();
            if (ch == '-' || ch == '+')
                literal << ch;
            else
                unget_char();
            // Scan decimal
            extract_number(literal);
            ch = get_char();
        }
    }

    // Scan possible real type suffix
    if (ch == 'F' || ch == 'f' || ch == 'D' || ch == 'd' || ch == 'M' || ch == 'm')
        literal << ch;
    else
        unget_char();

    return Token(span(position, _loc), literal.str(), Token::REAL_LITERAL);
}


