#include "s21_view.h"

#include "s21_calculator.h"
#include "s21_view.h"

namespace s21 {
double View::get_final_result(int* error_number) {
  return this->controller->get_result(error_number);
}
}  // namespace s21