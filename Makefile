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


# Rules section
prog :
	gcc main.c -lsqlite3 -o main.o

test_SQL :
	gcc test_SQLite.c -o test_SQLite.o -lcunit

clean :
	if [ -a main.o ];        then rm main.o;        fi
	if [ -a test_SQLite.o ]; then rm test_SQLite.o; fi
