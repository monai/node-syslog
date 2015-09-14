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
using Nan::AsyncQueueWorker;
using Nan::Callback;
using Nan::GetFunction;
using Nan::HandleScope;
using Nan::New;
using Nan::Set;
using Nan::Utf8String;

NAN_METHOD(Closelog) {
    Callback *callback = new Callback(info[0].As<Function>());
    AsyncQueueWorker(new CloselogWorker(callback));
}

NAN_METHOD(CloselogSync) {
    closelog();
}

NAN_METHOD(Openlog) {
    Utf8String *ident = new Utf8String(info[0]);
    int logopt = info[1]->ToInteger()->Int32Value();
    int facility = info[2]->ToInteger()->Int32Value();
    
    Callback *callback = new Callback(info[3].As<Function>());
    AsyncQueueWorker(new OpenlogWorker(callback, ident, logopt, facility));
}

NAN_METHOD(OpenlogSync) {
    Utf8String *ident = new Utf8String(info[0]);
    int logopt = info[1]->ToInteger()->Int32Value();
    int facility = info[2]->ToInteger()->Int32Value();
    
    openlog(**ident, logopt, facility);
}

NAN_METHOD(Setlogmask) {
    int maskpri = info[0]->ToInteger()->Int32Value();
    
    Callback *callback = new Callback(info[1].As<Function>());
    AsyncQueueWorker(new SetlogmaskWorker(callback, maskpri));
}

NAN_METHOD(SetlogmaskSync) {
    int out;
    int maskpri = info[0]->ToInteger()->Int32Value();
    out = setlogmask(LOG_UPTO(maskpri));
    
    info.GetReturnValue().Set(New<Number>(out));
}

NAN_METHOD(Syslog) {
    int priority = info[0]->ToInteger()->Int32Value();
    Utf8String *message = new Utf8String(info[1]);
    Callback *callback = new Callback(info[2].As<Function>());
    AsyncQueueWorker(new SyslogWorker(callback, priority, message));
}

NAN_METHOD(SyslogSync) {
    int priority = info[0]->ToInteger()->Int32Value();
    String::Utf8Value message(info[1]->ToString());
    syslog(priority, "%s", *message);
}

NAN_MODULE_INIT(InitAll) {
    #define EXPORTS_NUMBER(key, value) Set(target, New<String>(key).ToLocalChecked(), New<Number>(value));
    #define EXPORTS_FUNCTION(key, value) Set(target, New<String>(key).ToLocalChecked(), GetFunction(New<FunctionTemplate>(value)).ToLocalChecked());
    
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
    
    Local<Object> priorityNames = New<Object>();
    i = -1;
    while (prioritynames[++i].c_val > -1) {
        Set(priorityNames, New<String>(prioritynames[i].c_name).ToLocalChecked(), New<Number>(prioritynames[i].c_val));
    }
    Set(target, New<String>("prioritynames").ToLocalChecked(), priorityNames);
    
    Local<Object> facilityNames = New<Object>();
    i = -1;
    while (facilitynames[++i].c_val > -1) {
        Set(facilityNames, New<String>(facilitynames[i].c_name).ToLocalChecked(), New<Number>(facilitynames[i].c_val));
    }
    Set(target, New<String>("facilitynames").ToLocalChecked(), facilityNames);
    #endif
}

NODE_MODULE(syslog, InitAll)
