#include "vm.h"
#include "object.h"
#include "value.h"
#include "table.h"
#include "chunk.h"
#include "value.h"
#include "debug.h"

void init_vm_runtime(VM * vm){
  // caution, if garbage collection is every added, we should take care
  // to make sure it doesn't run while we're doing this

 // strings that we'll re-use
  ObjString* OBJECT_string = copyString("OBJECT", 6);

  // establish a global empty class OBJECT {}
  tableSet(&(vm->globals), OBJECT_string, OBJ_VAL(newClass(OBJECT_string)));

  // add a built-in global variable DOUBLE_QUOTE to make up for the lack of
  // escape sequences in lox strings (which are double quote deliminted)
  // this is more of a minimalistic change compared to adding a
  // native function that does decimal to string conversion (e.g. itoa() )
  tableSet(&(vm->globals),
	   copyString("DOUBLE_QUOTE", 12),
	   OBJ_VAL(copyString("\"", 1)) );
}
