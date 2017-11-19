#!/bin/sh
# Run this to generate all the initial makefiles, etc.

# in part copied from https://github.com/lighttpd/lighttpd1.4/blob/master/autogen.sh

# Special Thanks to George Brocklehurst for this excellent tutorial:
# https://robots.thoughtbot.com/the-magic-behind-configure-make-make-install

set -e

if [ ! -f configure.ac -o ! -f LICENSE ]; then
	echo "Doesn't look like you're in the source directory" >&2
	exit 1
fi

aclocal # Set up an m4 environment

autoconf # Generate configure from configure.ac

automake --add-missing # Generate Makefile.in from Makefile.am


