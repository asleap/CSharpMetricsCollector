//
// Created by Timofey Lysenko on 05.10.16.
//

#include "MetricsDriver.hpp"

#include <cctype>
#include <fstream>
#include <cassert>

Metrics::MetricsDriver::~MetricsDriver() {
    delete (scanner);
    scanner = nullptr;
    delete (parser);
    parser = nullptr;
}

void Metrics::MetricsDriver::parse(const char *const filename) {
    assert(filename != nullptr);
    std::ifstream in_file(filename);
    if (!in_file.good()) {
        exit(EXIT_FAILURE);
    }
    parse_helper(in_file);
}

void Metrics::MetricsDriver::parse(std::istream &stream) {
    if (!stream.good() || stream.eof()) {
        return;
    }
    parse_helper(stream);
}

void Metrics::MetricsDriver::parse_helper(std::istream &stream) {
    delete (scanner);
    try {
        scanner = new Metrics::CSScanner(&stream);
    }
    catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate parser: " << ba.what() << std::endl << "\t...exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    delete (parser);
    try {
        parser = new Metrics::CSParser((*scanner) /* scanner */, (*this) /* driver */ );
    }
    catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate parser: " << ba.what() << std::endl << "\t...exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    const int accept(0);
    if (parser->parse() != accept) {
        std::cerr << "Parse failed" << std::endl;
    }
}

void Metrics::MetricsDriver::pushBackToken(const Metrics::Token &token) {
    tokens.push_back(token);
}

std::vector<Metrics::Token> &Metrics::MetricsDriver::getTokens() {
    return tokens;
}

std::ostream &Metrics::operator<<(std::ostream &os, const Metrics::MetricsDriver &driver) {
    os << std::endl;
    for (auto&& token : driver.tokens) {
        os << token.getToken();
        os << " ";
        os << token.getLocation();
        os << " ";
        if (!token.getAttribute().empty()) {
            os << token.getAttribute();
            os << " ";
        }
        if (token.getToken() == Metrics::CSParser::token::NEW_LINE) {
            os << std::endl;
        }
    }
    return os;
}