#include "mainwindow.h"

#include <QVector>

#include "../backend/s21_calculator.h"
#include "../backend/s21_controller.h"
#include "../backend/s21_model.h"
#include "../backend/s21_view.h"
#include "../plot/qcustomplot.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_digit_0, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_1, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_2, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_3, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_4, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_5, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_6, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_7, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_8, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_digit_9, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_period, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));

  connect(ui->pushButton_sign_bracket_left, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_bracket_right, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_minus, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_plus, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_star, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_slash, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_modulo, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_sign_power, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));

  connect(ui->pushButton_function_sin, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_asin, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_cos, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_acos, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_tan, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_atan, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_sqrt, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_log, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));
  connect(ui->pushButton_function_ln, SIGNAL(clicked()), this,
          SLOT(add_character_to_string()));

  connect(ui->pushButton_plot_graph, SIGNAL(clicked()), this,
          SLOT(on_pushButton_plot_graph_clicked()));
  connect(ui->pushButton_equal_to, SIGNAL(clicked()), this,
          SLOT(on_pushButton_equal_to_clicked()));
  connect(ui->pushButton_all_clear, SIGNAL(clicked()), this, SLOT(all_clear()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::all_clear() {
  ui->lineEdit_expressions_input->setText(QString(""));
  ui->lineEdit_result_display->setText(QString(""));
  ui->lineEdit_value_x->setText(QString(""));
  ui->lineEdit_range_from->setText(QString(""));
  ui->lineEdit_range_to->setText(QString(""));
}

void MainWindow::add_character_to_string() {
  QPushButton *button = (QPushButton *)sender();
  QString new_string;
  new_string = ui->lineEdit_expressions_input->text() + button->text();
  ui->lineEdit_expressions_input->setText(new_string);
}

void MainWindow::on_pushButton_plot_graph_clicked() {
  ui->lineEdit_result_display->setText(QString(""));
  QString new_string = ui->lineEdit_expressions_input->text();

  QString string_x = ui->lineEdit_value_x->text();
  QString string_range_from = ui->lineEdit_range_from->text();
  QString string_range_to = ui->lineEdit_range_to->text();

  double x_value = 0.0 / 0.0;
  double range_from_value = 0;
  double range_to_value = 0;
  double result_value = 0;

  bool is_x_ok = false;
  bool is_range_from_ok = false;
  bool is_range_to_ok = false;
  bool is_all_ok = false;

  if (string_x.isEmpty() == false) {
    is_x_ok = false;
  } else {
    is_x_ok = true;
  }

  if (string_range_from.isEmpty() == false) {
    bool ok;
    string_range_from.toDouble(&ok);
    if (ok == true) {
      range_from_value = string_range_from.toDouble();
      is_range_from_ok = true;
    } else {
      ui->lineEdit_result_display->setText(
          QString("Range from value is invalid"));
    }
  } else {
    range_from_value = -10;
    is_range_from_ok = true;
  }

  if (string_range_to.isEmpty() == false) {
    bool ok;
    string_range_to.toDouble(&ok);
    if (ok == true) {
      range_to_value = string_range_to.toDouble();
      is_range_to_ok = true;
    } else {
      ui->lineEdit_result_display->setText(
          QString("Range from value is invalid"));
    }
  } else {
    range_to_value = 10;
    is_range_to_ok = true;
  }

  if (is_x_ok == true && is_range_from_ok == true && is_range_to_ok) {
    is_all_ok = true;
  }

  if (is_all_ok == true) {
    std::string str = new_string.toStdString();

    int dots = 5000;
    double step = (range_to_value - range_from_value) / dots;
    QVector<double> x(dots), y(dots);

    for (int i = 0; i < dots; i++) {
      x[i] = range_from_value + step * i;

      s21::Model model(str, x[i]);
      s21::Controller controller(&model);
      s21::View view(&controller);

      int error_number;
      result_value = view.get_final_result(&error_number);

      int function_result = error_number;
      if (function_result == 0) {
        y[i] = result_value;
      } else if (function_result == 1) {
        ui->lineEdit_result_display->setText(
            QString("ERROR: Unrecognized operator is used!"));
        is_all_ok = false;
        break;
      } else if (function_result == 2) {
        ui->lineEdit_result_display->setText(
            QString("ERROR: Wrong number entered!"));
        is_all_ok = false;
        break;
      } else if (function_result == 3) {
        ui->lineEdit_result_display->setText(QString(
            "ERROR: Wrong order of tokens (numbers, operators, functions)!"));
        is_all_ok = false;
        break;
      }
    }

    if (is_all_ok == true) {
      ui->customPlot->addGraph();
      ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->customPlot->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssDisc, 6));
      ui->customPlot->graph(0)->setData(x, y);
      // give the axes some labels:
      ui->customPlot->xAxis->setLabel("x");
      ui->customPlot->yAxis->setLabel("y");
      // set axes ranges, so we see all data:
      ui->customPlot->xAxis->setRange(range_from_value, range_to_value);
      ui->customPlot->yAxis->setRange(range_from_value, range_to_value);
      ui->customPlot->replot();
    }

  } else {
    if (is_x_ok == false) {
      ui->lineEdit_result_display->setText(
          QString("Error:X value is entered! "));
    } else {
      ui->lineEdit_result_display->setText(
          "ERROR: Range from or/and Range to are invalid!");
    }
  }
}

void MainWindow::on_pushButton_equal_to_clicked() {
  QString new_string = ui->lineEdit_expressions_input->text();

  QString string_x = ui->lineEdit_value_x->text();
  double x_value = 0.0 / 0.0;
  double result_value = 0;

  bool ok = true;
  bool is_input_valid = false;

  if (string_x.isEmpty() == false) {
    bool ok;
    string_x.toDouble(&ok);
    if (ok == true) {
      x_value = string_x.toDouble();
      is_input_valid = true;
    } else {
      ui->lineEdit_result_display->setText(QString("X value is invalid"));
    }
  } else {
    is_input_valid = true;
  }

  //    ui->statusbar->showMessage(QString::number(ok, 10));

  if (is_input_valid == true) {
    std::string str = new_string.toStdString();

    s21::Model model(str, x_value);
    s21::Controller controller(&model);
    s21::View view(&controller);

    int error_number;
    result_value = view.get_final_result(&error_number);

    int function_result = error_number;
    if (function_result == 0) {
      ui->lineEdit_result_display->setText(
          QString::number(result_value, 'g', 15));
    } else if (function_result == 1) {
      ui->lineEdit_result_display->setText(
          QString("ERROR: Unrecognized operator is used!"));
    } else if (function_result == 2) {
      ui->lineEdit_result_display->setText(
          QString("ERROR: Wrong number entered!"));
    } else if (function_result == 3) {
      ui->lineEdit_result_display->setText(QString(
          "ERROR: Wrong order of tokens (numbers, operators, functions)!"));
    }

  } else {
    ui->lineEdit_result_display->setText("ERROR: X value is invalid!");
  }
}
