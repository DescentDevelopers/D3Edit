include ../../default.mak

OBJS = module.o     
REFS = module.cpp 
LIBNAME = module.a

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