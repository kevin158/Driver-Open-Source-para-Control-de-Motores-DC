TOPDIR		:= $(PWD)
LIB_DIR		= $(TOPDIR)/lib
SRC_DIR		= $(TOPDIR)/src
INCLUDE_DIR	= $(TOPDIR)/include

app: library
		make -C $(SRC_DIR) TOPDIR=$(TOPDIR)
library:
		make -C $(LIB_DIR)
