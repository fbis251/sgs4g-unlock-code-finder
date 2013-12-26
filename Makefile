# Compilers
CROSS_COMPILER = arm-none-linux-gnueabi-gcc
GCC            = gcc
GCC_OPTS       = -Wall

# Add debugging symbols to the output executable
DEBUG_OPTS     = -g

# Files
SOURCES        = unlocker.c
EXE            = unlock_code

native: $(SOURCES)
	$(GCC) -o $(EXE) $(GCC_OPTS) $(SOURCES)
	clear
	./$(EXE) nv_data.bin

native-debug: $(SOURCES)
	$(GCC) -o $(EXE) $(GCC_OPTS) $(DEBUG_OPTS) $(SOURCES)

clean:
	rm -f $(EXE) *.o

new: clean default

debug: native_debug

default: native_debug

