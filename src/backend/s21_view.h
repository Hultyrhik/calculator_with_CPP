#ifndef S21_VIEW_H
#define S21_VIEW_H

#include "s21_calculator.h"
#include "s21_controller.h"

namespace s21 {

class View {
 private:
  Controller *controller;

 public:
  View(Controller *c) : controller(c){};
  double get_final_result(int *error_number);
};

}  // namespace s21

#endif