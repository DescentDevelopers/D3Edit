include ../../default.mak

OBJS = CLIPPER.o DRAW.o GLOBVARS.o INSTANCE.o POINTS.o SETUP.o
REFS = CLIPPER.cpp DRAW.cpp GLOBVARS.cpp INSTANCE.cpp POINTS.cpp SETUP.cpp
LIBNAME = 3d.a

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