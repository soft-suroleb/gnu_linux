#include <check.h>
#include "../src/buf.h"

int *a;
long *ai;

#tcase Initialization
#test capacity_init
    a = 0;
    ck_assert_int_eq(buf_capacity(a), 0);

#test size_init
    ck_assert_int_eq(buf_size(a), 0);

#test size_1
    buf_push(a, 3);
    ck_assert_int_eq(buf_size(a), 1);

#test value
    buf_push(a, 3);
    ck_assert_int_eq(a[0], 3);

#test buffer_clear
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);

#test clear_not_free
    buf_push(a, 3);
    buf_clear(a);
    ck_assert_ptr_ne(a, NULL);

#test buffer_free
    buf_push(a, 3);
    buf_free(a);
    ck_assert_ptr_eq(a, NULL);

#tcase Some
#test clear_empty
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);

#test clear_no_op
    ck_assert_ptr_eq(a, NULL);

#test size_10000
    for(int i = 0; i < 10000; i++) {
        buf_push(ai, i);
    }

    ck_assert_int_eq(buf_size(ai), 10000);

#test match_10000
    int match = 0;
    buf_free(a);
    for(int i = 0; i < 10000; i++) {
        buf_push(ai, i);
    }
    for(int i = 0; i < (int)(buf_size(ai)); i++) {
        match += ai[i] == i;
    }
    ck_assert_int_eq(match, 10000);
    buf_free(ai);

#test grow_1000
    buf_grow(ai, 1000);
    ck_assert_int_eq(buf_capacity(ai), 1000);

#test size_0_grow
    ck_assert_int_eq(buf_size(ai), 0);

#test trunc_100
    buf_trunc(ai, 100);
    ck_assert_int_eq(buf_capacity(ai), 100);
    buf_free(ai);

#test buf_pop_test
    buf_push(a, 1);
    buf_push(a, 2);
    buf_push(a, 3);
    buf_push(a, 4);
    ck_assert_int_eq(buf_size(a), 4);
    ck_assert_int_eq(buf_pop(a), 4);
    buf_trunc(a, 3);
    ck_assert_int_eq(buf_size(a), 3);
    ck_assert_int_eq(buf_pop(a), 3);
    ck_assert_int_eq(buf_pop(a), 2);
    ck_assert_int_eq(buf_pop(a), 1);
    ck_assert_int_eq(buf_size(a), 0);
    buf_free(a);
