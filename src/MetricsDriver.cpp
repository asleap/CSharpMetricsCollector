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

void Metrics::MetricsDriver::add_upper() {
    uppercase++;
    chars++;
    words++;
}

void Metrics::MetricsDriver::add_lower() {
    lowercase++;
    chars++;
    words++;
}

void Metrics::MetricsDriver::add_word(const std::string &word) {
    words++;
    chars += word.length();
    for (const char &c : word) {
        if (islower(c)) {
            lowercase++;
        } else if (isupper(c)) {
            uppercase++;
        }
    }
}

void Metrics::MetricsDriver::add_newline() {
    lines++;
    chars++;
}

void Metrics::MetricsDriver::add_char() {
    chars++;
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

std::ostream &Metrics::operator<<(std::ostream &os, const Metrics::MetricsDriver &driver) {
    os << "Results:\n";
    os << "Uppercase: " << driver.getUppercase() << "\n";
    os << "Lowercase: " << driver.getLowercase() << "\n";
    os << "Lines: " << driver.getLines() << "\n";
    os << "Words: " << driver.getWords() << "\n";
    os << "Characters: " << driver.getChars() << "\n";
    return os;
}



