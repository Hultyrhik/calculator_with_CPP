#include "s21_model.h"

#include <cctype>
#include <cmath>
#include <cstring>
#include <stdexcept>

#include "s21_calculator.h"

namespace s21 {

Model::Model(std::string s, double x) : input_string{s}, x_value{x}, result{} {}

Model::Model(Model *other)
    : input_string{other->input_string}, x_value{other->x_value}, result{} {}

Model::Model(const Model &other) {
  this->input_string = other.input_string;
  this->x_value = other.x_value;
}

Model::Model(Model &&other) {
  this->input_string = other.input_string;
  this->x_value = other.x_value;
}

int Model::complete_calculation() {
  int correctness_result = NO_ERROR;
  bool is_valid = false;
  bool notation_result = true;
  int polish_result = NO_ERROR;

  int str_result = this->s21_string_process();
  if (str_result == NO_ERROR) {
    is_valid = is_expression_valid(this->token_list);
  } else {
    correctness_result = str_result;
  }

  if (correctness_result == NO_ERROR && is_valid == true) {
    notation_result = this->shunting_yard_algorithm();
  } else {
    if (correctness_result == NO_ERROR) {
      correctness_result = WRONG_COMPOSITION;
    }
  }

  if (correctness_result == NO_ERROR && notation_result == true) {
    polish_result = calculate_polish_notation();
  } else {
    if (correctness_result == NO_ERROR) {
      correctness_result = notation_result;
    }
  }

  if (correctness_result == NO_ERROR) {
    correctness_result = polish_result;
  }

  this->error_number = correctness_result;
  return correctness_result;
}

bool Model::check_parentheses() {
  bool result = true;
  int left_parentheses_count = 0;
  int right_parentheses_count = 0;
  for (auto current = this->token_list.begin();
       current != this->token_list.end(); current++) {
    if (current->unit_type == BRACKET_LEFT) {
      left_parentheses_count++;
    }

    if (current->unit_type == BRACKET_RIGHT) {
      right_parentheses_count++;
    }
  }

  if (right_parentheses_count != left_parentheses_count) {
    result = false;
  }

  return result;
}

int Model::s21_string_process() {
  error result = NO_ERROR;

  for (std::string::iterator current_char = this->input_string.begin();
       current_char != this->input_string.end() && result == NO_ERROR;
       current_char++) {
    if (std::isblank(*current_char) != 0) {
      continue;
    } else if (*current_char == '+') {
      s21_stack_push(&token_list, 0, SUM);
    } else if (*current_char == '-') {
      s21_stack_push(&token_list, 0, SUB);
    } else if (*current_char == '*') {
      s21_stack_push(&token_list, 0, MULT);
    } else if (*current_char == '/') {
      s21_stack_push(&token_list, 0, DIV);
    } else if (std::memcmp(&*current_char, "mod", 3) == 0) {
      s21_stack_push(&token_list, 0, MOD);
      current_char += 2;
    } else if (*current_char == '^') {
      s21_stack_push(&token_list, 0, POWER);
    } else if (*current_char == '(') {
      s21_stack_push(&token_list, 0, BRACKET_LEFT);
    } else if (*current_char == ')') {
      s21_stack_push(&token_list, 0, BRACKET_RIGHT);
    } else if (std::memcmp(&*current_char, "sin", 3) == 0) {
      s21_stack_push(&token_list, 0, SIN);
      current_char += 2;
    } else if (std::memcmp(&*current_char, "cos", 3) == 0) {
      s21_stack_push(&token_list, 0, COS);
      current_char += 2;
    } else if (std::memcmp(&*current_char, "tan", 3) == 0) {
      s21_stack_push(&token_list, 0, TAN);
      current_char += 2;
    } else if (std::memcmp(&*current_char, "asin", 4) == 0) {
      s21_stack_push(&token_list, 0, ASIN);
      current_char += 3;
    } else if (std::memcmp(&*current_char, "acos", 4) == 0) {
      s21_stack_push(&token_list, 0, ACOS);
      current_char += 3;
    } else if (std::memcmp(&*current_char, "atan", 4) == 0) {
      s21_stack_push(&token_list, 0, ATAN);
      current_char += 3;
    } else if (std::memcmp(&*current_char, "sqrt", 4) == 0) {
      s21_stack_push(&token_list, 0, SQRT);
      current_char += 3;
    } else if (std::memcmp(&*current_char, "ln", 2) == 0) {
      s21_stack_push(&token_list, 0, LN);
      current_char += 1;
    } else if (std::memcmp(&*current_char, "log", 3) == 0) {
      s21_stack_push(&token_list, 0, LOG);
      current_char += 2;
    } else if (*current_char == 'x') {
      s21_stack_push(&token_list, x_value, X);
    } else if (isdigit(*current_char) != 0 || *current_char == '.') {
      int count = 0;
      char number_string[NUMBER_SIZE] = {0};

      while (std::isdigit(*current_char) != 0 || *current_char == '.' ||
             *current_char == 'e' || *current_char == 'E') {
        if (count >= 309) {
          result = WRONG_NUMBER;
          break;
        }

        number_string[count++] = *current_char;
        current_char++;
      }

      int period_counter = 0;
      int e_counter = 0;
      for (char *tmp = number_string; *tmp != '\0'; tmp++) {
        if (*tmp == '.') {
          period_counter++;
        }
        if (*tmp == 'e' || *tmp == 'E') {
          e_counter++;
        }
      }

      if (period_counter > 1 || e_counter > 1) {
        result = WRONG_NUMBER;
      }

      if (result == NO_ERROR) {
        double tmp;
        std::string number_cpp_string = number_string;
        try {
          tmp = std::stod(number_cpp_string);

        } catch (std::invalid_argument const &ex) {
          result = WRONG_NUMBER;
        }

        if (result == NO_ERROR) {
          s21_stack_push(&token_list, tmp, NUMBER);
          current_char--;
        }
      }
    } else {
      result = WRONG_OPERATOR;
    }
  }

  if (result == NO_ERROR) {
    if (this->check_parentheses() == false) {
      result = WRONG_COMPOSITION;
    }
  }

  if (result == NO_ERROR) {
    check_for_unary_plus_and_minus();
  }

  return result;
}

void s21_stack_push(std::list<unit> *list, double value, type unit_type) {
  unit current{};
  s21_set_values(&current, value, unit_type);
  list->push_back(current);
}

int s21_set_values(unit *current, double value, type unit_type) {
  if (current != nullptr) {
    current->is_value = false;
    current->operator_priority = NOT_SET;
    current->value = value;
    current->unit_type = unit_type;
    current->is_binary = false;
    current->type_id = -1;

    current->operator_sign = '\0';
    s21_fill_up_values(current);
  }
  return 0;
}

void s21_fill_up_values(unit *current) {
  if (current != nullptr) {
    if (current->unit_type == NUMBER) {
      s21_set_other_values(current, true, PRIORITY_ONE, '\0', "NUMBER", false,
                           0);
    } else if (current->unit_type == X) {
      s21_set_other_values(current, true, PRIORITY_ONE, 'x', "X", false, 0);
    } else if (current->unit_type == SUM) {
      s21_set_other_values(current, false, PRIORITY_TWO, '+', "SUM", true, 1);
    } else if (current->unit_type == SUB) {
      s21_set_other_values(current, false, PRIORITY_TWO, '-', "SUB", true, 1);
    } else if (current->unit_type == DIV) {
      s21_set_other_values(current, false, PRIORITY_THREE, '/', "DIV", true, 1);
    } else if (current->unit_type == MULT) {
      s21_set_other_values(current, false, PRIORITY_THREE, '*', "MULT", true,
                           1);
    } else if (current->unit_type == MOD) {
      s21_set_other_values(current, false, PRIORITY_THREE, '\0', "mod", true,
                           1);
    } else if (current->unit_type == BRACKET_LEFT) {
      s21_set_other_values(current, false, PRIORITY_FOUR, '(', "BRACKET_LEFT",
                           false, 2);
    } else if (current->unit_type == BRACKET_RIGHT) {
      s21_set_other_values(current, false, PRIORITY_FOUR, ')', "BRACKET_RIGHT",
                           false, 3);
    } else if (current->unit_type == POWER) {
      s21_set_other_values(current, false, PRIORITY_FOUR, '^', "POWER", true,
                           1);
    } else if (current->unit_type == UNARY_PLUS) {
      s21_set_other_values(current, false, PRIORITY_FOUR, '+', "UNARY_PLUS",
                           false, 5);
    } else if (current->unit_type == UNARY_MINUS) {
      s21_set_other_values(current, false, PRIORITY_FOUR, '-', "UNARY_MINUS",
                           false, 5);
    } else if (current->unit_type == SIN) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "sin", false,
                           4);
    } else if (current->unit_type == COS) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "cos", false,
                           4);
    } else if (current->unit_type == TAN) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "tan", false,
                           4);
    } else if (current->unit_type == ACOS) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "acos", false,
                           4);
    } else if (current->unit_type == ASIN) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "asin", false,
                           4);
    } else if (current->unit_type == ATAN) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "atan", false,
                           4);
    } else if (current->unit_type == SQRT) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "sqrt", false,
                           4);
    } else if (current->unit_type == LN) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "ln", false, 4);
    } else if (current->unit_type == LOG) {
      s21_set_other_values(current, false, PRIORITY_FIVE, '\0', "log", false,
                           4);
    }
  }
}

