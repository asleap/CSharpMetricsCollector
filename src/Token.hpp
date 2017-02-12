//
// Created by Timofey Lyssenko on 12.02.2017.
//

#ifndef CSHARPMETRICS_TOKEN_HPP
#define CSHARPMETRICS_TOKEN_HPP

#include "generated/CSParser.hh"

namespace Metrics {

/**
 * Token class
 */
class Token {

private:
    Metrics::CSParser::token_type _token;
    Metrics::CSParser::location_type _location;
    std::string _attribute;

public:
    Token(CSParser::token_type token, const CSParser::location_type location,
          const std::string &attribute);

    CSParser::token_type getToken() const;

    const CSParser::location_type &getLocation() const;

    const std::string &getAttribute() const;
};

}

#endif //CSHARPMETRICS_TOKEN_HPP
