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

#ifndef DiffWorkerCallback_H
#define DiffWorkerCallback_H

#include <nan.h>
#include <sys/types.h>

struct DiffWorkerData {
    int percentage;
    const Nan::AsyncBareProgressWorker<int>::ExecutionProgress* progressWorker;
};

class DiffWorkerCallback : public Nan::AsyncProgressWorkerBase<int> 
{
public:
    DiffWorkerCallback(Nan::Callback *callback, const std::string& oldfile, const std::string& newfile, const std::string& patchfile);
    ~DiffWorkerCallback();

    virtual void Execute(const ExecutionProgress& progress);
    virtual void HandleProgressCallback(const int* data, size_t count);
    virtual void HandleOKCallback();

private:
    static void CCallback(off_t current, off_t total, void* data)
    {
        ((DiffWorkerData*)data)->percentage = static_cast<int>(current * 100 / total);
        ((DiffWorkerData*)data)->progressWorker->Send(&((DiffWorkerData*)data)->percentage, 2);
    }

private:
    std::string _oldfile, _newfile, _patchfile;
    std::string _error;
};

#endif  // DiffWorkerCallback_H