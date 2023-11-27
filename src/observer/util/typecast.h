//
// Created by tanyuzhen on 23-11-27.
//

#ifndef MINIDB_TYPECAST_H
#define MINIDB_TYPECAST_H

#endif  // MINIDB_TYPECAST_H

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "sql/parser/parse_defs.h"

class TypeCast {
public:
  AttrType oldType;
  AttrType newType;

  TypeCast(AttrType old_t, AttrType new_t)
  {
    oldType = old_t;
    newType = new_t;
  }

  void *cast(void *data);
  void *int_to_char(void *data);
  void *int_to_float(void *data);
  void *float_to_int(void *data);
  void *float_to_char(void *data);
  void *char_to_int(void *data);
  void *char_to_float(void *data);
};