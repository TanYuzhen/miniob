//
// Created by tanyuzhen on 23-11-28.
//
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "storage/record/record.h"
#include "join_operator.h"

RC JoinOperator::open()
{
  RC rc;
  rc = left_->open();
  if (rc != RC::SUCCESS) {
    LOG_ERROR("join operator failed open() left operator\n");
    return rc;
  }
  rc = right_->open();
  if (rc != RC::SUCCESS) {
    LOG_ERROR("join operator failed open() right operator\n");
    return rc;
  }
  Tuple *left_tuple = left_->current_tuple();
  Tuple *right_tuple = right_->current_tuple();
  assert(dynamic_cast<RowTuple *>(right_tuple) != nullptr);
  this->tuple_.init(left_tuple, right_tuple);
  return rc;
}
RC JoinOperator::next()
{
  RC rc;
  if (is_first) {
    // get the one tuple of left operator;
    is_first = false;
    rc = left_->next();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("left operator next() failed in first time\n");
      return rc;
    }
    rc = fetch_the_right_data();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("fetch the right data failed in first time\n");
      return rc;
    }
  }
  if (right_table_data_position_ != right_table_data_.end()) {
    // if don't visit all right table data,we should get every right table data,when the join
    // operator execute the next() function
    JoinRecord temp(*right_table_data_position_);
    tuple_.set_right_record(temp);
    right_table_data_position_++;
    return RC::SUCCESS;
  }
  // If the right table data have visited over, we should get the left operator's next record;
  rc = left_->next();
  if (rc != RC::SUCCESS) {
    if (rc == RC::RECORD_EOF) {
      return rc;
    } else {
      LOG_ERROR("get the left operator next() record failed");
      return rc;
    }
  }
  // remove the right table position to the beginning of the right table
  right_table_data_position_ = right_table_data_.begin();
  // Then begin the connecting operator connect the next record of left table and all data of right table
  return next();
}
RC JoinOperator::close()
{
  RC rc;
  rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_ERROR("join operator failed to close() left operator\n");
    return rc;
  }
  rc = right_->close();
  if (rc != RC::SUCCESS) {
    LOG_ERROR("join operator failed to close() right operator\n");
    return rc;
  }
  return rc;
}
Tuple *JoinOperator::current_tuple()
{
  return &tuple_;
}
RC JoinOperator::fetch_the_right_data()
{
  RC rc;
  while ((rc = right_->next()) == RC::SUCCESS) {
    // get the data of the right table
    JoinRecord r_data;
    assert(dynamic_cast<RowTuple *>(right_->current_tuple()) != nullptr);
    right_->current_tuple()->get_record(r_data);
    // r_data --> right.current_record
    // so when right->next, right.current_record changes and make the r_data changes
    // so here we need make r_data different from right_current_record, should copy one
    for (Record *&record : r_data) {
      record = new Record(*record);
    }
    right_table_data_.emplace_back(r_data);
  }
  right_table_data_position_ = right_table_data_.begin();
  if (rc == RC::RECORD_EOF) {
    return RC::SUCCESS;
  }
  return rc;
}
