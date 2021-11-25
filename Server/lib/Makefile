CONSOLE_LIB	= libconsole
SRC			= $(CONSOLE_LIB).c
OBJ			= $(CONSOLE_LIB).o
ARCHIVE		= $(CONSOLE_LIB).a

CC			= gcc
CFLAGS		= -c
ARFLAGS		= rv
LDFLAGS		= -shared -o

static: $(OBJ)
		ar $(ARFLAGS) $(ARCHIVE) $(OBJ)
		ranlib $(ARCHIVE)

$(OBJ): $(SRC)
		$(CC) $(CFLAGS) $(SRC)