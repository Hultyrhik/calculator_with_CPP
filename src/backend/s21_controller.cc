#include "s21_controller.h"

#include "s21_calculator.h"

namespace s21 {

int Controller::calculate() {
  this->model->complete_calculation();
  return this->model->get_error();
}

double Controller::get_result(int* error_number) {
  int temp = this->calculate();
  *error_number = temp;
  return this->model->get_result();
}

}  // namespace s21