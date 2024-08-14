#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>

#include <stdint.h>

/* This file includes all the wrappers around the Ocaml func's
   TO-DO: Ocaml func pointers should be initialized either
   in main, or a function called by main, to avoid being
   checked every single time the wrapper is called */

int tcp_LEmod4G(u32_t n1, u32_t n2) {
  static value* ml_tcp_LEmod4G = 0;
  if(ml_tcp_LEmod4G == 0) {
    ml_tcp_LEmod4G = caml_named_value("LEmod");
    if(ml_tcp_LEmod4G == 0) return -1;
  }

  return Int_val(caml_callback2(*ml_tcp_LEmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}

int tcp_GEmod4G(u32_t n1, u32_t n2) {
  static value* ml_tcp_GEmod4G = 0;
  if(ml_tcp_GEmod4G == 0) {
    caml_named_value("GEmod");
    if(ml_tcp_GEmod4G == 0) return -1;
  }

  return Int_val(caml_callback2(*ml_tcp_GEmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}

int tcp_Lmod4G(u32_t n1, u32_t n2) {
  static value* ml_tcp_Lmod4G = 0;
  if(ml_tcp_Lmod4G == 0) {
    caml_named_value("Lmod");
    if(ml_tcp_Lmod4G == 0) return -1;
  }

  return Int_val(caml_callback2(*ml_tcp_Lmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}

int tcp_Gmod4G(u32_t n1, u32_t n2) {
  static value* ml_tcp_Gmod4G = 0;
  if(ml_tcp_Gmod4G == 0) {
    caml_named_value("Gmod");
    if(ml_tcp_Gmod4G == 0) return -1;
  }

  return Int_val(caml_callback2(*ml_tcp_Gmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}
