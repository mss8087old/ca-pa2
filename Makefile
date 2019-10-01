#----------------------------------------------------------------
# 
#  4190.308 Computer Architecture (Fall 2019)
#
#  Project #2: Half-precision Floating Points
#
#  October 1, 2019
#
#  Jin-Soo Kim (jinsoo.kim@snu.ac.kr)
#  Systems Software & Architecture Laboratory
#  Dept. of Computer Science and Engineering
#  Seoul National University
#
#----------------------------------------------------------------

PREFIX		=
CC			= $(PREFIX)gcc
CXX			= $(PREFIX)g++
CFLAGS		= -g -O2 -Wall 
LIBS		= 
RM			= rm
TAR			= tar

TARGET		= pa2
CSRCS		= pa2-test.c pa2.c 
CXXSRCS		= 
HEADERS		= pa2.h
OBJS		= $(CSRCS:.c=.o) $(CXXSRCS:.cpp=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS) 

.c.o: $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o: $(HEADERS)
	$(CXX) $(CFLAGS) -c $< -o $@

tar:
	$(RM) -f $(TARGET).tgz
	$(TAR) cvzf $(TARGET).tgz $(CSRCS) $(HEADERS) Makefile
	ls -l $(TARGET).tgz

clean:
	$(RM) -f $(TARGET) $(TARGET).tgz $(OBJS) *~ a.out
