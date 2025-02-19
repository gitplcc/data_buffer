#include <data_buffer.h>
#include <unity.h>
#include <unity_fixture.h>

TEST_GROUP(DBufEmptyTestCase);

TEST_SETUP(DBufEmptyTestCase) { dbuf_clear(); }

TEST_TEAR_DOWN(DBufEmptyTestCase) {}

TEST(DBufEmptyTestCase, initial_state_should_be_empty) {
  TEST_ASSERT_EQUAL_INT(0, dbuf_record_count());
}

TEST(DBufEmptyTestCase, current_wr_slot_should_return_not_null) {
  TEST_ASSERT_NOT_NULL(dbuf_current_wr_slot());
}

TEST(DBufEmptyTestCase, current_rd_slot_should_return_null) {
  TEST_ASSERT_NULL(dbuf_current_rd_slot());
}

TEST(DBufEmptyTestCase, push_record_should_inc_record_count) {
  size_t org_count = dbuf_record_count();
  dbuf_push_record();
  TEST_ASSERT_EQUAL_INT(1, dbuf_record_count() - org_count);
}

TEST(DBufEmptyTestCase, pop_record_bundle_should_dec_record_count) {
  for (int i = DBUF_BUNDLE_LENGTH; i; i--)
    dbuf_push_record();
  size_t org_count = dbuf_record_count();
  for (int i = DBUF_BUNDLE_LENGTH; i; i--)
    dbuf_push_record();
  TEST_ASSERT_EQUAL_PTR(dbuf_current_rd_slot() + 2 * DBUF_BUNDLE_LENGTH,
                        dbuf_current_wr_slot());
  TEST_ASSERT_EQUAL_INT(DBUF_BUNDLE_LENGTH, dbuf_record_count() - org_count);
  dbuf_pop_record_bundle();
  TEST_ASSERT_EQUAL_INT(0, dbuf_record_count() - org_count);
  TEST_ASSERT_EQUAL_PTR(dbuf_current_rd_slot(),
                        dbuf_current_wr_slot() - DBUF_BUNDLE_LENGTH);
}

TEST(DBufEmptyTestCase,
     bundle_available_should_return_false_when_not_enough_records) {
  size_t org_count = dbuf_record_count();
  for (int i = DBUF_BUNDLE_LENGTH - 1; i; i--)
    dbuf_push_record();
  TEST_ASSERT_FALSE(dbuf_bundle_available());
}

TEST(DBufEmptyTestCase,
     current_rd_slot_should_return_null_when_not_enough_records) {
  size_t org_count = dbuf_record_count();
  for (int i = DBUF_BUNDLE_LENGTH - 1; i; i--)
    dbuf_push_record();
  TEST_ASSERT_NULL(dbuf_current_rd_slot());
}

TEST(DBufEmptyTestCase,
     bundle_available_should_return_true_when_enough_records) {
  size_t org_count = dbuf_record_count();
  for (int i = DBUF_BUNDLE_LENGTH; i; i--)
    dbuf_push_record();
  TEST_ASSERT_TRUE(dbuf_bundle_available());
}

TEST_GROUP_RUNNER(DBufEmptyTestCase) {
  RUN_TEST_CASE(DBufEmptyTestCase, initial_state_should_be_empty);
  RUN_TEST_CASE(DBufEmptyTestCase, current_wr_slot_should_return_not_null);
  RUN_TEST_CASE(DBufEmptyTestCase, current_rd_slot_should_return_null);
  RUN_TEST_CASE(DBufEmptyTestCase, push_record_should_inc_record_count);
  RUN_TEST_CASE(DBufEmptyTestCase, pop_record_bundle_should_dec_record_count);
  RUN_TEST_CASE(DBufEmptyTestCase,
                bundle_available_should_return_false_when_not_enough_records);
  RUN_TEST_CASE(DBufEmptyTestCase,
                current_rd_slot_should_return_null_when_not_enough_records);
  RUN_TEST_CASE(DBufEmptyTestCase,
                bundle_available_should_return_true_when_enough_records);
}
