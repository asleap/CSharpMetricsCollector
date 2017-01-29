//
// Created by Timofey Lyssenko on 29.01.2017.
//

#include <gtest/gtest.h>

#include <CSScanner.hpp>
#include <CSParser.hh>
#include <c++/memory>
#include <c++/fstream>

class ParserTests : public ::testing::Test {
public:
    virtual ~ParserTests() {}

protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
        delete scanner;
        delete parser;
        delete driver;
    }

    Metrics::CSScanner *scanner = nullptr;
    Metrics::CSParser *parser = nullptr;
    Metrics::CSMetricsDriver *driver = nullptr;
};

TEST_F(ParserTests, ParseSingleLineComment) {
    std::string from_source = "HelloWorld";
    std::istringstream source_stream(from_source);
    scanner = new Metrics::CSScanner(&source_stream);
    driver = new Metrics::CSMetricsDriver();
    parser = new Metrics::CSParser((*scanner), (*driver));


}
