OBJECTS += $(patsubst %.c,%.o,$(wildcard src/*.c))

CPPFLAGS += -Iinclude -Isrc -I../
CFLAGS += -fPIC

LDFLAGS += -L../gimxlog -L../gimxserial
LDLIBS += -lgimxlog -lgimxserial

include Makedefs
