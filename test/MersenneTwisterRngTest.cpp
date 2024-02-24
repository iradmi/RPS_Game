#include "gtest/gtest.h"

#include <memory>
#include "MersenneTwisterRngEngine.h"

class MersenneTwisterFixture : public ::testing::Test {
 protected:
    virtual void SetUp() override {
        static_assert(Rng::EngineC<MtEngine::MersenneTwisterRngEngine>);
    }

    virtual void TearDown() override {}

    MtEngine::MersenneTwisterRngEngine _p;
};

TEST_F(MersenneTwisterFixture, RandomNumberGeneration) {
    const int64_t MIN = -5;
    const int64_t MAX = 10;

    EXPECT_GE(_p.generateRandomNumber(MIN,MAX), MIN);
    EXPECT_LE(_p.generateRandomNumber(MIN,MAX), MAX);
}