int s21_set_other_values(unit *current, bool is_value,
                         priority operator_priority, char operator_sign,
                         std::string operator_name, bool is_binary,
                         int type_id) {
  if (current != nullptr) {
    current->is_value = is_value;
    current->operator_priority = operator_priority;
    current->operator_sign = operator_sign;
    current->operator_name = operator_name;
    current->is_binary = is_binary;
    current->type_id = type_id;
  }

  return 0;
}

/*
current

-num
+num

(-num
(+num

-(
+(

num-(   not unary
num+(   not unary

num - -num
num - +num

num -+ num
num + +num
*/
void Model::check_for_unary_plus_and_minus() {
  for (auto current = this->token_list.begin();
       current != this->token_list.end(); current++) {
    bool is_unary_plus = false;
    bool is_unary_minus = false;
    if (current->unit_type == SUM) {
      if (current == this->token_list.begin()) {
        is_unary_plus = true;
      }
      if (current != this->token_list.begin()) {
        auto previous = std::prev(current, 1);
        auto prev_t = previous->unit_type;
        auto prev_b = previous->is_binary;
        if (prev_t == BRACKET_LEFT || prev_b == true) {
          is_unary_plus = true;
        }
      }
    }

    if (current->unit_type == SUB) {
      if (current == this->token_list.begin()) {
        is_unary_minus = true;
      }
      if (current != this->token_list.begin()) {
        auto previous = std::prev(current, 1);
        auto prev_t = previous->unit_type;
        auto prev_b = previous->is_binary;
        if (prev_t == BRACKET_LEFT || prev_b == true) {
          is_unary_minus = true;
        }
      }
    }

    if (is_unary_plus == true) {
      current->unit_type = UNARY_PLUS;
      s21_set_other_values(&*current, false, PRIORITY_FOUR, '+', "UNARY_PLUS",
                           false, 5);
    } else if (is_unary_minus == true) {
      current->unit_type = UNARY_MINUS;
      s21_set_other_values(&*current, false, PRIORITY_FOUR, '-', "UNARY_MINUS",
                           false, 5);
    }

    // if (current == list.begin()) {
    //   continue;
    // } else {
    // auto previous = current;
    // previous--;
    // if (current->unit_type == SUM || current->unit_type == SUB) {
    //   if (previous == list.begin() || previous->unit_type == BRACKET_LEFT ||
    //       (previous->is_value == false &&
    //        previous->unit_type != BRACKET_RIGHT)) {
    //     if (current->unit_type == SUM) {
    //       current->unit_type = UNARY_PLUS;
    //       s21_set_other_values(&*current, false, PRIORITY_FOUR, '+',
    //                            "UNARY_PLUS", false, 5);
    //     } else {
    //       current->unit_type = UNARY_MINUS;
    //       s21_set_other_values(&*current, false, PRIORITY_FOUR, '-',
    //                            "UNARY_MINUS", false, 5);
    //     }
    //   }
    // } else if (previous->unit_type == SUM || previous->unit_type == SUB) {
    //    if (previous == list.begin() || previous->unit_type == BRACKET_LEFT) {

    //    }
    // }

    // }
  }
}

