#include <check.h>
#include "../lib/libgame.h"

#test dummy
    ck_assert_ptr_ne(result, NULL);
    ck_assert_ptr_ne(ask, NULL);
    ck_assert_ptr_ne(usage, NULL);
