#include <node.h>
#include "node_buffer.h"
#include <cstring>
#include <v8.h>
#include <string>
#include <cstdlib>
#include "../lib/lz4.h"
#define Buffer node::Buffer
#define malloc std::malloc
#define memcpy memcpy

using namespace v8;

Local<Object> closeBuffer(Buffer* slowBuffer, int length);
Handle<Value> compress(const Arguments& args){
  HandleScope scope;

  if (args.Length() < 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
/*
  if (!args[0]->IsString()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }*/

  int sourceSize = args[1]->NumberValue();

  Local<Object> bufferObj    = args[0]->ToObject();
  char*         source   = Buffer::Data(bufferObj);

  int destSize = LZ4_compressBound(sourceSize) * sizeof(char);

  char* dest = (char*) malloc(destSize);


  int compSize = LZ4_compress_fast (source, dest, sourceSize, destSize, -100);

  Buffer *slowBuffer = Buffer::New(compSize);
  memcpy(Buffer::Data(slowBuffer), dest, compSize);
  return scope.Close(closeBuffer(slowBuffer, compSize));
}

Handle<Value> decompress(const Arguments& args){
  HandleScope scope;

  if (args.Length() < 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
/*
  if (!args[0]->IsString() || !args[1]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }*/
  int destSize = args[1]->NumberValue();



  Local<Object> bufferObj    = args[0]->ToObject();
  char* source   = Buffer::Data(bufferObj);

  char* dest = (char*) malloc(destSize * sizeof(char));

  LZ4_decompress_fast(source, dest, destSize);



  Buffer *slowBuffer = Buffer::New(destSize);
  memcpy(Buffer::Data(slowBuffer), dest, destSize);
  return scope.Close(closeBuffer(slowBuffer, destSize));
}
Local<Object> closeBuffer(Buffer* slowBuffer, int length){
  Local<Object> globalObj = Context::GetCurrent()->Global();
  Local<Function> bufferConstructor = Local<Function>::Cast(globalObj->Get(String::New("Buffer")));
  Handle<Value> constructorArgs[3] = { slowBuffer->handle_, v8::Integer::New(length), v8::Integer::New(0) };
  Local<Object> actualBuffer = bufferConstructor->NewInstance(3, constructorArgs);
  return actualBuffer;
}


Handle<Value> compressBound(const Arguments& args){

	HandleScope scope;
  return scope.Close(Number::New(LZ4_compressBound(args[0]->NumberValue())));
}
void Init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("compress"),
      FunctionTemplate::New(compress)->GetFunction());
  exports->Set(String::NewSymbol("compressBound"),
      FunctionTemplate::New(compressBound)->GetFunction());
  exports->Set(String::NewSymbol("decompress"),
      FunctionTemplate::New(decompress)->GetFunction());

}

NODE_MODULE(lz4_clib, Init)
