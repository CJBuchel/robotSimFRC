# Build entrypoint for linux

CC = g++
PROG = sim

# Dirs
CPP = libs/main/cpp**/*.cpp src/cpp**/*.cpp
HEADERS = -Ilibs/main/include -Isrc/include
CFLAGS = -pthread

#OPENCV
OPENCV = `pkg-config opencv --cflags --libs`
OPENCV4 = `pkg-config opencv4 --cflags --libs`

LIBS = $(OPENCV)
LIBS4 = $(OPENCV4)

MKDIR = mkdir -p
OUTDIR = build

LOCAL_DEFS = 

COMPILE = $(CC) $(CFLAGS) -o $(OUTDIR)/$(PROG) $(HEADERS) $(CPP)

all:
	$(MAKE) all4 || $(MAKE) all1

all1:
	$(MKDIR) $(OUTDIR)
	$(COMPILE) $(LIBS) $(LOCAL_DEFS)

all4:
	$(MKDIR) $(OUTDIR)
	$(COMPILE) $(LIBS4) $(LOCAL_DEFS)

clean:
	rm -rf $(OUTDIR)/$(PROG)