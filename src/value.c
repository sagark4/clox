#include "include/value.h"

#include "include/dyn_arr.h"

INIT_DYN_ARR_FUN(init_val_arr, ValueArray, Value, count, capacity, values)
PUSH_DYN_ARR_FUN(push_value, ValueArray, Value, count, capacity, values)
POP_DYN_ARR_FUN(pop_value, ValueArray, Value, count, capacity, values)
DELETE_DYN_ARR_FUN(delete_val_arr, ValueArray, Value, count, capacity, values)
