//
// Created by tanyuzhen on 23-11-13.
//

#pragma once

#include "sql/operator/update_operator.h"
#include "rc.h"
#include "storage/trx/trx.h"

RC UpdateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("update operator must has only 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_ERROR("in update, failed to open child operator: %s", strrc(rc));
  }

  Table *table = update_stmt_->table();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (tuple == nullptr) {
      LOG_ERROR("in update, failed to get current record: %s", strrc(rc));
      return rc;
    }
    RowTuple *row_tuple = dynamic_cast<RowTuple *>(tuple);
    if (row_tuple == nullptr) {
      LOG_ERROR("in update, row tuple cast error");
      return RC::GENERIC_ERROR;
    }
    Record &record = row_tuple->record();
    rc = table->update_record(trx_, &record, update_stmt_->values(), update_stmt_->attr_name());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("failed to delete record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC UpdateOperator::close()
{
  return RC::RECORD_EOF;
}

RC UpdateOperator::next()
{
  children_[0]->close();
  return RC::SUCCESS;
}
