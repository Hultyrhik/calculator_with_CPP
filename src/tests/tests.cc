#include <gtest/gtest.h>

#include "../backend/s21_calculator.h"
#include "../backend/s21_controller.h"
#include "../backend/s21_model.h"
#include "../backend/s21_view.h"

/*
typedef enum {
  NO_ERROR,			      0
  WRONG_OPERATOR,		  1
  WRONG_NUMBER,			  2
  WRONG_COMPOSITION		3
} error;

*/

TEST(s21_errors, s21_errors_tests_01) {
  std::string str = "4.32312.4";
  double x_value = 2;
  double right_result = 0;
  int right_error = 2;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_errors, s21_errors_tests_02) {
  std::string str = "4.32312 + + + 5";
  double x_value = 2;
  double right_result = 0;
  int right_error = 3;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_errors, s21_errors_tests_03) {
  std::string str = "3 & 2";
  double x_value = 2;
  double right_result = 0;
  int right_error = 1;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_errors, s21_errors_tests_04) {
  std::string str = "3 + 2 ( 4- 1";
  double x_value = 2;
  double right_result = 0;
  int right_error = 3;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_errors, s21_errors_tests_05) {
  std::string str = "log7";
  double x_value = 2;
  double right_result = 0;
  int right_error = 3;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_errors, s21_errors_tests_06) {
  std::string str = "6..";
  double x_value = 2;
  double right_result = 0;
  int right_error = 2;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_x_variable, s21_x_variable_tests_01) {
  std::string str = "x";

  double x_value = 2;

  double right_result = 2;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_x_variable, s21_x_variable_tests_02) {
  std::string str = "x + 2";

  double x_value = 2;

  double right_result = 4;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_x_variable, s21_x_variable_tests_03) {
  std::string str = "x*x";

  double x_value = 3;

  double right_result = 9;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_x_variable, s21_x_variable_tests_04) {
  std::string str = "-x + 10";

  double x_value = 2;

  double right_result = 8;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_just_number, s21_just_number_tests_01) {
  std::string str = "2";

  double x_value = 2;

  double right_result = 2;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_just_number, s21_just_number_tests_02) {
  std::string str = "-5";

  double x_value = 2;

  double right_result = -5;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_just_number, s21_just_number_tests_03) {
  std::string str = "0";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_just_number, s21_just_number_tests_04) {
  std::string str = "-0";

  double x_value = 2;

  double right_result = -0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_just_number, s21_just_number_tests_05) {
  std::string str = "1234567890";

  double x_value = 2;

  double right_result = 1234567890;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_brackets, s21_brackets_tests_01) {
  std::string str = "(2)";

  double x_value = 2;

  double right_result = 2;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_brackets, s21_brackets_tests_02) {
  std::string str = "(2+6)";

  double x_value = 2;

  double right_result = 8;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_brackets, s21_brackets_tests_03) {
  std::string str = "3 * (2 + 6)";

  double x_value = 2;

  double right_result = 24;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_brackets, s21_brackets_tests_04) {
  std::string str = "(3 * ((2 + 6)))";

  double x_value = 2;

  double right_result = 24;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_brackets, s21_brackets_tests_05) {
  std::string str =
      "1234 + (2 + (3 * ((2 + 6))) + 3 / 2 + ((3 -10) /20)) * -1000";

  double x_value = 2;

  double right_result = -25916;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_addition, s21_addition_tests_01) {
  std::string str = "0 + 0";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_addition, s21_addition_tests_02) {
  std::string str = "1 + 3";

  double x_value = 2;

  double right_result = 4;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_addition, s21_addition_tests_03) {
  std::string str = "-1 + 1";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_addition, s21_addition_tests_04) {
  std::string str = "-3 + -8";

  double x_value = 2;

  double right_result = -11;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_subtraction, s21_subtraction_tests_01) {
  std::string str = "-3 -3";

  double x_value = 2;

  double right_result = -6;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_subtraction, s21_subtraction_tests_02) {
  std::string str = "5 - 2";

  double x_value = 2;

  double right_result = 3;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_subtraction, s21_subtraction_tests_03) {
  std::string str = "0-0";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_subtraction, s21_subtraction_tests_04) {
  std::string str = "2 - -3";

  double x_value = 2;

  double right_result = 5;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_subtraction, s21_subtraction_tests_05) {
  std::string str = "-3333333 - -3333333";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_subtraction, s21_subtraction_tests_06) {
  std::string str = "-3333333 - 3333333";

  double x_value = 2;

  double right_result = -6666666;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_multiplication, s21_multiplication_tests_01) {
  std::string str = "1*0";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_multiplication, s21_multiplication_tests_02) {
  std::string str = "1*1";

  double x_value = 2;

  double right_result = 1;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_multiplication, s21_multiplication_tests_03) {
  std::string str = "2 * -3";

  double x_value = 2;

  double right_result = -6;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_multiplication, s21_multiplication_tests_04) {
  std::string str = "-3 * -10";

  double x_value = 2;

  double right_result = 30;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_multiplication, s21_multiplication_tests_05) {
  std::string str = "1*2*3*4*5";

  double x_value = 2;

  double right_result = 120;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_multiplication, s21_multiplication_tests_06) {
  std::string str = "10*10*10*-10*10*10";

  double x_value = 2;

  double right_result = -1000000;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_division, s21_division_tests_01) {
  std::string str = "4/2";

  double x_value = 2;

  double right_result = 2;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_division, s21_division_tests_02) {
  std::string str = "10/1";

  double x_value = 2;

  double right_result = 10;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_division, s21_division_tests_03) {
  std::string str = "432/000.3";

  double x_value = 2;

  double right_result = 1440;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_division, s21_division_tests_04) {
  std::string str = "0.002/0.1234567";

  double x_value = 2;

  double right_result = 0.016200012;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_01) {
  std::string str = "2^2";

  double x_value = 2;

  double right_result = 4;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_02) {
  std::string str = "2^2^3";

  double x_value = 2;

  double right_result = 256;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_03) {
  std::string str = "3^2^2";

  double x_value = 2;

  double right_result = 81;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_04) {
  std::string str = "3*4^2";

  double x_value = 2;

  double right_result = 48;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_05) {
  std::string str = "sin(0.5)^3";

  double x_value = 2;

  double right_result = 0.110195407;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_06) {
  std::string str = "4^0.03";

  double x_value = 2;

  double right_result = 1.042465761;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_07) {
  std::string str = "0.32^3";

  double x_value = 2;

  double right_result = 0.032768;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_power, s21_power_tests_08) {
  std::string str = "0.01^0.02";

  double x_value = 2;

  double right_result = 0.912010839;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_modulus, s21_modulus_tests_01) {
  std::string str = "3mod2";

  double x_value = 2;

  double right_result = 1;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_modulus, s21_modulus_tests_02) {
  std::string str = "5mod3";

  double x_value = 2;

  double right_result = 2;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_modulus, s21_modulus_tests_03) {
  std::string str = "3mod13";

  double x_value = 2;

  double right_result = 3;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_modulus, s21_modulus_tests_04) {
  std::string str = "3mod-5";

  double x_value = 2;

  double right_result = 3;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_modulus, s21_modulus_tests_05) {
  std::string str = "-3mod-5";

  double x_value = 2;

  double right_result = -3;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_modulus, s21_modulus_tests_06) {
  std::string str = "-3mod5";

  double x_value = 2;

  double right_result = -3;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_plus, s21_unary_plus_tests_01) {
  std::string str = "+6";

  double x_value = 2;

  double right_result = 6;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_plus, s21_unary_plus_tests_02) {
  std::string str = "+6+10";

  double x_value = 2;

  double right_result = 16;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_plus, s21_unary_plus_tests_03) {
  std::string str = "+3-+2";

  double x_value = 2;

  double right_result = 1;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_plus, s21_unary_plus_tests_04) {
  std::string str = "+10+10";

  double x_value = 2;

  double right_result = 20;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_plus, s21_unary_plus_tests_05) {
  std::string str = "3++10";

  double x_value = 2;

  double right_result = 13;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_minus, s21_unary_minus_tests_01) {
  std::string str = "-4";

  double x_value = 2;

  double right_result = -4;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_minus, s21_unary_minus_tests_02) {
  std::string str = "-4+4";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_minus, s21_unary_minus_tests_03) {
  std::string str = "-5--9";

  double x_value = 2;

  double right_result = 4;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_minus, s21_unary_minus_tests_04) {
  std::string str = "-(3*10)";

  double x_value = 2;

  double right_result = -30;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_unary_minus, s21_unary_minus_tests_05) {
  std::string str = "-sin(0.5)";

  double x_value = 2;

  double right_result = -0.479425539;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_sqrt, s21_sqrt_tests_01) {
  std::string str = "sqrt(4)";

  double x_value = 2;

  double right_result = 2;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_ln, s21_ln_tests_01) {
  std::string str = "ln(1)";

  double x_value = 2;

  double right_result = 0;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

TEST(s21_log, s21_log_tests_01) {
  std::string str = "log(25)";

  double x_value = 2;

  double right_result = 1.397940009;

  int right_error = 0;

  s21::Model model(str, x_value);
  s21::Controller controller(&model);
  s21::View view(&controller);

  int error_number;
  double result_value = view.get_final_result(&error_number);

  EXPECT_NEAR(result_value, right_result, 1e-9);
  EXPECT_EQ(error_number, right_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}