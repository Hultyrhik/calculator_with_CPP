CC= g++
CFLAGS= -Wall -Werror -Wextra -std=c++17 -g
PROJECT_NAME= s21_calculator
PROJECT_NAME2= s21_calculator_tar
FRONT_DIR = frontend
BACK_DIR= backend
TEXI2DVI= texi2pdf
HEADER_FILES= $(BACK_DIR)/s21_calculator.h $(BACK_DIR)/s21_controller.h $(BACK_DIR)/s21_model.h $(BACK_DIR)/s21_view.h
SOURCE_FILES= $(BACK_DIR)/s21_controller.cc $(BACK_DIR)/s21_model.cc $(BACK_DIR)/s21_view.cc
GTEST_FLAGS = -lgtest -lgtest_main
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

.PHONY: tests test

test: clean 
	g++ -Wall -g -pthread $(CFLAGS) $(HEADER_FILES) $(SOURCE_FILES) tests/tests.cc -lgtest_main  -lgtest -lpthread -o test
	./test

main: clean
	$(CC) $(CFLAGS) $(HEADER_FILES) $(SOURCE_FILES)  main.cc -o main 
	./main


all: clean test 
	mkdir app && cd app && cmake .. && cmake --build . && ./s21_calculator

install: clean
	mkdir app && cd app && cmake .. && cmake --build .
	cd ..
	mkdir s21_calculator
	cp app/s21_calculator s21_calculator
	./s21_calculator/s21_calculator

uninstall: clean
	rm -rf s21_calculator

$(PROJECT_NAME).o: $(PROJECT_NAME).cc $(PROJECT_NAME).h
	$(CC) $(CFLAGS) -c -o $@ $<

build: clean install

valgrind: test
	valgrind -s --tool=memcheck  --track-origins=yes --leak-check=yes ./test



dvi: $(PROJECT_NAME).dvi
	open info.pdf

$(PROJECT_NAME).dvi: info.texi 
	$(TEXI2DVI) info.texi

dist:
	mkdir $(PROJECT_NAME2)
	cp Makefile CMakeLists.txt CMakeLists.txt.user $(PROJECT_NAME2)
	cp -r $(FRONTEND_FOLDER) tests $(HEADER_FILES) $(SOURCE_FILES) $(PROJECT_NAME2)
	 tar cvzf $(PROJECT_NAME2).tgz $(PROJECT_NAME2)
	 rm -rf $(PROJECT_NAME2)


clean:
	rm -rf *.o *.a *.so *.out $(PROJECT_NAME) s21_test report
	rm -rf ../../build/$(PROJECT_NAME)
	rm -rf core.* log.txt *.gcda *.gcno *.gch *.info
	rm -rf core.* log.txt tests/*.gcda tests/*.gcno tests/*.gch tests/*.info tests/s21_test
	rm -rf *.log .clang-format
	rm -rf $(PROJECT_NAME)_test.c
	rm -rf app
	rm -rf *.aux *.cp *.cps *.dvi *.log *.pdf *.toc
	rm -rf $(PROJECT_NAME).tgz
	rm -rf s21_calculator
	rm -rf main
	rm -rf s21_calculator_tar.tgz
	rm -rf test
	rm -rf backend/*.gch

rebuild:
	$(MAKE) clean
	$(MAKE) all

clangMakeRight:
	cp ../materials/linters/.clang-format ./
	clang-format -i backend/*.cc backend/*.h plot/*.h plot/*.cpp frontend/*.cpp frontend/*.h tests/*.cc
	clang-format --verbose -n backend/*.cc backend/*.h plot/*.h plot/*.cpp frontend/*.cpp frontend/*.h tests/*.cc

clangTest:
	cp ../materials/linters/.clang-format ./
	clang-format --verbose -n backend/*.cc backend/*.h plot/*.h plot/*.cpp frontend/*.cpp frontend/*.h tests/*.cc

cppcheck:
	cppcheck --enable=all --inconclusive --library=posix --suppress=missingIncludeSystem *.c *.h
