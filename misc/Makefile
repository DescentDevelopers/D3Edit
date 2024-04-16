include ../../default.mak

OBJS = error.o endian.o logfile.o psglob.o pstring.o psrand.o
REFS = error.cpp endian.cpp logfile.cpp psglob.cpp pstring.cpp psrand.cpp
LIBNAME = misc.a

all:	depall $(OBJS)
	ar r $(LIBNAME) $(OBJS)
	ranlib $(LIBNAME)

depall:
	$(CC) -E -M $(CFLAGS) $(DEFINES) $(REFS) > .depend

clean:	
	rm -f $(OBJS) *~ $(LIBNAME) core
	
%.o: %.cpp
	$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@

ifeq (.depend,$(wildcard .depend))
include .depend
endif
