//
// Created by tanyuzhen on 23-11-13.
//
#pragma once

#ifndef MINIDB_UPDATE_OPERATOR_H
#define MINIDB_UPDATE_OPERATOR_H

#endif  // MINIDB_UPDATE_OPERATOR_H

#include "sql/operator/operator.h"
#include "rc.h"
#include "sql/stmt/update_stmt.h"

class Trx;
class UpdateStmt;

class UpdateOperator : public Operator {
public:
  UpdateOperator(UpdateStmt *update_stmt, Trx *trx) : update_stmt_(update_stmt), trx_(trx)
  {}

  virtual ~UpdateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override
  {
    return nullptr;
  }

private:
  UpdateStmt *update_stmt_ = nullptr;
  Trx *trx_ = nullptr;
};