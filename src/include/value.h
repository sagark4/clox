#ifndef VALUE_H
#define VALUE_H

#include "common.h"

typedef double Value;

typedef struct {
  int count;
  int capacity;
  Value *values;
} ValueArray;

void init_val_arr(ValueArray *);
void push_value(ValueArray *, Value);
Value pop_value(ValueArray *);
void delete_val_arr(ValueArray *);

#endif  // VALUE_H
