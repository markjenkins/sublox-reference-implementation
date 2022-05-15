#include "vm.h"
#include "object.h"
#include "value.h"
#include "table.h"
#include "chunk.h"
#include "value.h"
#include "debug.h"

static void init_vm_runtime_pair_fns(VM * vm){
  // note, all invocations of writeChunk here have 0 as a last argument
  // meaning that we're describing this runtime as living on line 0

  // strings that we'll re-use
  ObjString* OBJECT_string = copyString("OBJECT", 6);
  ObjString* first_string =  copyString("first", 5);
  ObjString* second_string = copyString("second", 6);

  // establish a global empty class OBJECT {}
  tableSet(&(vm->globals), OBJECT_string, OBJ_VAL(newClass(OBJECT_string)));

  // establish a built-in pair(a, b) function
  // fun pair(a, b){
  //   var p = OBJECT();
  //   p.first  = a;
  //   p.second = b;
  //   return p;
  // }
  ObjFunction* pair_function = newFunction();
  ObjString * pair_fn_string = copyString("pair", 4);
  pair_function->name = pair_fn_string;
  pair_function->arity = 2;
  Chunk * pair_function_chunk = &(pair_function->chunk);

  // OP_GET_GLOBAL 'object'
  writeChunk(pair_function_chunk, OP_GET_GLOBAL, 0);
  writeChunk(pair_function_chunk,
	     addConstant(pair_function_chunk, OBJ_VAL(OBJECT_string) ),
	     0); // OBJECT

  // this call leaves the result of OBJECT() on top of the stack as p (local 3)
  writeChunk(pair_function_chunk, OP_CALL, 0);
  writeChunk(pair_function_chunk, 0, 0); // pair has 0 arguments

  // build up the stack with p, b, p, a
  // they'll be used by two OP_SET_PROPERTY coming up
  // its the p and a on top of the stack that are used first for p.first
  writeChunk(pair_function_chunk, OP_GET_LOCAL, 0);
  writeChunk(pair_function_chunk, 3, 0); // local 3 is p
  writeChunk(pair_function_chunk, OP_GET_LOCAL, 0);
  writeChunk(pair_function_chunk, 2, 0); // local 2 is b
  writeChunk(pair_function_chunk, OP_GET_LOCAL, 0);
  writeChunk(pair_function_chunk, 3, 0); // local 3 is p
  writeChunk(pair_function_chunk, OP_GET_LOCAL, 0);
  writeChunk(pair_function_chunk, 1, 0); // local 1 is a

  writeChunk(pair_function_chunk, OP_SET_PROPERTY, 0);
  writeChunk(pair_function_chunk,
	     addConstant(pair_function_chunk, OBJ_VAL(first_string) ),
	     0);
  // OP_SET_PROPERTY leaves the value assigned on the stack
  writeChunk(pair_function_chunk, OP_POP, 0);

  writeChunk(pair_function_chunk, OP_SET_PROPERTY, 0);
  writeChunk(pair_function_chunk,
	     addConstant(pair_function_chunk, OBJ_VAL(second_string) ),
	     0);
    // OP_SET_PROPERTY leaves the value assigned on the stack
  writeChunk(pair_function_chunk, OP_POP, 0);

  // local p is on top of the stack and there are no other locals
  // so we can return that and know the stack is back where we found it
  writeChunk(pair_function_chunk, OP_RETURN, 0);
  tableSet(&(vm->globals), pair_fn_string, OBJ_VAL(pair_function));
  // disassembleChunk(pair_function_chunk, "pair");
  // END OF pair() function

  // START OF pair_first function
  // fun pair_first(p){
  //   return p.first;
  // }
  pair_function = newFunction();
  pair_fn_string = copyString("pair_first", 10);
  pair_function->name = pair_fn_string;
  pair_function->arity = 1;
  pair_function_chunk = &(pair_function->chunk);

  // we need to copy local var p even though its already on top of the stack
  // because OP_GET_PROPERTY will consume it
  writeChunk(pair_function_chunk, OP_GET_LOCAL, 0);
  writeChunk(pair_function_chunk, 1, 0); // local 1 is p

  writeChunk(pair_function_chunk, OP_GET_PROPERTY, 0);
  writeChunk(pair_function_chunk,
	     addConstant(pair_function_chunk, OBJ_VAL(first_string) ),
	     0);
  writeChunk(pair_function_chunk, OP_RETURN, 0);
  tableSet(&(vm->globals), pair_fn_string, OBJ_VAL(pair_function));
  // END of pair_first function

  // START OF pair_second function
  // fun pair_second(p){
  //   return p.first;
  // }
  pair_function = newFunction();
  pair_fn_string = copyString("pair_second", 11);
  pair_function->name = pair_fn_string;
  pair_function->arity = 1;
  pair_function_chunk = &(pair_function->chunk);

  // we need to copy local var p even though its already on top of the stack
  // because OP_GET_PROPERTY will consume it
  writeChunk(pair_function_chunk, OP_GET_LOCAL, 0);
  writeChunk(pair_function_chunk, 1, 0); // local 1 is p

  writeChunk(pair_function_chunk, OP_GET_PROPERTY, 0);
  writeChunk(pair_function_chunk,
	     addConstant(pair_function_chunk, OBJ_VAL(second_string) ),
	     0);
  writeChunk(pair_function_chunk, OP_RETURN, 0);
  tableSet(&(vm->globals), pair_fn_string, OBJ_VAL(pair_function));
  // END of pair_second function
}

void init_vm_runtime(VM * vm){
  // caution, if garbage collection is every added, we should take care
  // to make sure it doesn't run while we're doing this

  init_vm_runtime_pair_fns(vm);
}
