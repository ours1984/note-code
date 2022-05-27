#include "test_util.h"

int main(int argc,char *argv[])
{
    testing::InitGoogleTest(&argc,argv);
    auto env = new GlobalTest();
    testing::AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}