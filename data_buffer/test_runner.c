#include <unity_fixture.h>

static void RunAllTests(void)
{
  RUN_TEST_GROUP(DBufEmptyTestCase);
  RUN_TEST_GROUP(DBufFullTestCase);
}

int main(int argc, char* argv[]) {
  return UnityMain(argc, (const char **)argv, RunAllTests);
}
