#include <iostream>
#include <iomanip>

#include "backend/s21_model.h"
#include "backend/s21_view.h"
#include "backend/s21_controller.h"

int main() {
    // std::string input = "2+2";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "1.23005e2";
    // double x = 2;
    
    // std::string input = "1e9";
    // double x = 2;

    // std::string input = "4.32312 + + + 5";
    // double x = 2;

    // std::string input = "3 & 2";
    // double x = 2;

    // std::string input = "3 + 2 ( 4- 1";
    // double x = 2;

    // std::string input = "x*x";
    // double x = 3;

    // std::string input = "-5";
    // double x = 2;

    // std::string input = " 2 - -2";
    // double x = 2;

    // std::string input = "5 + (3*4)";
    // double x = 2;


    // std::string input = "1E9";
    // double x = 2;

    std::string input = "sin(0.5)^3";
    double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    // std::string input = "4.32312.4";
    // double x = 2;

    s21::Model model(input, x);
    s21::Controller controller(&model);
    s21::View view(&controller);

    int error_number; 
    double result = view.get_final_result(&error_number);
    std::cout << std::setprecision(20) << "Result: " << result << std::endl;
    std::cout << "Error: " << error_number << std::endl;
    std::cout << 0  << " - NO_ERROR" << std::endl;
    std::cout << 1  << " - WRONG_OPERATOR" << std::endl;
    std::cout << 2  << " - WRONG_NUMBER" << std::endl;
    std::cout << 3 << " - WRONG_COMPOSITION"  << std::endl;


    return 0;
}