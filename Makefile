
TARGET = Laby

##########################################################"

CFLAGS = -g -O2   `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`

all: $(TARGET)

clean:
	-rm -rf $(TARGET)

