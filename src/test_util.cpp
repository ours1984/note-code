#include "test_util.h"
#include <iostream>

using namespace std;

void TestUtil::SetUpTestCase()
{
    cout << "SetUpTestCase" << endl;
}

void TestUtil::TearDownTestCase()
{
    cout << "TearDownTestCase" << endl;
}

void TestUtil::SetUp() // TEST跑之前会执行SetUp
{
    cout << "SetUp" << endl;
}

void TestUtil::TearDown() // TEST跑完之后会执行TearDown
{
    cout << "TearDown" << endl;
}

void GlobalTest::SetUp()
{

}

void GlobalTest::TearDown()
{

}

