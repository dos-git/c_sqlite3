#APP       = test_bst

#SRCS      = $(wildcard *.c)
#SRCS      = $(test_bst.c)
#OBJS      = $(SRCS:.c=.o)

#CUNIT_DIR = /usr/include/CUnit

#INCLUDES  = $(CUNIT_DIR)
#CFLAGS    = -Wall $(INCLUDES)

#LDFLAGS   = -L$(CUNIT_DIR)
#LIBS      = -lcunit

# suppress all output info whem the command "make clean" is executed
.SILENT: clean

CWD=$(shell pwd)
DB_PATH="$(CWD)/data/test_sqlite.db"


# Rules section
prog :
	gcc main.c resources_sqlite.c -lsqlite3 -o main.o

test_SQL :
	gcc test_SQLite.c resources_sqlite.c -o test_SQLite.o -lcunit -lsqlite3

clean :
	if [ -a main.o ];        then rm main.o;        fi
	if [ -a test_SQLite.o ]; then rm test_SQLite.o; fi
	if [ -a $(DB_PATH) ];    then rm $(DB_PATH); fi
