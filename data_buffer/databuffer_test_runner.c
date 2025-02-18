#include <data_buffer.h>
#include <unity.h>

void setUp(void) { dbuf_clear(); }

void tearDown(void) {
  // clean stuff up here
}

void test_initial_state_should_be_empty(void) {
  TEST_ASSERT_EQUAL_INT(0, dbuf_record_count());
  TEST_ASSERT_TRUE(dbuf_current_wr_slot() == dbuf_current_rd_slot());
}

void test_push_record_should_inc_record_count(void) {
  size_t org_count = dbuf_record_count();
  dbuf_push_record();
  TEST_ASSERT_EQUAL_INT(1, dbuf_record_count() - org_count);
}

void test_pop_record_bundle_should_dec_record_count(void) {
  size_t org_count = dbuf_record_count();
  for (int i = DBUF_BUNDLE_LENGTH; i; i--)
    dbuf_push_record();
  TEST_ASSERT_EQUAL_INT(DBUF_BUNDLE_LENGTH, dbuf_record_count() - org_count);
  dbuf_pop_record_bundle();
  TEST_ASSERT_EQUAL_INT(0, dbuf_record_count() - org_count);
}

void test_bundle_available_should_return_false_when_not_enough_records(void) {
  size_t org_count = dbuf_record_count();
  for (int i = DBUF_BUNDLE_LENGTH - 1; i; i--)
    dbuf_push_record();
  TEST_ASSERT_FALSE(dbuf_bundle_available());
}

void test_bundle_available_should_return_true_when_enough_records(void) {
  size_t org_count = dbuf_record_count();
  for (int i = DBUF_BUNDLE_LENGTH; i; i--)
    dbuf_push_record();
  TEST_ASSERT_TRUE(dbuf_bundle_available());
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_initial_state_should_be_empty);
  RUN_TEST(test_push_record_should_inc_record_count);
  RUN_TEST(test_pop_record_bundle_should_dec_record_count);
  RUN_TEST(test_bundle_available_should_return_false_when_not_enough_records);
  RUN_TEST(test_bundle_available_should_return_true_when_enough_records);
  return UNITY_END();
}
