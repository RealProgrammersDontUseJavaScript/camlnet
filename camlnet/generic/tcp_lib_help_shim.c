#include <caml/mlvalues.h>
#include <caml/custom.h> // For custom_XXXXX default struct members
// #include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/intext.h> // Needed for the serialization/deserialization func's

// #include "assert.h" Error: expected func. body after declarator
#include "inet.h"    // So the compiler doesn't complain about "ipaddr_t"
#include "event.h"   // So the compiler doesn't complain about "event_t"
#include "buf.h"     // So the compiler doesn't complain about "acc_t"
#include "clock.h"   // So the compiler doesn't complain about "minix_timer_t"
#include "type.h"    // For get_userdata_t, put_userdata_t, & select_res_t
#include "tcp_int.h" // For the tcp_conn_t definition (so far)

#include <stdint.h>

// So tcp_int.h doesn't complain
#undef tcp_LEmod4G
#undef tcp_GEmod4G
#undef tcp_Lmod4G
#undef tcp_Gmod4G

// A bit of black magic stolen from http://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))


/* This file includes all the wrappers around the Ocaml func's
   Information gathered from these links:
   https://ocaml.org/manual/4.03/intfc.html
   https://askra.de/software/ocaml-doc/4.03/intfc.html
*/ 

static void tcp_conn_t_serialize(value cust_block, uintnat* i386_size, uintnat* amd_size);
static uintnat tcp_conn_t_deserialize(void* caml_dest);

// Ocaml function pointers:
static value* ml_tcp_LEmod4G = 0;
static value* ml_tcp_GEmod4G = 0;
static value* ml_tcp_Lmod4G = 0;
static value* ml_tcp_Gmod4G = 0;
   
/* This struct contains all the func's necessary for Ocaml
   when calling caml_alloc_custom for a tcp_conn_t
   Note: it's actually a tcp_conn_t pointer */
struct custom_operations tcp_conn_t_ops = {
  "inet.tcp_conn_t",
  custom_finalize_default,    // Leave this field default for now, when it's GC'ed nothing should happen
  custom_compare_default,     // If you're comparing 2 TCP connections, you're doing it wrong
  custom_hash_default,        // Default for now, must fix later
  tcp_conn_t_serialize,
  tcp_conn_t_deserialize,
  custom_compare_ext_default // See above ^
};

// Called in tcp_init():
void caml_init(void) {
  ml_tcp_LEmod4G = caml_named_value("LEmod");
  ml_tcp_GEmod4G = caml_named_value("GEmod");
  ml_tcp_Lmod4G = caml_named_value("Lmod");
  ml_tcp_Gmod4G = caml_named_value("Gmod");

  // assert (ml_tcp_LEmod4G && ml_tcp_GEmod4G && ml_tcp_Lmod4G && ml_tcp_Gmod4G);
  if (ml_tcp_LEmod4G && ml_tcp_GEmod4G && ml_tcp_Lmod4G && ml_tcp_Gmod4G)
    return;
  exit(1); 
}

int tcp_LEmod4G(u32_t n1, u32_t n2) {
  return Int_val(caml_callback2(*ml_tcp_LEmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}

int tcp_GEmod4G(u32_t n1, u32_t n2) {
  return Int_val(caml_callback2(*ml_tcp_GEmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}

int tcp_Lmod4G(u32_t n1, u32_t n2) {
  return Int_val(caml_callback2(*ml_tcp_Lmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}

int tcp_Gmod4G(u32_t n1, u32_t n2) {
  return Int_val(caml_callback2(*ml_tcp_Gmod4G, Val_int(n1 >> 2), Val_int(n2 >> 2))) << 2;
}

// Skip tcp_extract_ipopt since it does nothing

/* Comment out tcp_extract_tcpopt (for now),
   since the defined preprocessor directive doesn't
   behave the way I thought it would
#if !defined(tcp_extract_tcpopt) // Don't replace the tcp_lib func. until it has been removed & this 1 finished
// Transfer struct pointers according to: https://gaiustech.wordpress.com/2011/05/17/accessing-c-memory-structures-from-ocaml/
void tcp_extract_tcpopt(tcp_conn_t* tcp_conn, tcp_hdr_t* tcp_hdr, size_t* mssp) {
  value caml_tcp_conn = caml_alloc_custom(&tcp_conn_t_ops, sizeof(tcp_conn_t*), 0, 1);
  // Not yet sure why 0 & 1, that's just what was used in the example.
  *((tcp_conn_t**) Data_custom_val(caml_tcp_conn)) = tcp_conn;
  
  return;
}
#endif
*/

// All the func's needed for the custom operations struct above
// Note: cust_block = tcp_conn_t**
static void tcp_conn_t_serialize(value cust_block, uintnat* i386_size, uintnat* amd_size) {
  tcp_conn_t* tcp_conn = *((tcp_conn_t**) Data_custom_val(cust_block));
  
  /* Unfortunately, as far as I know, there's no cross-platform way to know
     If a C program is being compiled on a 32 or 64-bit platform
     Therefore, I will disallow compilation on anything other than
     an i386/x86 Minix platform */


  BUILD_BUG_ON(sizeof(tcp_conn_t*) != 4);
  
  *i386_size = sizeof(tcp_conn_t*);
  *amd_size = sizeof(tcp_conn_t*) * 2;
  // This is totally inappropriate, but no elegant way of doing it... for now
  caml_serialize_block_4(&tcp_conn, 1);
  
  return;
}

static uintnat tcp_conn_t_deserialize(void* cust_block) {
  tcp_conn_t* temp;
  caml_deserialize_block_4(&temp, 1);
  *((tcp_conn_t*) Data_custom_val(cust_block)) = *temp; 
  
  return 0; // Must fix later
}



