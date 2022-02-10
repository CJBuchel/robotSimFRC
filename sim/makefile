# Build entrypoint for linux

CC = g++ -std=c++17
PROG = sim

# Dirs
CPP_LIBS = libs/main/cpp*/**/*.cpp libs/main/cpp*/*.cpp 
CPP_SIM = src/cpp*/*.cpp

CPP = $(CPP_LIBS) $(CPP_SIM)
HEADERS = -Ilibs/main/include -Isrc/include -I../Trajectory-Utilities/lib/src/main/public
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
	rm -rf $(OUTDIR)