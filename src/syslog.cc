#include <node.h>
#include <nan.h>

#define SYSLOG_NAMES
#include <syslog.h>

#include "async.h"

using v8::Function;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::String;

NAN_METHOD(Closelog) {
    NanScope();
    
    NanCallback *callback = new NanCallback(args[0].As<Function>());
    NanAsyncQueueWorker(new CloselogWorker(callback));
    
    NanReturnUndefined();
}

NAN_METHOD(CloselogSync) {
    NanScope();
    
    closelog();
    
    NanReturnUndefined();
}

NAN_METHOD(Openlog) {
    NanScope();
    
    NanUtf8String *ident = new NanUtf8String(args[0]);
    int logopt = args[1]->ToInteger()->Int32Value();
    int facility = args[2]->ToInteger()->Int32Value();
    
    NanCallback *callback = new NanCallback(args[3].As<Function>());
    NanAsyncQueueWorker(new OpenlogWorker(callback, ident, logopt, facility));
    
    NanReturnUndefined();
}

NAN_METHOD(OpenlogSync) {
    NanScope();
    
    NanUtf8String *ident = new NanUtf8String(args[0]);
    int logopt = args[1]->ToInteger()->Int32Value();
    int facility = args[2]->ToInteger()->Int32Value();
    
    openlog(**ident, logopt, facility);
    
    NanReturnUndefined();
}

NAN_METHOD(Setlogmask) {
    NanScope();
    
    int maskpri = args[0]->ToInteger()->Int32Value();
    
    NanCallback *callback = new NanCallback(args[1].As<Function>());
    NanAsyncQueueWorker(new SetlogmaskWorker(callback, maskpri));
    
    NanReturnUndefined();
}

NAN_METHOD(SetlogmaskSync) {
    NanScope();
    
    int out;
    int maskpri = args[0]->ToInteger()->Int32Value();
    out = setlogmask(LOG_UPTO(maskpri));
    
    NanReturnValue(NanNew<Number>(out));
}

NAN_METHOD(Syslog) {
    NanScope();
    
    int priority = args[0]->ToInteger()->Int32Value();
    NanUtf8String *message = new NanUtf8String(args[1]);
    NanCallback *callback = new NanCallback(args[2].As<Function>());
    NanAsyncQueueWorker(new SyslogWorker(callback, priority, message));
    
    NanReturnUndefined();
}

NAN_METHOD(SyslogSync) {
    NanScope();
    
    int priority = args[0]->ToInteger()->Int32Value();
    String::Utf8Value message(args[1]->ToString());
    syslog(priority, "%s", *message);
    
    NanReturnUndefined();
}

void InitAll(Handle<Object> exports) {
    #define EXPORTS_NUMBER(key, value) exports->Set(NanNew<String>(key), NanNew<Number>(value));
    #define EXPORTS_FUNCTION(key, value) exports->Set(NanNew<String>(key), NanNew<FunctionTemplate>(value)->GetFunction());
    
    // priorities
    EXPORTS_NUMBER("LOG_EMERG", LOG_EMERG);
    EXPORTS_NUMBER("LOG_ALERT", LOG_ALERT);
    EXPORTS_NUMBER("LOG_CRIT", LOG_CRIT);
    EXPORTS_NUMBER("LOG_ERR", LOG_ERR);
    EXPORTS_NUMBER("LOG_WARNING", LOG_WARNING);
    EXPORTS_NUMBER("LOG_NOTICE", LOG_NOTICE);
    EXPORTS_NUMBER("LOG_INFO", LOG_INFO);
    EXPORTS_NUMBER("LOG_DEBUG", LOG_DEBUG);
    
    // facilities
    EXPORTS_NUMBER("LOG_KERN", LOG_KERN);
    EXPORTS_NUMBER("LOG_USER", LOG_USER);
    EXPORTS_NUMBER("LOG_MAIL", LOG_MAIL);
    EXPORTS_NUMBER("LOG_DAEMON", LOG_DAEMON);
    EXPORTS_NUMBER("LOG_AUTH", LOG_AUTH);
    EXPORTS_NUMBER("LOG_SYSLOG", LOG_SYSLOG);
    EXPORTS_NUMBER("LOG_LPR", LOG_LPR);
    EXPORTS_NUMBER("LOG_NEWS", LOG_NEWS);
    EXPORTS_NUMBER("LOG_UUCP", LOG_UUCP);
    EXPORTS_NUMBER("LOG_CRON", LOG_CRON);
    EXPORTS_NUMBER("LOG_AUTHPRIV", LOG_AUTHPRIV);
    EXPORTS_NUMBER("LOG_FTP", LOG_FTP);

    EXPORTS_NUMBER("LOG_LOCAL0", LOG_LOCAL0);
    EXPORTS_NUMBER("LOG_LOCAL1", LOG_LOCAL1);
    EXPORTS_NUMBER("LOG_LOCAL2", LOG_LOCAL2);
    EXPORTS_NUMBER("LOG_LOCAL3", LOG_LOCAL3);
    EXPORTS_NUMBER("LOG_LOCAL4", LOG_LOCAL4);
    EXPORTS_NUMBER("LOG_LOCAL5", LOG_LOCAL5);
    EXPORTS_NUMBER("LOG_LOCAL6", LOG_LOCAL6);
    EXPORTS_NUMBER("LOG_LOCAL7", LOG_LOCAL7);
    
    // openlog options
    EXPORTS_NUMBER("LOG_PID", LOG_PID);
    EXPORTS_NUMBER("LOG_CONS", LOG_CONS);
    EXPORTS_NUMBER("LOG_ODELAY", LOG_ODELAY);
    EXPORTS_NUMBER("LOG_NDELAY", LOG_NDELAY);
    EXPORTS_NUMBER("LOG_NOWAIT", LOG_NOWAIT);
    EXPORTS_NUMBER("LOG_PERROR", LOG_PERROR);
    
    EXPORTS_FUNCTION("closelog", Closelog);
    EXPORTS_FUNCTION("closelogSync", CloselogSync);
    EXPORTS_FUNCTION("openlog", Openlog);
    EXPORTS_FUNCTION("openlogSync", OpenlogSync);
    EXPORTS_FUNCTION("setlogmask", Setlogmask);
    EXPORTS_FUNCTION("setlogmaskSync", SetlogmaskSync);
    EXPORTS_FUNCTION("syslog", Syslog);
    EXPORTS_FUNCTION("syslogSync", SyslogSync);
    
    #ifdef SYSLOG_NAMES
    EXPORTS_NUMBER("INTERNAL_NOPRI", INTERNAL_NOPRI);
    EXPORTS_NUMBER("INTERNAL_MARK", INTERNAL_MARK);
    
    int i;
    
    Local<Object> priorityNames = NanNew<Object>();
    i = -1;
    while (prioritynames[++i].c_val > -1) {
        priorityNames->Set(NanNew<String>(prioritynames[i].c_name), NanNew<Number>(prioritynames[i].c_val));
    }
    exports->Set(NanNew<String>("prioritynames"), priorityNames);
    
    Local<Object> facilityNames = NanNew<Object>();
    i = -1;
    while (facilitynames[++i].c_val > -1) {
        facilityNames->Set(NanNew<String>(facilitynames[i].c_name), NanNew<Number>(facilitynames[i].c_val));
    }
    exports->Set(NanNew<String>("facilitynames"), facilityNames);
    #endif
}

NODE_MODULE(syslog, InitAll)
