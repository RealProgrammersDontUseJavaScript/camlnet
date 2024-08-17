#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/intext.h> // Needed for the serialization/deserialization func's

#include "tcp_int.h" // For the tcp_conn_t definition (so far)

#include <stdint.h>

/* This file includes all the wrappers around the Ocaml func's
   Information gathered from these links:
   https://ocaml.org/manual/4.02/intfc.html
   https://askra.de/software/ocaml-doc/4.02/intfc.html
   
   TO-DO: Ocaml func pointers should be initialized either
   in main, or a function called by main, to avoid being
   checked every single time the wrapper is called */
   

static void tcp_conn_t_serialize(value cust_block, uintnat* i386_size, uintnat* amd_size);
static uintnat tcp_conn_t_deserialize(void* caml_dest);
   
/* This struct contains all the func's necessary for Ocaml
   when calling caml_alloc_custom for a tcp_conn_t
   Note: it's actually a tcp_conn_t pointer */
struct custom_operations tcp_conn_t_ops = {
  "inet.tcp_conn_t",
  custom_finalize_default,    // Leave this field default for now, when it's GC'ed nothing should happen
  custom_compare_default,     // If you're comparing 2 TCP connections, you're doing it wrong
  custom_compare_ext_default, // See above ^
  custom_hash_default,        // Default for now, must fix later
  tcp_conn_t_serialize,
  tcp_conn_t_deserialize
};


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

// Skip tcp_extract_ipopt since it does nothing

#if !defined(tcp_extract_tcpopt) // Don't replace the tcp_lib func. until it has been removed & this 1 finished
// Transfer struct pointers according to: https://gaiustech.wordpress.com/2011/05/17/accessing-c-memory-structures-from-ocaml/
void tcp_extract_tcpopt(tcp_conn_t* tcp_conn, tcp_hdr_t* tcp_hdr, size_t* mssp) {
  value caml_tcp_conn = caml_alloc_custom(&tcp_conn_t_ops, sizeof(tcp_conn_t*), 0, 1);
  // Not yet sure why 0 & 1, that's just what was used in the example.
  *((tcp_conn_t**) Data_custom_val(caml_tcp_conn)) = tcp_conn;
  
  return;
}
#endif


// All the func's needed for the custom operations struct above
// Note: cust_block = tcp_conn_t**
static void tcp_conn_t_serialize(value cust_block, uintnat* i386_size, uintnat* amd_size) {
  tcp_conn_t* tcp_conn = *((tcp_conn_t**) Data_custom_val(cust_block));
  
  /* Unfortunately, as far as I know, there's no cross-platform way to know
     If a C program is being compiled on a 32 or 64-bit platform
     Therefore, I will disallow compilation on anything other than
     an i386/x86 Minix platform */
  #if (sizeof(tcp_conn_t*) != 4)
    #error
  #endif
  *i386_size = sizeof(tcp_conn_t*);
  *amd_size = sizeof(tcp_conn_t*) * 2;
  // This is totally inappropriate, but no elegant way of doing it... for now
  caml_serialize_block_4(&tcp_conn, 1);
  
  return;
}

static void tcp_conn_t_deserialize(void* cust_block) {
  tcp_conn_t* temp;
  caml_deserialize_block_4(&temp, 1);
  *((tcp_conn_t*) Data_custom_val(cust_block)) = temp; 
  
  return;
}



