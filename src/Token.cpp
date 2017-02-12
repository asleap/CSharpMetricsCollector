//
// Created by Timofey Lyssenko on 12.02.2017.
//

#include "Token.hpp"

Metrics::Token::Token(Metrics::CSParser::token_type token,
                      const Metrics::CSParser::location_type location,
                      const std::string &attribute)
        : _token(token), _location(location), _attribute(attribute) {}

Metrics::CSParser::token_type Metrics::Token::getToken() const {
    return _token;
}

const Metrics::CSParser::location_type &Metrics::Token::getLocation() const {
    return _location;
}

const std::string &Metrics::Token::getAttribute() const {
    return _attribute;
}

