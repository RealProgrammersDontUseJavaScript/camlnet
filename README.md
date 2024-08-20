# \*\* ON HOLD \*\*
Currently VirtualBox is not working. Every attempt to boot a VM (not just Minix) gives a critical error. I've spent hours trying to debug it, to no avail. Until I can fix it, or get something else (like QEMU) to work, this project is on hold.

# An implementation of the Minix TCP stack in OCaml

A reimplementation of Minix 3.3.0's TCP stack in OCaml, using the OCaml FFI. Linked into the inet ELF.

*Currently in progress. Replaced tcp_lib helper functions.
Currently more of a proof of concept that Ocaml can be linked w/ Minix drivers.*

Build environment: Minix 3.3.0\
Download: <https://wiki.minix3.org/doku.php?id=www:download:releasenotes-3.3.0>\
OCaml Version: 4.03.0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Note: It's for Minix 3.4.0, but runs just fine on 3.3.0*\
Download: <https://minix3.org/pkgsrc/packages/3.4.0/i386/All/ocaml-4.03.0nb2.tgz>\
Virtualization Software: VirtualBox Graphical User Interface Version 6.1.50\
Download: <https://www.virtualbox.org/wiki/Downloads>

*Note: I assume this would work on Minix running on native hardware. However,
I haven't tested it out yet; you're certainly welcome to try.*

## Steps:
1. Install VirtualBox using the link above or your distro's package manager.
2. Download the Minix 3.3.0 (stable release) .bz2 from the Minix3 download above.
3. Decompress it using the decompression software of your choice.
4. Get a new Minix instance up and running by following these instructions:
  <https://wiki.minix3.org/doku.php?id=usersguide:runningonvirtualbox>
5. Close the Minix instance by going to *File -> Close -> Power off the machine -> ✓OK*
6. Remove the Installation .iso by going to *Settings -> Storage*, right-click on
*minix_R3.3.0-588a35b.iso*, then select *X Remove Attachment*
7. Start Minix again, then login by typing *root* then ENTER.
8. Run the command *fetch http://minix3.org/pkgsrc/packages/3.4.0/i386/All/ocaml-4.03.0nb2.tgz*
9. Run *pkgin update*
10. Install clang, by running the command *pkgin install clang*, then answering 'y'
11. Install the GNU utils, by running *pkgin install binutils*, then answering 'y'
12. Run the command *pkg_add -f ocaml*
13. Install the links browser by running *pkgin install links*
14. Run the command *links https://github.com/RealProgrammersDontUseJavaScript/camlnet/archive/refs/heads/master.zip*
15. Hit enter twice to download *camlnet-master.zip*
16. Hit q, followed by Enter, to exit the links browser
17. Run *unzip camlnet-master.zip*
18. *cd* into *camlnet-master/camlnet*, then run *./build_script.sh*

If you've done it all correctly, then congratulations, you now have proof
that Ocaml can be used to write device drivers.

Minix3 doesn't really have a lot of TCP applications at base, the main ones being *links*, *ftp*, and *fetch*.

### Important
**Before running `replace_inet.sh`, copy the original inet ELF into a backup folder,
or the only way to get it back will be to download a fresh install of Minix3 and copy it over.
Also, DO NOT RUN `make install`. IT WILL SCREW EVERYTHING UP, AND TCP WON'T
WORK NO MATTER HOW MANY TIMES YOU RESTART THE VM!**
