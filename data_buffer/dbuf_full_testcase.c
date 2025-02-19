#include <data_buffer.h>
#include <unity.h>
#include <unity_fixture.h>

TEST_GROUP(DBufFullTestCase);

TEST_SETUP(DBufFullTestCase) {
  dbuf_clear();
  for (int i = DBUF_BUFFER_LENGTH; i; i--)
    dbuf_push_record();
}

TEST_TEAR_DOWN(DBufFullTestCase) {}

TEST(DBufFullTestCase, available_records_should_return_buffer_length) {
  TEST_ASSERT_EQUAL_INT(DBUF_BUFFER_LENGTH, dbuf_record_count());
}

TEST(DBufFullTestCase, pop_record_bundle_should_dec_available_records_by_4) {
  dbuf_pop_record_bundle();
  TEST_ASSERT_EQUAL_INT(DBUF_BUFFER_LENGTH - 4, dbuf_record_count());
}

TEST(DBufFullTestCase, current_wr_slot_should_return_null) {
  TEST_ASSERT_NULL(dbuf_current_wr_slot());
}

TEST(DBufFullTestCase, current_wr_slot_should_return_not_null_after_pop) {
  dbuf_pop_record_bundle();
  TEST_ASSERT_NOT_NULL(dbuf_current_wr_slot());
  TEST_ASSERT_EQUAL_PTR(dbuf_current_rd_slot() - DBUF_BUNDLE_LENGTH,
                        dbuf_current_wr_slot());
}

TEST(DBufFullTestCase, current_rd_slot_should_wrap_around) {
  for (int i = DBUF_BUFFER_LENGTH - 1; i; i--)
    dbuf_pop_record_bundle();
  TEST_ASSERT_EQUAL_INT(1, dbuf_record_count());
  dbuf_pop_record_bundle();
  TEST_ASSERT_EQUAL_INT(0, dbuf_record_count());
  TEST_ASSERT_EQUAL_PTR(dbuf_current_wr_slot(), dbuf_current_rd_slot());
}

TEST_GROUP_RUNNER(DBufFullTestCase) {
  RUN_TEST_CASE(DBufFullTestCase,
                available_records_should_return_buffer_length);
  RUN_TEST_CASE(DBufFullTestCase,
                pop_record_bundle_should_dec_available_records_by_4);
  RUN_TEST_CASE(DBufFullTestCase, current_wr_slot_should_return_null);
  RUN_TEST_CASE(DBufFullTestCase,
                current_wr_slot_should_return_not_null_after_pop);
}
