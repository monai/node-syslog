#include <node.h>
#include <nan.h>
#include "async.h"

#include <syslog.h>

using v8::Local;
using v8::Number;
using v8::Value;

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
    NanScope();
    
    Local<Value> argv[] = {
        NanNull()
      , NanNew<Number>(out)
    };
    
    callback->Call(2, argv);
};

void SyslogWorker::Execute () {
    syslog(priority, "%s", **message);
}
