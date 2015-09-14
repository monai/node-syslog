#include <node.h>
#include <nan.h>
#include "async.h"

#include <syslog.h>

using v8::Local;
using v8::Number;
using v8::Value;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;

void CloselogWorker::Execute () {
    closelog();
}

void OpenlogWorker::Execute () {
    openlog(**ident, logopt, facility);
}

void SetlogmaskWorker::Execute () {
    out = setlogmask(LOG_UPTO(maskpri));
}

void SetlogmaskWorker::HandleOKCallback () {
    Local<Value> argv[] = {
        Null()
      , New<Number>(out)
    };
    
    callback->Call(2, argv);
};

void SyslogWorker::Execute () {
    syslog(priority, "%s", **message);
}
