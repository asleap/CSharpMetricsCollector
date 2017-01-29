//
// Created by asleap on 07.11.2016.
//

#include "Lexer.hpp"

#include <string>
#include <stdexcept>
#include <sstream>

CSMetrics::Lexer::Lexer(std::istream &input, size_t number_of_lines)
        : _input(input), _loc(location(1, 1)) {
    _chars_in_line.reserve(number_of_lines);
}

void CSMetrics::Lexer::scanning_error(std::string message) {
    std::cerr << message << ", _loc:" << _loc.lineno << ":" << _loc.charno << std::endl;
    throw std::runtime_error(message + ", _loc:" + std::to_string(_loc.lineno) + ":" + std::to_string(_loc.charno));
}

char CSMetrics::Lexer::get_char() {
//    if (_input.good()) {
//        _input.get(_ch);
//    } else {
//        _ch = '\0';
//    }

    _input.get(_ch);
    if(!_input.good()) {
        _ch = '\0';
    }

    if (_ch == '\n') {
        _loc.lineno++;
        _chars_in_line.push_back(_loc.charno + 1);
        _loc.charno = 1;
    } else if (_ch != '\0') {
        _loc.charno++;
    }

    return _ch;
}

char CSMetrics::Lexer::current() {
    return _ch;
}

std::string CSMetrics::Lexer::get_after(int n) {
    if (n < 0) {
        std::cerr << "n = " << n << ", n < 0" << std::endl;
        throw std::invalid_argument("n = " + std::to_string(n) + ", n < 0");
    } else if (n == 0) {
        return std::string(1, _ch);
    } else if (n == 1) {
        return std::string(1, static_cast<char>(_input.peek()));
    } else {
        char *chars = new char[n];
        std::streampos current_pos = _input.tellg();
        _input.get(chars, n + 1);
        _input.seekg(current_pos);
        return std::string(chars);
    }
}

void CSMetrics::Lexer::unget_char() {
    if (_loc.charno == 1 && _loc.lineno == 1) {
        return;
    }

    if (_ch == '\0') {
        return;
    }

    if (_loc.charno > 1) {
        _loc.charno--;
    } else if (_loc.charno == 1 && _loc.lineno > 1) {
        _loc.lineno--;
        _loc.charno = _chars_in_line[_loc.lineno - 1] - 1;
    }

    _ch = '\0';
    _input.unget();
}

void CSMetrics::Lexer::skip_whitespaces() {
    while (true) {
        get_char();

        switch (current()) {
            case '\0':
                std::cerr << "Met eos/eof, _loc:" << _loc.lineno << ":" << _loc.charno << std::endl;
                return;

            case ' ':
            case '\t':
            case '\v':
            case '\f':
            case '\r':
            case '\n':
                continue;

            default:
                unget_char();
                return;
        }
    }
}

CSMetrics::Token CSMetrics::Lexer::scan_comment() {
    location start_loc = _loc;
    std::ostringstream comment;

    comment << get_char();

    if (current() == '/') {
        // Handle one line comment
        while (true) {
            get_char();
            comment << current();
            if (get_after()[0] == '\n' || !_input.good()) {
                break;
            }
        }
    } else if (current() == '*') {
        // Handle multi line comment
        while (true) {
            get_char();
            comment << current();

            if (current() == '*' && get_after()[0] == '/') {
                comment << current();
                comment << get_char();
                break;
            }
        }
    } else {
        // Not a comment
        unget_char();
        scanning_error("Scanning not a comment");
    }

    return Token(span(start_loc, _loc), comment.str(), Token::COMMENT);
}

void CSMetrics::Lexer::extract_number(std::ostream &os, bool hex) {
    while (true) {
        get_char();
        if (std::isdigit(current()))
            // Scan decimal
            os << current();
        else if (hex && std::tolower(current()) >= 'a' && std::tolower(current()) <= 'f')
            // Scan hexadecimal right after ('0x' | '0X')
            os << current();
        else {
            unget_char();
            break;
        }
    }
}

