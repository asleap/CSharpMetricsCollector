//
// Created by asleap on 22.10.2016.
//

#include <gtest/gtest.h>
#include <MetricsDriver.hpp>

class MetricsDriverTests : public ::testing::Test {
public:
    virtual ~MetricsDriverTests() {}

protected:
    virtual void SetUp() {
        md = new Metrics::MetricsDriver();
    }

    virtual void TearDown() {
        delete md;
    }

    Metrics::MetricsDriver *md;
};

TEST_F(MetricsDriverTests, CtorOK) {
    EXPECT_NE(md, nullptr);
}