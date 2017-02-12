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
#include "Token.hpp"
#include "generated/CSParser.hh"
//#include <CSParser.hh>

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

    void pushBackToken(const Metrics::Token &token);

    std::vector<Metrics::Token> &getTokens();

    friend std::ostream &operator<<(std::ostream &os, const MetricsDriver &driver);

private:
    std::vector<Metrics::Token> tokens;
    Metrics::CSParser *parser = nullptr;
    Metrics::CSScanner *scanner = nullptr;

    void parse_helper(std::istream &stream);
};

} // end namespace Metrics


#endif //CSHARPMETRICS_METRICSDRIVER_H
