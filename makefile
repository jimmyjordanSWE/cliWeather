BINARY=main.out
CODEDIRS=source source/libs
INCDIRS=source/libs
BUILDDIR=build

CC=gcc
OPT=-O0
DEPFLAGS=-MMD -MP -MD 
CFLAGS=-std=c89 -Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

LDFLAGS=
LDLIBS=-lcurl

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

OBJECTS=$(patsubst %.c,$(BUILDDIR)/%.o,$(CFILES))
DEPFILES=$(patsubst %.c,$(BUILDDIR)/%.d,$(CFILES))

DIRS=$(sort $(dir $(OBJECTS)))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(BUILDDIR)

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

-include $(DEPFILES)

.PHONY: all clean diff
