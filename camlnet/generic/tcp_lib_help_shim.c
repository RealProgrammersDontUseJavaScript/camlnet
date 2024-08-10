#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>

#include <stdint.h>

int tcp_LEmod4G(u32_t n1, u32_t n2) {
  char* nullPtr = 0;
  caml_startup(&nullPtr);

  value* ml_tcp_LEmod4G = caml_named_value("LEmon2");
  if(ml_tcp_LEmod4G == 0) return -1;

  return Int_val(caml_callback2(*ml_tcp_LEmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}
