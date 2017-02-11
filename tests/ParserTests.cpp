//
// Created by Timofey Lyssenko on 29.01.2017.
//

#include <gtest/gtest.h>

#include <CSScanner.hpp>
#include <CSParser.hh>
#include <c++/memory>
#include <c++/fstream>
#include <MetricsDriver.hpp>

class ParserTests : public ::testing::Test {
public:
    virtual ~ParserTests() {}

protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
        delete driver;
    }

    Metrics::MetricsDriver *driver = nullptr;
};

TEST_F(ParserTests, ParseWord) {
    std::string from_source = "Hello World";
    std::istringstream source_stream(from_source);

    driver = new Metrics::MetricsDriver();
    driver->parse(source_stream);

    EXPECT_EQ(driver->getTokens().size(), static_cast<size_t >(3));
    EXPECT_EQ(driver->getTokens()[0], Metrics::CSParser::token::WORD);
    EXPECT_EQ(driver->getTokens()[1], Metrics::CSParser::token::CHAR);
    EXPECT_EQ(driver->getTokens()[2], Metrics::CSParser::token::WORD);
}
