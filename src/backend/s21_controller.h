#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include "s21_calculator.h"
#include "s21_model.h"

namespace s21 {
class Controller {
 private:
  Model *model;

 public:
  Controller(Model *m) : model{m} {};
  int calculate();
  double get_result(int *error_number);
};

}  // namespace s21

#endif