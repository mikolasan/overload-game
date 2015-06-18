CC=g++
CFLAFS=-c
INCLUDES=
LFLAGS=
LIBS=-lGL -lGLU -lglut

SOURCES=scene.cpp playgrnd.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=overload


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJECTS) $(LFLAGS) $(LIBS)

$(OBJECTS): %.o: %.cpp
		$(CC) -c $(CFLAGS) $< -o $@

clean:
		rm -f *.o $(EXECUTABLE) *~
