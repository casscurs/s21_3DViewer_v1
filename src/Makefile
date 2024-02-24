#Makefile by Casscurs Hunturek

PROJECT_NAME = 3DViewer
VERSION = 1.0

# Цвета для оформления вывода
COLOR_TITLE = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m
# Исходники
NAME = viewer.a
SRC_FILES = $(wildcard ./Backend/*.c)
HEADER_FILES = $(wildcard ./Backend/*.h)
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
DEP_FILES = $(patsubst %.c, %.d, $(SRC_FILES))
CPP_FILES = $(wildcard ./3D_Viewer/*.cpp)
CPP_HEADERS = $(wildcard ./3D_Viewer/*.h)
# Тесты
TESTS_DIR = Backend/tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.c)
TESTS_OBJ = $(patsubst %.c,%.o,$(TESTS_SRC))
# Флаги
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
#-g -fsanitize=address,undefined,unreachable -fno-sanitize-recover -fstack-protector
AR = ar rcs
LIBS = -lcheck
COVERAGE =
# Документация .dvi
DVI_TARGET = doc.dvi
TEXI2DVI = texi2dvi
SRC_DIR = documentation
# Дистрибутируемый архив 
DIST_DIR = dist/$(PROJECT_NAME)-$(VERSION)
DIST_FILES = $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) $(CPP_HEADERS) $(TESTS_SRC) $(SRC_DIR)/html/index.html Makefile

all : install

txt:
	mv models/katana.txt models/katana.obj
	mv models/pumpkin.txt models/pumpkin.obj
	mv models/skull.txt models/skull.obj
	mv Backend/tests/empty.txt Backend/tests/empty.obj
	mv Backend/tests/error.txt Backend/tests/error.obj
	mv Backend/tests/nenormal.txt Backend/tests/nenormal.obj
	mv Backend/tests/normal.txt Backend/tests/normal.obj

gcov_report: clean add_coverage tests
	@echo "$(COLOR_TITLE)=== Running tests ===$(COLOR_RESET)"
	./tests
	@echo "$(COLOR_TITLE)=====================$(COLOR_RESET)"
	mkdir -p report
	lcov -o report/test.info -c -d .
	genhtml -o report report/test.info
	@rm -rf *.gcda *.gcno Backend/tests/*.gcda Backend/tests/*.gcno
	open report/index.html
	@rm -rf Backend/tests/*.d Backend/tests/*.o Backend/tests/*.gcda Backend/tests/*.gcno
	@rm -rf Backend/*.o Backend/*.gcda Backend/*.gcno

add_coverage:
	$(eval COVERAGE += --coverage)

tests: $(NAME) $(TESTS_OBJ)
	$(CC) $(CFLAGS) $(COVERAGE) $(TESTS_OBJ) $(LIBS) $(NAME) -o $@
	./tests

$(NAME) : $(OBJ_FILES)
	  $(AR) $(NAME) $?
	 # $(CC) -o $(NAME) $?
	@echo "$(COLOR_SUCCESS)=== Build complete ===$(COLOR_RESET)"

%.o : %.c
	$(CC) $(CFLAGS) $(COVERAGE) -c $< -o $@ -MMD

include $(wildcard $(D_FILES))

install: $(NAME)
	cd 3D_Viewer && mkdir -p build && cd build && cmake .. && make
	mv 3D_Viewer/build ../src 
	
uninstall:
	rm -rf build 

dvi: $(DVI_TARGET)

$(DVI_TARGET): $(TEXI_FILES)
	 rm -rf $(SRC_DIR)
	 mkdir $(SRC_DIR)
	 doxygen Doxyfile
	 @mv html latex $(SRC_DIR)

undvi:
	@rm -rf $(SRC_DIR)

dist: dvi
	@echo "$(COLOR_TITLE)=== Creating distribution archive ===$(COLOR_RESET)"
	mkdir -p $(DIST_DIR)
	cp -r $(DIST_FILES) $(DIST_DIR)/
	tar czvf $(DIST_DIR).tar.gz -C dist $(PROJECT_NAME)-$(VERSION)/
	rm -r $(DIST_DIR)
	@echo "$(COLOR_SUCCESS)=== Distribution archive created ===$(COLOR_RESET)"

distclean:
	@rm -rf dist

clean : uninstall undvi distclean
	@echo "$(COLOR_TITLE)=== Cleaning ===$(COLOR_RESET)"
	@rm -rf *.a *.o report *.gcda *.gcno $(DEP_FILES) $(NAME) tests
	@rm -rf Backend/tests/*.d Backend/tests/*.o Backend/tests/*.gcda Backend/tests/*.gcno
	@rm -rf Backend/*.o Backend/*.gcda Backend/*.gcno

cppcheck :
	@echo "$(COLOR_TITLE)=== Running cppcheck ===$(COLOR_RESET)"
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_FILES) $(HEADER_FILES) $(TESTS_SRC)

format :
	@echo "$(COLOR_TITLE)=== Formatting code ===$(COLOR_RESET)"
	clang-format -i -style=Google $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) $(CPP_HEADERS) $(TESTS_SRC)


check-format :
	@echo "$(COLOR_TITLE)=== Checking code formatting ===$(COLOR_RESET)"
	clang-format -n -style=Google $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) $(CPP_HEADERS) $(TESTS_SRC)

.PHONY : all clean cppcheck cpplint format check-format dvi undvi dist distclean start tests