bool is_expression_valid(std::list<unit> list) {
  bool result = true;
  bool validation_matrix[6][6] = {

      // 0 - number, x;
      // True if next - (1)sum, (3)Right bracket;
      // False if - (0)number, (2)Left bracket, (4)sin, (5)unary;
      {0, 1, 0, 1, 0, 0},

      // 1 - sum, sub, div, mult, mod, power;
      // True if next - (0)number, (2)Left bracker, (4)sin, (5)unary;
      // False if next - (1)sum, (3)Right bracket;
      {1, 0, 1, 0, 1, 1},

      // 2 - (;
      // True if next - (0)number, (2)Left bracker, (4)sin, (5)unary;
      // False if next - (1)sum, (3)Right bracket;
      {1, 0, 1, 0, 1, 1},

      // 3 - );
      // True if next - (1)sum, (3)Right bracket;
      // False if next - (0)number, (2)Left bracket, (4)sin, (5)unary;
      {0, 1, 0, 1, 0, 0},

      // 4 - sin, cos, tan, acos, asin, atan, sqrt, ln, log;
      // True if next - (2)Left bracket;
      // False if next - (0)number, (1)sum, (3)Right bracket, (4)sin,
      // (5)unary;
      {0, 0, 1, 0, 0, 0},

      // 5 - unary_plus, unary_minus;
      // True if next - (0)number, (2)Left bracket, (4)sin;
      // False if next - (1)sum, (3)Right bracket, (5)unary;
      {1, 0, 1, 0, 1, 0}};

  for (auto current = list.begin(); current != list.end() && result == true;
       current++) {
    auto next = std::next(current, 1);
    if (next != list.end()) {
      if (validation_matrix[current->type_id][next->type_id] != true) {
        result = false;
      }
    }
  }

  return result;
}

