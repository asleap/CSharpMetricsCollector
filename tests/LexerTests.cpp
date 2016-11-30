//
// Created by asleap on 07.11.2016.
//

#include <gtest/gtest.h>
#include <Lexer.hpp>
#include <sstream>
#include <fstream>

class LexerTests : public ::testing::Test {
public:
    virtual ~LexerTests() {};

protected:
    virtual void setUp() {
        std::ifstream source_file("Test.cs.txt");
        std::string from_source((std::istreambuf_iterator<char>(source_file)),
                                std::istreambuf_iterator<char>());
        std::istringstream source_stream(from_source);
        lexer = new CSMetrics::Lexer(source_stream);
    }

    virtual void tearDown() {
        delete lexer;
    }

    CSMetrics::Lexer *lexer;
};

TEST_F(LexerTests, RunTest) {
    EXPECT_EQ(1, 1);
}