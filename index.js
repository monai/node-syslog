var bindings;

try {
    bindings = require('bindings')('syslog');
} catch (ex) {
    if (process.platform == 'win32') {
        bindings = new Error('Platform win32 is not supported');
    } else {
        throw ex;
    }
}

module.exports = bindings;
