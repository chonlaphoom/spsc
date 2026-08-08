#include <stdlib.h>

#include "../../munit/munit.h"
#include "intStack.h"

#define MUNIT_ENABLE_ASSERT_ALIASES

static void *test_setup(const MunitParameter params[], void *user_data) {
  (void)params;
  (void)user_data;
  IntStack *s = (IntStack *)malloc(sizeof(IntStack));
  stack_init(s);
  return s;
}
static void test_tear_down(void *fixture) {
  IntStack *s = (IntStack *)fixture;
  if (s->data != NULL) {
    free(s->data);
  }
  free(fixture);
}

static MunitResult basic_push_pop(const MunitParameter params[],
                                  void *fixture) {
  (void)params;
  IntStack *s = (IntStack *)fixture;

  int rc;
  int value;

  rc = stack_push(s, 10);
  munit_assert_int(rc, ==, 0);
  rc = stack_push(s, 20);
  munit_assert_int(rc, ==, 0);
  rc = stack_pop(s, &value);
  munit_assert_int(rc, ==, 0);
  munit_assert_int(value, ==, 20);
  rc = stack_pop(s, &value);
  munit_assert_int(rc, ==, 0);
  munit_assert_int(value, ==, 10);
  munit_assert_int(stack_is_empty(s), ==, 1);

  return MUNIT_OK;
}

MunitResult test_peek(const MunitParameter params[], void *fixture) {
  (void)params;
  IntStack *s = (IntStack *)fixture;

  int rc;
  int value;

  rc = stack_push(s, 5);
  munit_assert_int(rc, ==, 0);
  rc = stack_peek(s, &value);
  munit_assert_int(rc, ==, 0);
  munit_assert_int(value, ==, 5);
  munit_assert_int(stack_is_empty(s), ==, 0);

  return MUNIT_OK;
}

MunitResult test_underflow_and_empty_submit(const MunitParameter params[],
                                            void *fixture) {
  (void)params;
  IntStack *s = (IntStack *)fixture;
  int rc;
  int value = 12345;

  rc = stack_pop(s, &value);
  munit_assert_int(rc, ==, -1);
  rc = stack_peek(s, &value);
  munit_assert_int(rc, ==, -1);
  munit_assert_int(stack_is_empty(s), ==, 1);

  return MUNIT_OK;
}

MunitResult test_dynamic_growth(const MunitParameter params[], void *fixture) {
  (void)params;
  IntStack *s = (IntStack *)fixture;
  int rc;
  int value;

  rc = stack_push(s, 1);
  munit_assert_int(rc, ==, 0);
  rc = stack_push(s, 2);
  munit_assert_int(rc, ==, 0);
  rc = stack_push(s, 3);
  munit_assert_int(rc, ==, 0);
  rc = stack_push(s, 4);
  munit_assert_int(rc, ==, 0);
  rc = stack_push(s, 5);
  munit_assert_int(rc, ==, 0);
  rc = stack_pop(s, &value);
  munit_assert_int(rc, ==, 0);
  munit_assert_int(value, ==, 5);
  rc = stack_pop(s, &value);
  munit_assert_int(rc, ==, 0);
  munit_assert_int(value, ==, 4);

  return MUNIT_OK;
}

int main(int argc, char *const argv[]) {
  const MunitSuite suite = {
      (char *)"/intStack",
      (MunitTest[]){{"/basic_push_pop", basic_push_pop, test_setup,
                     test_tear_down, MUNIT_TEST_OPTION_NONE, NULL},
                    {"/peek", test_peek, test_setup, test_tear_down,
                     MUNIT_TEST_OPTION_NONE, NULL},
                    {"/underflow_and_empty", test_underflow_and_empty_submit,
                     test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL},
                    {"/dynamic_growth", test_dynamic_growth, test_setup,
                     test_tear_down, MUNIT_TEST_OPTION_NONE, NULL},
                    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}},
      NULL, 1, MUNIT_SUITE_OPTION_NONE};

  return munit_suite_main(&suite, NULL, argc, argv);
}
