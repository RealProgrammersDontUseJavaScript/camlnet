(* 536870912 = 0x20000000 = 0x80000000 >> 2
   Ocaml integers on the i386 are 31 bits wide
   0x80000000 is an unsigned int w/ the single 1 bit
   in the most significant position; to get around this,
   we shift the args 2 to the right
   before passing them to Ocaml *)

let tcp_LEmod4G (n1: int) (n2: int) : int =
  if ((n2 - n1) land 536870912) = 0
  then 1 else 0;;

let tcp_GEmod4G (n1: int) (n2: int) : int =
  if ((n1 - n2) land 536870912) = 0
  then 1 else 0;;

let tcp_Lmod4G (n1: int) (n2: int) : int =
  if ((n1 - n2) land 536870912) = 0
  then 0 else 1;;

let tcp_Gmod4G (n1: int) (n2: int) : int =
  if ((n2 - n1) land 536870912) = 0
  then 0 else 1;;

let _ = Callback.register "LEmod" tcp_LEmod4G;;
let _ = Callback.register "GEmod" tcp_GEmod4G;;
let _ = Callback.register "Lmod" tcp_Lmod4G;;
let _ = Callback.register "Gmod" tcp_Gmod4G;;
