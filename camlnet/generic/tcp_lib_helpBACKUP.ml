let tcp_LEmod4G (n1: int64) (n2: int64) : int64 =
  if Int64.equal 0L (Int64.logand (Int64.sub n1 n2) 2147483648L)
  then 1L else 0L;;

let _ = Callback.register "LEmon" tcp_LEmod4G;;
