CC = g++
LD = ld

CFLAGS = -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -Wall -Wextra -O0 -g
LDFLAGS = -T $(LDS) -nostdlib

BINDIR := bin
SRCDIR := src
OBJDIR := lib

SRC := $(wildcard $(SRCDIR)/*.cpp)
ASMSRC := $(wildcard $(SRCDIR)/*.s)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
ASMOBJS := $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%-asm.o, $(ASMSRC))
LDS = kernel.ld
TARGET = kernel.elf

kernel: $(OBJS) $(ASMOBJS) $(TARGET)

$(OBJDIR):
	@echo "[MAKE] Creating lib directory..."
	@mkdir $@

$(BINDIR):
	@echo "[MAKE] Creating bin directory..."
	@mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR) $(BINDIR)
	@echo "[MAKE] Compiling $^..."
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%-asm.o: $(SRCDIR)/%.s $(OBJDIR) $(BINDIR)
	@echo "[MAKE] Compiling $^..."
	$(CC) $(CFLAGS) -c $^ -o $@

$(TARGET):
	@echo "[MAKE] Linking into ELF file..."
	$(LD) $(LDFLAGS) $(OBJS) $(ASMOBJS) -o $(BINDIR)/$(TARGET)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
