#APP       = test_bst

#SRCS      = $(wildcard *.c)
#SRCS      = $(test_bst.c)
#OBJS      = $(SRCS:.c=.o)

#CUNIT_DIR = /usr/include/CUnit

#INCLUDES  = $(CUNIT_DIR)
#CFLAGS    = -Wall $(INCLUDES)

#LDFLAGS   = -L$(CUNIT_DIR)
#LIBS      = -lcunit


# Rules section
#
prog_str :
	gcc main.c -lsqlite3 -o main_out 

clean :
	rm main_out