bool Model::shunting_yard_algorithm() {
  bool result = true;
  std::list<unit> operator_stack{};
  unit temp = {};
  if (this->token_list.size() != 0) {
    for (auto current = this->token_list.begin();
         current != this->token_list.end() && result == true; current++) {
      if (current->is_value == true) {
        s21_stack_push(&polish_notation_list, current->value,
                       current->unit_type);
      } else if (current->unit_type == BRACKET_LEFT ||
                 current->operator_priority == PRIORITY_FIVE) {
        s21_stack_push(&operator_stack, current->value, current->unit_type);
      } else if (current->type_id == 1 || current->type_id == 5) {
        while (operator_stack.back().unit_type != BRACKET_LEFT &&
               operator_stack.back().unit_type != BRACKET_RIGHT &&
               (operator_stack.back().operator_priority >
                    current->operator_priority ||
                (operator_stack.back().operator_priority ==
                     current->operator_priority &&
                 current->unit_type != POWER))) {
          temp = operator_stack.back();
          operator_stack.pop_back();
          s21_stack_push(&polish_notation_list, temp.value, temp.unit_type);
        }
        s21_stack_push(&operator_stack, current->value, current->unit_type);
      } else if (current->unit_type == BRACKET_RIGHT) {
        while (operator_stack.size() != 0 &&
               operator_stack.back().unit_type != BRACKET_LEFT &&
               result == true) {
          temp = operator_stack.back();
          operator_stack.pop_back();
          s21_stack_push(&polish_notation_list, temp.value, temp.unit_type);
        }
        if (operator_stack.size() == 0) {
          result = false;
        } else if (operator_stack.back().unit_type == BRACKET_LEFT) {
          operator_stack.pop_back();
          if (operator_stack.back().operator_priority == PRIORITY_FIVE) {
            temp = operator_stack.back();
            operator_stack.pop_back();
            s21_stack_push(&polish_notation_list, temp.value, temp.unit_type);
          }
        }
      }
    }

    if (result == true) {
      while (operator_stack.size() != 0 && result == true) {
        if (operator_stack.back().unit_type == BRACKET_LEFT ||
            operator_stack.back().unit_type == BRACKET_RIGHT) {
          result = false;
        } else {
          temp = operator_stack.back();
          operator_stack.pop_back();
          s21_stack_push(&polish_notation_list, temp.value, temp.unit_type);
        }
      }
    }
  }
  return result;
}

