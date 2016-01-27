CC=clang++
CXXFLAGS= -std=c++11 -stdlib=libc++
DEBUG=-g
WARNINGS=-Wall
OPT= -O0 -O1 -O2 -O3 -O4
FRAMEWORKPATH=-F/Library/Frameworks -framework sfml-graphics

TARGETS=rules pattern raster

%: %.cpp
	$(CC) $(CXXFLAGS) $(WARNINGS) $(DEBUG) $< -o $@ $(DEBUG) $(FRAMEWORKPATH)

%.pattern: %.rules
	rules $< 10 > $@

%.coords: %.pattern
	pattern $< > $@

%.png: %.coords
	raster $< -o "$@"


.PHONY:all clean test
all:$(TARGETS)
clean:
	rm -rf $(TARGETS)
test: all
	rm -rf test.png
	make test.png
