#include "gtest/gtest.h"

#include <memory>
#include "MersenneTwisterRngEngine.h"

class MersenneTwisterFixture : public ::testing::Test {
 protected:
    virtual void SetUp() override {
        _p = std::make_shared<MtEngine::MersenneTwisterRngEngine>();
    }

    virtual void TearDown() override {}

    std::shared_ptr<Rng::IRandomNumberGenerator> _p;
};

TEST_F(MersenneTwisterFixture, RandomNumberGeneration) {
	const int64_t MIN = -5;
	const int64_t MAX = 10;

	EXPECT_GE(_p->generateRandomNumber(MIN,MAX), MIN);
	EXPECT_LE(_p->generateRandomNumber(MIN,MAX), MAX);
}
