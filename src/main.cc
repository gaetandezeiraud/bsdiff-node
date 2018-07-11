#include <node.h>
#include <node_buffer.h>

#include <memory.h>
#include <stdlib.h>
#include <sys/time.h>

extern "C" {
  #include "bsdiff/bsdiff.h"
  #include "bspatch/bspatch.h"  
}

namespace bsdpNode {
  using namespace v8;

  void callback(off_t current, off_t total)
  {
    static struct timeval start;
    static bool           started = false;
    struct timeval        now;
    size_t                diff;

    if(started)
    {
      gettimeofday(&now, NULL);
      diff = (now.tv_sec - start.tv_sec) * 1000 +
      (now.tv_usec - start.tv_usec) / 1000;
      if (diff)
      {
        printf("%i \n", static_cast<int>(current * 100 / total));
      }
    }
    else
    {
      started = true;
      gettimeofday(&start, NULL);
    }
    // printf("%ld/%ld\n", current, total);
  }

  void diff(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
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
    int ret = bsdiff(error, *oldfile, *newfile, *patchfile, &callback);   
    if(ret != 0) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, error)));
    }        
  }

  void patch(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
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
    }    
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "diff", diff);
    NODE_SET_METHOD(exports, "patch", patch);
  }

  NODE_MODULE(bsdp, init)
}