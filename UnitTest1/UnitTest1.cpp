#include "pch.h"
#include "CppUnitTest.h"
#include "../10.1B/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(4, calc_n(1000));
			Assert::AreEqual(2, calc_n(10));
			Assert::AreEqual(3, calc_n(100));
		}
	};
}
