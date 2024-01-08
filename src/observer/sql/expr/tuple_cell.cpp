/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/util.h"
#include "util/typecast.h"

void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
    case INTS: {
      os << *(int *)data_;
    } break;
    case FLOATS: {
      float v = *(float *)data_;
      os << double2string(v);
    } break;
    case CHARS: {
      for (int i = 0; i < length_; i++) {
        if (data_[i] == '\0') {
          break;
        }
        os << data_[i];
      }
    } break;
    case DATE: {
      int data = *(int *)data_;
      int y = data / 10000;
      int m = (data % 10000) / 100;
      int d = data % 100;
      std::string y_zero = y < 10 ? "000" : (y < 100 ? "00" : (y < 1000 ? "0" : ""));
      std::string m_zero = m < 10 ? "0" : "";
      std::string d_zero = d < 10 ? "0" : "";
      os << y_zero << y << "-" << m_zero << m << "-" << d_zero << d;
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
}

int TupleCell::compare(const TupleCell &other) const
{
  assert(this->attr_type_ == other.attr_type_);
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS:
      case DATE:
        return compare_int(this->data_, other.data_);
      case FLOATS:
        return compare_float(this->data_, other.data_);
      case CHARS:
        return compare_string(this->data_, this->length_, other.data_, other.length_);
      case NULLS:
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = *(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    return compare_float(data_, &other_data);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}
const TupleCell TupleCell::add(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  if (left.attr_type_ == INTS && right.attr_type_ == INTS) {
    int result = (*(int *)left.data_) + (*(int *)right.data_);
    int *result_data = new int(result);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(INTS);
  } else {
    TypeCast *left_typeCast = new TypeCast(left.attr_type_, AttrType::FLOATS);
    TypeCast *right_typeCast = new TypeCast(right.attr_type_, AttrType::FLOATS);
    float *tmp_left = (float *)left_typeCast->cast(left.data_);
    float *tmp_right = (float *)right_typeCast->cast(right.data_);
    assert(nullptr != tmp_left);
    assert(nullptr != tmp_right);
    float *result_data = new float((*tmp_left) + (*tmp_right));
    result_cell.set_data((char *)result_data);
    result_cell.set_type(FLOATS);
    delete tmp_left;
    delete tmp_right;
  }
  return result_cell;
}
const TupleCell TupleCell::sub(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  if (left.attr_type_ == INTS && right.attr_type_ == INTS) {
    int result = (*(int *)left.data_) - (*(int *)right.data_);
    int *result_data = new int(result);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(INTS);
  } else {
    TypeCast *left_typeCast = new TypeCast(left.attr_type_, AttrType::FLOATS);
    TypeCast *right_typeCast = new TypeCast(right.attr_type_, AttrType::FLOATS);
    float *tmp_left = (float *)left_typeCast->cast(left.data_);
    float *tmp_right = (float *)right_typeCast->cast(right.data_);
    assert(nullptr != tmp_left);
    assert(nullptr != tmp_right);
    float *result_data = new float((*tmp_left) - (*tmp_right));
    result_cell.set_data((char *)result_data);
    result_cell.set_type(FLOATS);
    delete tmp_left;
    delete tmp_right;
  }
  return result_cell;
}
const TupleCell TupleCell::mul(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  if (left.attr_type_ == INTS && right.attr_type_ == INTS) {
    int result = (*(int *)left.data_) * (*(int *)right.data_);
    int *result_data = new int(result);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(INTS);
  } else {
    TypeCast *left_typeCast = new TypeCast(left.attr_type_, AttrType::FLOATS);
    TypeCast *right_typeCast = new TypeCast(right.attr_type_, AttrType::FLOATS);
    float *tmp_left = (float *)left_typeCast->cast(left.data_);
    float *tmp_right = (float *)right_typeCast->cast(right.data_);
    assert(nullptr != tmp_left);
    assert(nullptr != tmp_right);
    float *result_data = new float((*tmp_left) * (*tmp_right));
    result_cell.set_data((char *)result_data);
    result_cell.set_type(FLOATS);
    delete tmp_left;
    delete tmp_right;
  }
  return result_cell;
}
const TupleCell TupleCell::div(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  // 处理除数为0的情况
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  if (right.attr_type_ == INTS && *(int *)right.data_ == 0) {
    result_cell.set_type(NULLS);
    return result_cell;
  }
  // 处理除数为0的情况
  if (right.attr_type_ == FLOATS && *(float *)right.data_ == 0) {
    result_cell.set_type(NULLS);
    return result_cell;
  }
  TypeCast *left_typeCast = new TypeCast(left.attr_type_, AttrType::FLOATS);
  TypeCast *right_typeCast = new TypeCast(right.attr_type_, AttrType::FLOATS);
  float *tmp_left = (float *)left_typeCast->cast(left.data_);
  float *tmp_right = (float *)right_typeCast->cast(right.data_);
  assert(nullptr != tmp_left);
  assert(nullptr != tmp_right);
  float *result_data = new float((*tmp_left) / (*tmp_right));
  result_cell.set_data((char *)result_data);
  result_cell.set_type(FLOATS);
  delete tmp_left;
  delete tmp_right;
  return result_cell;
}
