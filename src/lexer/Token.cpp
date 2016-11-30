//
// Created by asleap on 08.11.2016.
//

#include "Token.hpp"


CSMetrics::Token::Token(const CSMetrics::span &_span, const std::string &_attribute, CSMetrics::Token::Type _type)
    : _span(_span), _attribute(_attribute), _type(_type) {}

const CSMetrics::span &CSMetrics::Token::get_span() const {
    return _span;
}

const std::string &CSMetrics::Token::get_attribute() const {
    return _attribute;
}

CSMetrics::Token::Type CSMetrics::Token::get_type() const {
    return _type;
}
