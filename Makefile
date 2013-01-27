CC			= g++
CFLAGS		= -c -Wall
LDFLAGS		= -lxerces-c
SOURCES		= main.cpp xmldom.cpp
INCLUDES	= 
OBJECTS		= $(SOURCES:.cpp=.o)
TARGET		= xmldom

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
