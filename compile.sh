#!/bin/sh
clang++ -stdlib=libc++ -std=c++11 rules.cpp -o rules
clang++ -stdlib=libc++ -std=c++11 pattern.cpp -o pattern
clang++ -stdlib=libc++ -std=c++11 raster.cpp -o raster -F/Library/Frameworks -framework sfml-graphics
