#include <node.h>
#include "DiffWorkerCallback.hpp"
#include "PatchWorkerCallback.hpp"

extern "C" {
  #include "c/bsdiff/bsdiff.h"
  #include "c/bspatch/bspatch.h"
}

namespace bsdpNode {
  using namespace v8;

  void diff(const FunctionCallbackInfo<Value>& args)
  {
    if(args.Length() < 4 || !args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
    {
      Nan::ThrowError("Invalid arguments.");
      return;
    }

    Nan::Callback *callback = new Nan::Callback(args[3].As<v8::Function>());

    Nan::Utf8String param0(args[0]);
    std::string oldfile = std::string(*param0);

    Nan::Utf8String param1(args[1]);
    std::string newfile = std::string(*param1);

    Nan::Utf8String param2(args[2]);
    std::string patchfile = std::string(*param2);

    DiffWorkerCallback* wc = new DiffWorkerCallback(callback, oldfile, newfile, patchfile);
    Nan::AsyncQueueWorker(wc);
  }

  void diffSync(const FunctionCallbackInfo<Value>& args)
  {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
    {
      Nan::ThrowError("Invalid arguments.");
      return;
    }

    Nan::Utf8String oldfile(args[0]);
    Nan::Utf8String newfile(args[1]);
    Nan::Utf8String patchfile(args[2]);


    char error[1024];
    memset(error, 0, sizeof error);

    int ret = bsdiff(error, *oldfile, *newfile, *patchfile, nullptr, nullptr);

    if(ret != 0)
      Nan::ThrowError(error);
  }

  void patch(const FunctionCallbackInfo<Value>& args)
  {
    if(args.Length() < 4 || !args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
    {
      Nan::ThrowError("Invalid arguments.");
      return;
    }

    Nan::Callback *callback = new Nan::Callback(args[3].As<v8::Function>());

    Nan::Utf8String param0(args[0]);
    std::string oldfile = std::string(*param0);

    Nan::Utf8String param1(args[1]);
    std::string newfile = std::string(*param1);

    Nan::Utf8String param2(args[2]);
    std::string patchfile = std::string(*param2);

    PatchWorkerCallback* wc = new PatchWorkerCallback(callback, oldfile, newfile, patchfile);
    Nan::AsyncQueueWorker(wc);
  }

  void patchSync(const FunctionCallbackInfo<Value>& args)
  {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
    {
      Nan::ThrowError("Invalid arguments.");
      return;
    }

    Nan::Utf8String oldfile(args[0]);
    Nan::Utf8String newfile(args[1]);
    Nan::Utf8String patchfile(args[2]);

    char error[1024];
    memset(error, 0, sizeof error);

    int ret = bspatch(error, *oldfile, *newfile, *patchfile, nullptr, nullptr);

    if(ret != 0)
      Nan::ThrowError(error);
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "diff", diff);
    NODE_SET_METHOD(exports, "diffSync", diffSync);

    NODE_SET_METHOD(exports, "patch", patch);
    NODE_SET_METHOD(exports, "patchSync", patchSync);
  }

  NODE_MODULE_INIT() {
    init(exports);
  }
}
