#!/bin/sh

# This script is used to be able to build the ocaml
# portion of camlnet; The Minix3 Driver Makefiles/
# NetBSD build system doesn't play nice w/ ocamlopt


# First step: compile Ocaml
# Use ocamlopt, bc native code > bytecode
ocamlopt -verbose -output-obj -o jooseBox.o ./generic/tcp_lib_help.ml
|| exit 126

# Second step: Make the rest of the project
make || exit 1


# After this, replace the version of inet
# By running replace_inet.sh
