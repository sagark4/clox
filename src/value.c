#include "include/value.h"

#include <stdlib.h>

void init_val_arr(ValueArray *ptr) {
  ptr->count = 0;
  ptr->capacity = 8;
  void *result = malloc(8 * sizeof(Value));
  if (result == NULL) exit(1);
  ptr->values = ((Value *)result);
}

void push_value(ValueArray *ptr, Value elt) {
  if (ptr->count == ptr->capacity) {
    ptr->values = ((Value *)realloc(ptr->values, 2 * ptr->capacity * sizeof(Value)));
    ptr->capacity *= 2;
  }
  *(ptr->values + ptr->count) = elt;
  ptr->count++;
}

Value pop_value(ValueArray *ptr) { return *(ptr->values + --ptr->count); }

void delete_val_arr(ValueArray *ptr) {
  ptr->count = 0;
  ptr->capacity = 0;
  free(ptr->values);
  ptr->values = NULL;
}

/* INIT_DYN_ARR_FUN(init_val_arr, ValueArray, Value, count, capacity, values) */
/* PUSH_DYN_ARR_FUN(push_value, ValueArray, Value, count, capacity, values) */
/* POP_DYN_ARR_FUN(pop_value, ValueArray, Value, count, capacity, values) */
/* DELETE_DYN_ARR_FUN(delete_val_arr, ValueArray, Value, count, capacity, values) */
