let tcp_LEmod4G (n1: int) (n2: int) : int =
  if ((n2 - n1) land 536870912) = 0
  then 1 else 0;;

let _ = Callback.register "LEmon2" tcp_LEmod4G;;
