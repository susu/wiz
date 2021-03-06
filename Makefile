CC = g++
CPP = $(CC) -pedantic -Wall -U__STRICT_ANSI__
COMMON_OBJS = wiz.o implementation.o utility.o flyerz.o ais.o

ifdef SystemRoot
  RM = del /Q
  EXE = wiz.exe
  LDFLAGS		=  
  DEFS		= 
  INCLUDES	= -I.
  HACK_LIBS = -lgdi32
  OBJS = $(COMMON_OBJS)
else
  ifeq ($(shell uname), Linux)
    RM = rm -f
    EXE = wiz
    LDFLAGS		=  -L/usr/local/lib
    DEFS		= -DSTANDALONE -DHAVE_CONFIG_H -DHAVE_GTK2
    INCLUDES	= -I. -pthread -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include  
    HACK_LIBS = -lX11
    OBJS = $(COMMON_OBJS)
  endif
endif

HACK_OBJS	= screenhack.o fps.o resources.o visual.o usleep.o yarandom.o xmu.o
CPP_HACK  = $(CPP) $(LDFLAGS)

HEADERS = $(wildcard *.hpp) implementation_gdi.cpp implementation_xlib.cpp

default: wiz

all: wiz wizai

wiz: $(OBJS)
	$(CPP_HACK) -o $@ $(OBJS) $(HACK_LIBS) $(CFLAGS)

wiz.o: wiz.cpp wiz.hpp flyerz.hpp drawinterface.hpp ais.hpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

flyerz.o: flyerz.cpp wiz.hpp flyerz.hpp drawinterface.hpp ais.hpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

implementation.o: implementation.cpp wiz.hpp drawinterface.hpp implementation_gdi.cpp implementation_xlib.cpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

utility.o: utility.cpp drawinterface.hpp flyerz.hpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

ais.o: ais.cpp drawinterface.hpp flyerz.hpp ais.hpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

skeleton.o: skeleton.cpp skeleton.hpp
	$(CPP) -fPIC -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

%o: %cpp

LIB_WIZAI = libwizai.so
OBJ_WIZAI = skeleton.o
wizai: $(OBJ_WIZAI)
	$(CPP) -shared $(OBJ_WIZAI) -o $(LIB_WIZAI)

clean:
	$(RM) *.o $(EXE) core $(LIB_WIZAI)


