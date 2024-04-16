include ../../default.mak

OBJS = bitmain.o bumpmap.o iff.o lightmap.o pcx.o tga.o    
REFS = bitmain.cpp bumpmap.cpp iff.cpp lightmap.cpp pcx.cpp tga.cpp    
LIBNAME = bitmap.a

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