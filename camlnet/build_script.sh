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


# After this, ask the user if they want
# to replace the version of inet & reboot
echo "Do you want to reboot right now?\n[y] [n]"
read REPLY
if [ "$REPLY" = "y" ] || [ "$REPLY" = "yes" ] || [ "$REPLY" = "Y" ] || [ "$REPLY" = "Yes" ] || [ "$REPLY" = "YES" ]; then
	./replace_inet.sh
fi
if [ "$REPLY" = "n" ] || [ "$REPLY" = "no" ] || [ "$REPLY" = "N" ] || [ "$REPLY" = "No" ] || [ "$REPLY" = "NO" ]; then
	echo "Done"
	exit 0
fi
echo "Reply unintelligble."
exit 65
