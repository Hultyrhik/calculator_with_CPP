#ifndef S21_CALCULATOR_H
#define S21_CALCULATOR_H

#include <iostream>
#include <list>
#include <string>

#include "s21_calculator.h"

namespace s21 {

const int NUMBER_SIZE{311};

typedef enum {
  NOT_SET,
  PRIORITY_ONE,
  PRIORITY_TWO,
  PRIORITY_THREE,
  PRIORITY_FOUR,
  PRIORITY_FIVE
} priority;

typedef enum {
  EMPTY,
  NUMBER,
  X,
  SUM,
  SUB,
  DIV,
  MULT,
  MOD,
  BRACKET_LEFT,
  BRACKET_RIGHT,
  POWER,
  UNARY_PLUS,
  UNARY_MINUS,
  SIN,
  COS,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
} type;

typedef enum {
  NO_ERROR,
  WRONG_OPERATOR,
  WRONG_NUMBER,
  WRONG_COMPOSITION
} error;

typedef struct {
  bool is_value;  // false means operator
  priority operator_priority;
  double value;
  type unit_type;
  char operator_sign;
  std::string operator_name;
  bool is_binary;
  int type_id;
} unit;

}  // namespace s21

#endif