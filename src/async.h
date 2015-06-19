#ifndef ASYNC_H
#define ASYNC_H

#include <nan.h>

class CloselogWorker : public NanAsyncWorker {
    public:
        CloselogWorker(NanCallback *callback)
        : NanAsyncWorker(callback) {}
        ~CloselogWorker() {}
        void Execute();
};

class OpenlogWorker : public NanAsyncWorker {
    public:
        OpenlogWorker(NanCallback *callback, NanUtf8String *ident, int logopt, int facility)
        : NanAsyncWorker(callback), ident(ident), logopt(logopt), facility(facility) {}
        ~OpenlogWorker() {}
        void Execute();
    private:
        NanUtf8String *ident;
        int logopt;
        int facility;
};

class SetlogmaskWorker : public NanAsyncWorker {
    public:
        SetlogmaskWorker(NanCallback *callback, int maskpri)
        : NanAsyncWorker(callback), maskpri(maskpri) {}
        ~SetlogmaskWorker() {}
        void Execute();
        void HandleOKCallback();
    private:
        int maskpri;
        int out;
};

class SyslogWorker : public NanAsyncWorker {
    public:
        SyslogWorker(NanCallback *callback, int priority, NanUtf8String *message)
        : NanAsyncWorker(callback), priority(priority), message(message) {}
        ~SyslogWorker() {}
        void Execute();
    private:
        int priority;
        NanUtf8String *message;
};

NAN_METHOD(CloselogAsync);
NAN_METHOD(OpenlogAsync);
NAN_METHOD(SetlogmaskAsync);
NAN_METHOD(SyslogAsync);

#endif