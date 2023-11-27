//
// Created by tanyuzhen on 23-11-27.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "util/typecast.h"
#include "common/log/log.h"
#include "util/util.h"

void *TypeCast::cast(void *data)
{
  switch (this->oldType) {
    case INTS: {
      switch (this->newType) {
        case FLOATS: {
          return int_to_float(data);
        }
        case CHARS: {
          return int_to_char(data);
        }
        default: {
          LOG_ERROR("Error cast to the new type");
        } break;
      }
    } break;
    case FLOATS: {
      switch (this->newType) {
        case INTS: {
          return float_to_int(data);
        }
        case CHARS: {
          return float_to_char(data);
        }
        default: {
          LOG_ERROR("Error cast to the new type");
        } break;
      }
    } break;
    case CHARS: {
      switch (this->newType) {
        case INTS: {
          return char_to_int(data);
        }
        case FLOATS: {
          return char_to_float(data);
        }
        default: {
          LOG_ERROR("Error cast to the new type");
        } break;
      }
    } break;
    case DATE:
    case UNDEFINED: {
      LOG_WARN("don't support the type cast");
    } break;
  }
  return nullptr;
}

void *TypeCast::int_to_char(void *data)
{
    std::string s = std::to_string(*(int *)data);
    char *cast_data = new char[s.size() + 1];
    memset(cast_data,0,s.size()+1);
    memcpy(cast_data, s.c_str(), s.size());
    return cast_data;
}

void *TypeCast::int_to_float(void *data)
{
    const int s = *(int *)data;
    float *cast_data = new float(s);
    return cast_data;
}

void *TypeCast::float_to_int(void *data)
{
    const float s = *(float *)data;
    int *cast_data = new int(s + 0.5);  //四舍五入
    return cast_data;
}

void *TypeCast::float_to_char(void *data)
{
    std::string s = double2string(*(float *)data);
    char *cast_data = new char[s.size() + 1];
    memset(cast_data, 0, s.size()+1);
    memcpy(cast_data, s.c_str(), s.size());
    return cast_data;
}

void *TypeCast::char_to_int(void *data)
{
    const char *s = (char *)data;
    // atoi and atof function have already finished string like "12a" cast to 12 or "1.2a" cast to 1.2
    int *cast_data = new int(atoi(s));
    return cast_data;
}

void *TypeCast::char_to_float(void *data)
{
  const char *s = (char *)data;
  float *res = new float(atof(s));
  return res;
}
