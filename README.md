# An implementation of the Minix TCP stack in OCaml

## For [CSC 6523 - Topics in Networking](https://sandbox.mc.edu/~bennet/cs6523b/syl.html)

### Term Project

A reimplementation of Minix 3.3.0's TCP stack in OCaml, using the OCaml FFI. Linked into the inet ELF.
*Currently in progress. Replaced a single function in tcp_lib.
More of a proof of concept that Ocaml can be linked w/ Minix drivers.*

Build environment: Minix 3.3.0
Download: <https://wiki.minix3.org/doku.php?id=www:download:releasenotes-3.3.0>
OCaml Version: 4.03.0 *Note: It's for Minix 3.4.0, but runs just fine on 3.3.0*
Download: <https://minix3.org/pkgsrc/packages/3.4.0/i386/All/ocaml-4.03.0nb2.tgz>
Virtualization Software: VirtualBox Graphical User Interface Version 6.1.50
Download: <https://www.virtualbox.org/wiki/Downloads>

*Note: I assume this would work on Minix running on native hardware. However,
I haven't tested it out yet; you're certainly welcome to try.*

## Steps:
1. Install VirtualBox using the link above or your distro's package manager.
2. Download the Minix 3.3.0 (stable release) .bz2 from the Minix3 download above.
3. Decompress it using the decompression software of your choice.
4. Get a new Minix instance up and running by following these instructions:
  <https://wiki.minix3.org/doku.php?id=usersguide:runningonvirtualbox>
6. Close the Minix instance by going to *File -> Close -> Power off the machine -> ✓OK*
5. Remove the Installation .iso by going to *Settings -> Storage*, right-click on
*minix_R3.3.0-588a35b.iso*, then select *X Remove Attachment*
6. Start Minix again, then login by typing *root* then ENTER.
7. Run the command *fetch http://minix3.org/pkgsrc/packages/3.4.0/i386/All/ocaml-4.03.0nb2.tgz*
8. Run *pkgin update*
9. Install clang, by running the command *pkgin install clang*, then answering 'y'
10. Install the GNU utils, by running *pkgin install binutils*, then answering 'y'
10. Run the command *pkg_add -f ocaml*
11. Run the command *fetch INSERT GITHUB .gz URL*
12. Run *tar -xzf camlnet.tar.gz camlnet
13. *cd* into camlnet, then run *./build_script.sh*
14. If it runs successfully, (which can be checked by typing *echo $?*),
run the command *./replace_inet.sh*

If you've done it all correctly, then congratulations, you now have proof
that Ocaml can be used to write device drivers.

Minix3 doesn't really have a lot of TCP applications at base.
However, you can install the text-based links browser by running
*pkgin install links*

### Important
**Before `replace_inet.sh`, copy the original inet ELF into a backup folder,
or the only way to get it back will be to download a fresh install of Minix3 and copy it over.
Also, DO NOT RUN `make install`. IT WILL SCREW EVERYTHING UP, AND TCP WON'T
WORK NO MATTER HOW MANY TIMES YOU RESTART THE VM!**
