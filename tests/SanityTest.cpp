#include <unittest++/UnitTest++.h>

/*
 * This test suite tests for basic assumptions
 * as a "just-in-case" this changes
 */
SUITE(SanityTests)
{

	TEST(Bools) {
		// You never know
		CHECK_EQUAL(true, 1);
		CHECK_EQUAL(false, 0);
	}
}