int Model::calculate_polish_notation() {
  int result = NO_ERROR;
  // int count = 0;
  if (this->polish_notation_list.size() != 0) {
    while (this->polish_notation_list.size() > 1 && result == NO_ERROR) {
      for (auto current = this->polish_notation_list.begin();
           current != this->polish_notation_list.end() && result == NO_ERROR &&
           this->polish_notation_list.size() > 1;
           current++) {
        // if (count > 10000) {
        //     break;
        // }
        // printf("\n\tTry - %d\n", count++);
        // s21_print_all_nodes(*list);

        if ((current)->is_value == true) {
          continue;
        } else if ((current)->is_binary == true) {
          calculate_binary(this->polish_notation_list.begin(), current,
                           &result);
        } else if ((current)->is_binary == false) {
          calculate_unary(this->polish_notation_list.begin(), current, &result);
        }
        break;
      }
    }

    if (this->polish_notation_list.front().is_value == true &&
        result == NO_ERROR) {
      this->result = this->polish_notation_list.front().value;
    } else {
      result = WRONG_COMPOSITION;
    }
  }
  return result;
}

double Model::calculate_binary(std::list<unit>::iterator begin,
                               std::list<unit>::iterator current, int *result) {
  double right_value = 0;
  double left_value = 0;
  double answer = 0;
  *result = NO_ERROR;
  type current_type = (*current).unit_type;

  if (current != begin) {
    right_value = (*std::prev(current, 1)).value;
  } else {
    *result = WRONG_COMPOSITION;
  }

  if (*result == NO_ERROR && std::prev(current, 1) != begin) {
    left_value = (*std::prev(current, 2)).value;
    // typedef enum {SUM, SUB, DIV, MULT, MOD,  POWER} type;

    if (current_type == SUM) {
      answer = left_value + right_value;
    } else if (current_type == SUB) {
      answer = left_value - right_value;
    } else if (current_type == DIV) {
      answer = left_value / right_value;
    } else if (current_type == MULT) {
      answer = left_value * right_value;
    } else if (current_type == MOD) {
      answer = std::fmod(left_value, right_value);
    } else if (current_type == POWER) {
      answer = std::pow(left_value, right_value);
    }

    unit temp{};
    s21_set_values(&temp, answer, NUMBER);
    *std::prev(current, 2) = temp;
    this->polish_notation_list.erase(std::prev(current, 1), current);
    this->polish_notation_list.erase(current);
  } else {
    *result = WRONG_COMPOSITION;
  }
  return answer;
}

double Model::calculate_unary(std::list<unit>::iterator begin,
                              std::list<unit>::iterator current, int *result) {
  double only_value = 0;
  double answer = 0;
  type current_type = (*current).unit_type;

  if (current != begin) {
    only_value = (*std::prev(current, 1)).value;
    // typedef enum { UNARY_PLUS, UNARY_MINUS, SIN, COS, TAN, ACOS, ASIN, ATAN,
    // SQRT, LN, LOG} type;

    if (current_type == UNARY_PLUS) {
      answer = only_value;
    } else if (current_type == UNARY_MINUS) {
      answer = only_value * -1;
    } else if (current_type == SIN) {
      answer = std::sin(only_value);
    } else if (current_type == COS) {
      answer = std::cos(only_value);
    } else if (current_type == TAN) {
      answer = std::tan(only_value);
    } else if (current_type == ACOS) {
      answer = std::acos(only_value);
    } else if (current_type == ASIN) {
      answer = std::asin(only_value);
    } else if (current_type == ATAN) {
      answer = std::atan(only_value);
    } else if (current_type == SQRT) {
      answer = std::sqrt(only_value);
    } else if (current_type == LN) {
      answer = std::log(only_value);
    } else if (current_type == LOG) {
      answer = std::log10(only_value);
    }

    unit temp{};
    s21_set_values(&temp, answer, NUMBER);
    *std::prev(current, 1) = temp;
    this->polish_notation_list.erase(current);
  } else {
    *result = WRONG_COMPOSITION;
  }

  return answer;
}

double Model::get_result() { return this->result; }

}  // namespace s21