CSMetrics::Token CSMetrics::Lexer::scan_integer_literal() {
    int lookahead = get_after()[0];
    if (!std::isdigit(lookahead)) {
        // Not an integer
        scanning_error("Scanning not an integer");
    }

    location start_loc = _loc;
    std::ostringstream literal;

    get_char();
    if (current() == '0') {
        literal << current();
        if (std::tolower(get_after()[0]) == 'x') {
            // Scan hexadecimal integer literal
            literal << get_char();  // ('0x' | '0X')
            extract_number(literal, true);
        } else {
            // Scan decimal integer literal
            extract_number(literal);
        }
    } else {
        // Starts without 0
        literal << current();
        extract_number(literal);
    }

    // Scan type suffix
    if (std::tolower(get_after()[0]) == 'u') {
        literal << get_char();
        if (std::tolower(get_after()[0]) == 'l') {
            literal << get_char();
        }
    } else if (std::tolower(get_after()[0]) == 'l') {
        literal << get_char();
        if (std::tolower(get_after()[0]) == 'u') {
            literal << get_char();
        }
    }

    return Token(span(start_loc, _loc), literal.str(), Token::INTEGER_LITERAL);
}

CSMetrics::Token CSMetrics::Lexer::scan_real_literal() {
    int lookahead = get_after()[0];
    if (!std::isdigit(lookahead) && lookahead != '.') {
        // Not a real
        scanning_error("Scanning not a real");
    }

    location start_loc = _loc;
    std::ostringstream literal;

    // Scan decimal part
    extract_number(literal);

    // Try to extract '.'
    if (get_after()[0] == '.') {
        literal << get_char();

        // Scan decimal
        extract_number(literal);

        // Scan possible exponent part
        if (std::tolower(get_after()[0]) == 'e') {
            literal << get_char();

            // Scan possible sign
            lookahead = get_after()[0];
            if (lookahead == '-' || lookahead == '+')
                literal << get_char();

            // Scan decimal
            extract_number(literal);
        }
    }

    // Scan possible real type suffix
    lookahead = std::tolower(get_after()[0]);
    if (lookahead == 'f' || lookahead == 'd' || lookahead == 'm') {
        literal << get_char();
    }

    return Token(span(start_loc, _loc), literal.str(), Token::REAL_LITERAL);
}

CSMetrics::Token CSMetrics::Lexer::scan_character_literal() {
    if (get_after()[0] != '\'') {
        // Not a character
        scanning_error("Scanning not a character");
    }

    location start_loc = _loc;
    std::ostringstream literal;
    literal << get_char(); // Opening quote

    // Scanning character
    bool scanning = true;
    while(scanning) {
        get_char();

        switch (current()) {
            case '\\':
                if (get_after()[0] != '\'') {
                    literal << current();
                    break;
                } else {
                    scanning = false;
                    unget_char();
                    scanning_error("Scanning not a character");
                    break;
                }

            case '\r':
            case '\n':
                scanning = false;
                unget_char();
                scanning_error("Scanning not a character");
                break;

            case '\'':
                scanning = false;
                literal << current(); // Finishing quote
                break;

            default:
                literal << current();
                break;
        }
    }

    return Token(span(start_loc, _loc), literal.str(), Token::CHARACTER_LITERAL);
}

CSMetrics::Token CSMetrics::Lexer::scan_string_literal() {
    int lookahead = get_after()[0];
    if (lookahead != '"' && lookahead != '@') {
        scanning_error("Scanning not a string");
    }

    location start_loc = _loc;
    std::ostringstream literal;
    bool scanning = true;
    bool escaped = false;

    get_char();
    if (current() == '"') {
        literal << current();
    } else {
        literal << current();
        literal << get_char();
    }

    while (scanning) {
        get_char();

        if (current() == '"' && !escaped) {
            scanning = false;
        }

        escaped = current() == '\\';

        literal << current();
    }

    return Token(span(start_loc, _loc), literal.str(), Token::STRING_LITERAL);
}

CSMetrics::Token CSMetrics::Lexer::scan_identifier() {

}
