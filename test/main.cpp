// NeoPixels_TEST.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

