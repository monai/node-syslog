#ifndef ASYNC_H
#define ASYNC_H

#include <nan.h>

using Nan::AsyncWorker;
using Nan::Callback;
using Nan::Utf8String;

class CloselogWorker : public AsyncWorker {
    public:
        CloselogWorker(Callback *callback)
        : AsyncWorker(callback) {}
        ~CloselogWorker() {}
        void Execute();
};

class OpenlogWorker : public AsyncWorker {
    public:
        OpenlogWorker(Callback *callback, Utf8String *ident, int logopt, int facility)
        : AsyncWorker(callback), ident(ident), logopt(logopt), facility(facility) {}
        ~OpenlogWorker() {}
        void Execute();
    private:
        Utf8String *ident;
        int logopt;
        int facility;
};

class SetlogmaskWorker : public AsyncWorker {
    public:
        SetlogmaskWorker(Callback *callback, int maskpri)
        : AsyncWorker(callback), maskpri(maskpri) {}
        ~SetlogmaskWorker() {}
        void Execute();
        void HandleOKCallback();
    private:
        int maskpri;
        int out;
};

class SyslogWorker : public AsyncWorker {
    public:
        SyslogWorker(Callback *callback, int priority, Utf8String *message)
        : AsyncWorker(callback), priority(priority), message(message) {}
        ~SyslogWorker() {}
        void Execute();
    private:
        int priority;
        Utf8String *message;
};

NAN_METHOD(CloselogAsync);
NAN_METHOD(OpenlogAsync);
NAN_METHOD(SetlogmaskAsync);
NAN_METHOD(SyslogAsync);

#endif