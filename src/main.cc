#include <node.h>
#include <node_buffer.h>

#include "diffWorkerCallback.h"

namespace bsdpNode {
  using namespace v8;

  void diff(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if(!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) 
    {
      isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "Invalid arguments.")));
      return;
    }
    
    Nan::Callback *callback = NULL;
    if(args.Length() == 4)
      callback = new Nan::Callback(args[3].As<v8::Function>());

    v8::String::Utf8Value param0(args[0]->ToString());
    std::string oldfile = std::string(*param0);  

    v8::String::Utf8Value param1(args[1]->ToString());
    std::string newfile = std::string(*param1);  

    v8::String::Utf8Value param2(args[2]->ToString());
    std::string patchfile = std::string(*param2);  

    DiffWorkerCallback* wc = new DiffWorkerCallback(callback, oldfile, newfile, patchfile);
    Nan::AsyncQueueWorker(wc);
  }

  void patch(const FunctionCallbackInfo<Value>& args) {
    /*Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    if(!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, "Invalid arguments.")));
      return;
    }
    
    String::Utf8Value oldfile(args[0]);
    String::Utf8Value newfile(args[1]);
    String::Utf8Value patchfile(args[2]);

    char error[1024];
    int ret = bspatch(error, *oldfile, *newfile, *patchfile, &callback);   
    if(ret != 0) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, error)));
    }    */
  }

  void init(Local<Object> exports, Local<Object> module) {
    NODE_SET_METHOD(exports, "diff", diff);
    NODE_SET_METHOD(exports, "patch", patch);
  }

  NODE_MODULE(bsdp, init)
}