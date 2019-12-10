/*
**	MIT License
**
**	Copyright (c) 2018-2019 Exoway
**
**	Permission is hereby granted, free of charge, to any person obtaining a copy
**	of this software and associated documentation files (the "Software"), to deal
**	in the Software without restriction, including without limitation the rights
**	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
**	copies of the Software, and to permit persons to whom the Software is
**	furnished to do so, subject to the following conditions:
**
**	The above copyright notice and this permission notice shall be included in all
**	copies or substantial portions of the Software.
**
**	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
**	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
**	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
**	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
**	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
**	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
**	SOFTWARE.
**
*/

#include "PatchWorkerCallback.hpp"

extern "C" {
  #include "c/bspatch/bspatch.h"
}

// Public
PatchWorkerCallback::PatchWorkerCallback(Nan::Callback *callback, const std::string& oldfile, const std::string& newfile, const std::string& patchfile)
    : AsyncProgressWorkerBase(callback)
{
  _oldfile = oldfile;
  _newfile = newfile;
  _patchfile = patchfile;
}

PatchWorkerCallback::~PatchWorkerCallback()
{   }

void PatchWorkerCallback::Execute(const ExecutionProgress& progress)
{
    char error[1024];
    memset(error, 0, sizeof error);

    PatchWorkerData data;
    data.percentage = 0;
    data.progressWorker = &progress;

    bspatch(error, _oldfile.c_str(), _newfile.c_str(), _patchfile.c_str(), &data, &PatchWorkerCallback::CCallback);
    _error = error;
}

void PatchWorkerCallback::HandleProgressCallback(const int* data, size_t count)
{
    if(data != nullptr)
    {
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            v8::Number::New(v8::Isolate::GetCurrent(), *data),
            Nan::New<v8::String>(_error.c_str()).ToLocalChecked()
        };

        callback->Call(2, argv, this->async_resource);
    }
}

void PatchWorkerCallback::HandleOKCallback()
{
    v8::Local<v8::Value> argv[] = {
        v8::Number::New(v8::Isolate::GetCurrent(), 100),
        Nan::New<v8::String>(_error.c_str()).ToLocalChecked()
    };
    callback->Call(2, argv, this->async_resource);
}

