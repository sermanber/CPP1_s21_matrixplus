CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20
LIB = s21_matrix_oop.a
SRC = s21_matrix_oop.cpp
OBJ = $(SRC:.cpp=.o)
TEST_SRC = s21_matrix_test.cpp
TEST_BIN = test_matrix

all: $(LIB) test


$(LIB): $(OBJ)
	ar rcs $@ $^


%.o: %.cpp s21_matrix_oop.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: $(LIB) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -L. -l:$(LIB) -lgtest -lgtest_main -lpthread -o $(TEST_BIN)
	./$(TEST_BIN)


clean:
	rm -f *.o $(LIB) $(TEST_BIN)


clang:
	clang-format -i --style=Google *.cpp *.h
	clang-format -i --style=Google $(TEST_SRC)
