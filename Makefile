PROGRAMNAME=hexhls
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin


WARNINGS=-Wall -Wshadow
COMPILER=gcc -std=gnu89


SRCDIR=src
OBJDIR=obj
OUTDIR=bin

PROGRAM=$(addprefix $(OUTDIR)/, $(PROGRAMNAME))
CC=$(COMPILER) $(WARNINGS)


SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))


all: $(PROGRAM)


$(PROGRAM): $(OBJECTS)
	$(CC) $^ -o $@


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I$(SRCDIR) -c $< -o $@


install:
	chmod 755 $(PROGRAM)
	mkdir -p $(BINDIR)
	cp $(PROGRAM) $(BINDIR)/$(PROGRAMNAME)


uninstall:
	rm -f $(BINDIR)/$(PROGRAMNAME)

clean:
	rm -f $(PROGRAM) 
	rm -f $(OBJDIR)/*


.PHONY: all $(PROGRAM) $(OBJDIR)/%.o clean install uninstall
