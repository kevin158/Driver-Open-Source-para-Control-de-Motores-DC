APP		= server
SRC 	= $(APP).c
APP_S	= $(APP)_s

CC			= gcc
CFLAGS	= -o
INCLUDE	= -I $(TOPDIR)/include/
LINK	= -L $(TOPDIR)/lib/
ARCHIVE	= $(TOPDIR)/lib/libconsole.a

$(APP): $(APP_S)
		rm -rf $(TOPDIR)/build
		mkdir $(TOPDIR)/build
		mv $(APP_S) $(TOPDIR)/build/$(APP)

$(APP_S):
		$(CC) $(CFLAGS) $(APP_S) $(SRC) $(ARCHIVE) $(INCLUDE)