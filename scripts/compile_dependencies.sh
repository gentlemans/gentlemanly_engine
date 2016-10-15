#!/bin/bash

set -xe

SCRIPTSDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

GEDIR=$SCRIPTSDIR/..
DEPSDIR=$GEDIR/deps
BUILDIR=$DEPSDIR/build

mkdir -p $BUILDDIR

compileft2() {
	
	cd $BUILDDIR
	
	mkdir -p ft2 && cd ft2
	
	cmake ../../freetype2 -G"Unix Makefiles" -DCMAKE_COMPILE_PREFIX=$
	make
	make install
	
}
