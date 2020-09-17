#ifndef PatchWorkerCallback_H
#define PatchWorkerCallback_H

#include <nan.h>
#include <sys/types.h>

struct PatchWorkerData {
    int percentage;
    const Nan::AsyncBareProgressWorker<int>::ExecutionProgress* progressWorker;
};

class PatchWorkerCallback : public Nan::AsyncProgressWorkerBase<int> 
{
public:
    PatchWorkerCallback(Nan::Callback *callback, const std::string& oldfile, const std::string& newfile, const std::string& patchfile);
    ~PatchWorkerCallback();

    virtual void Execute(const ExecutionProgress& progress);
    virtual void HandleProgressCallback(const int* data, size_t count);
    virtual void HandleOKCallback();

private:
    static void CCallback(off_t current, off_t total, void* data)
    {
        ((PatchWorkerData*)data)->percentage = static_cast<int>(current * 100 / total);
        ((PatchWorkerData*)data)->progressWorker->Send(&((PatchWorkerData*)data)->percentage, 2);
    }

private:
    std::string _oldfile, _newfile, _patchfile;
    std::string _error;
};

#endif  // PatchWorkerCallback_H