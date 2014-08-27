CC			= g++
CFLAGS		= -c -Wall
LDFLAGS		= -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lxerces-c
SOURCES		= main.cpp XmlDomDocument.cpp
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
