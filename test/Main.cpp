#include <gmock/gmock.h>

#include "RpsGame.h"
#include "MersenneTwisterRngEngine.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
