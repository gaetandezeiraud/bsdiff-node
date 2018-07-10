#include <node.h>
#include <node_buffer.h>

#include <memory.h>
#include <stdlib.h>

extern "C" {
  #include "bsdiff/bsdiff.h"
  #include "bspatch/bspatch.h"  
}

namespace bsdpNode {
  using namespace v8;

  void diff(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    
    if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, "Invalid arguments.")));
      return;
    }
    
    String::Utf8Value oldfile(args[0]);
    String::Utf8Value newfile(args[1]);
    String::Utf8Value patchfile(args[2]);


    char error[1024];
    int ret = bsdiff(error, *oldfile, *newfile, *patchfile, NULL);   
    if(ret != 0) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, error)));
    }        
  }

  void patch(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, "Invalid arguments.")));
      return;
    }
    
    String::Utf8Value oldfile(args[0]);
    String::Utf8Value newfile(args[1]);
    String::Utf8Value patchfile(args[2]);

    char error[1024];
    int ret = bspatch(error, *oldfile, *newfile, *patchfile, NULL);   
    if(ret != 0) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, error)));
    }    
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "diff", diff);
    NODE_SET_METHOD(exports, "patch", patch);
  }

  NODE_MODULE(bsdp, init)
}