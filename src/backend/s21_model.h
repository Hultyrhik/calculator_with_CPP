#ifndef S21_MODEL_H
#define S21_MODEL_H

#include <iostream>

#include "s21_calculator.h"

// You should provide the input of numbers in exponential notation;

namespace s21 {

class Model {
 private:
  std::string input_string;
  std::list<unit> token_list;
  std::list<unit> polish_notation_list;
  double x_value;
  double result;
  int error_number = NO_ERROR;

 public:
  // funcs

  int get_error() { return this->error_number; }

  /**
   * @short Parametrized constructor.
   */

  Model(std::string s, double x);

  /**
   * @short Parametrized constructor with pointer.
   */

  Model(Model *other);

  /**
   * @brief Copy constructor.
   * @param other Receives l-value reference to other Model object
   */
  Model(const Model &other);

  /**
   * @brief Move constructor.
   * @param other Receives r-value reference to other Model object
   */
  Model(Model &&other);
  bool check_parentheses();

  void check_for_unary_plus_and_minus();

  int s21_string_process();

  bool shunting_yard_algorithm();

  double calculate_binary(std::list<unit>::iterator begin,
                          std::list<unit>::iterator current, int *result);

  double calculate_unary(std::list<unit>::iterator begin,
                         std::list<unit>::iterator current, int *result);

  int calculate_polish_notation();

  int complete_calculation();

  double get_result();
};  // class Model

// non-class functions

// +-
int s21_set_other_values(unit *current, bool is_value,
                         priority operator_priority, char operator_sign,
                         std::string operator_name, bool is_binary,
                         int type_id);

// +-
void s21_fill_up_values(unit *current);

// +-
int s21_set_values(unit *current, double value, type unit_type);

// +
void s21_stack_push(std::list<unit> *list, double value, type unit_type);

// +-
bool is_expression_valid(std::list<unit> list);

}  // namespace s21

#endif