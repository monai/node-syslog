var bindings;

try {
    bindings = require('bindings')('syslog');
} catch (ex) {
    if (process.platform == 'win32') {
        bindings = null;
    } else {
        throw ex;
    }
}

module.exports = bindings;
