#include <check.h>
#include "../src/buf.h"

float *a;

#tcase Initialization
#test capacity_init
    a = 0;
    ck_assert_int_eq(buf_capacity(a), 0);

#test size_init
    a = 0;
    ck_assert_int_eq(buf_size(a), 0);

#test size_1
    buf_push(a, 1.3f);
    ck_assert_int_eq(buf_size(a), 1);

// #test value
//     ck_assert
//     TEST("value", a[0] == (float)1.3f);

#test buffer_clear
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);

#test clear_not_free
    ck_assert_ptr_ne(a, NULL);

#test buffer_free
    buf_free(a);
    ck_assert_ptr_eq(a, NULL);
