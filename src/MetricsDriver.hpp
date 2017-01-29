//
// Created by Timofey Lysenko on 05.10.16.
//

#ifndef CSHARPMETRICS_METRICSDRIVER_HPP
#define CSHARPMETRICS_METRICSDRIVER_HPP 1

#include <string>
#include <cstddef>
#include <istream>
#include <ostream>

#include "flex/CSScanner.hpp"
#include <CSParser.hh>

namespace Metrics {

class MetricsDriver {
public:
    MetricsDriver() = default;
    virtual ~MetricsDriver();

    /**
     * parse - parse from a file
     * @param filename - valid string with input file
     */
    void parse(const char *const filename);

    /**
     * parse - parse from a c++ input stream
     * @param stream - valid input stream
     */
    void parse(std::istream &stream);

    void add_upper();
    void add_lower();
    void add_word(const std::string &word);
    void add_newline();
    void add_char();

    size_t getChars() const {
        return chars;
    }
    size_t getWords() const {
        return words;
    }
    size_t getLines() const {
        return lines;
    }
    size_t getUppercase() const {
        return uppercase;
    }
    size_t getLowercase() const {
        return lowercase;
    }

private:
    void parse_helper(std::istream &stream);

    std::size_t chars = 0;
    std::size_t words = 0;
    std::size_t lines = 0;
    std::size_t uppercase = 0;
    std::size_t lowercase = 0;

    Metrics::CSParser *parser = nullptr;
    Metrics::CSScanner *scanner = nullptr;
};


std::ostream &operator<<(std::ostream &os, const MetricsDriver &driver);

} // end namespace Metrics


#endif //CSHARPMETRICS_METRICSDRIVER_H
