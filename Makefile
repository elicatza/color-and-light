PROGRAMNAME=color-and-light
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
MANDIR=$(PREFIX)/share/man


WARNINGS=-Wall -Wshadow
COMPILER=gcc -std=gnu89 -lm


SRCDIR=src
OBJDIR=obj
OUTDIR=bin

PROGRAM=$(addprefix $(OUTDIR)/, $(PROGRAMNAME))
CC=$(COMPILER) $(WARNINGS)


SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))


default: makedir all

makedir:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OUTDIR)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I$(SRCDIR) -c $< -o $@

doc:
	mkdir -p $(MANDIR)/man1
	cp docs/man/color-and-light.1 $(MANDIR)/man1

install:
	chmod 755 $(PROGRAM)
	mkdir -p $(BINDIR)
	cp $(PROGRAM) $(BINDIR)/$(PROGRAMNAME)


uninstall:
	rm -f $(BINDIR)/$(PROGRAMNAME)
	rm -f $(MANDIR)/man1/color-and-light.1

clean:
	rm -f $(PROGRAM) 
	rm -f $(OBJDIR)/*


.PHONY: all install uninstall clean makedir default doc
