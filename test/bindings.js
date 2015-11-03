var assert = require('assert');
var bindings = require('../');

if (bindings === null) {
    console.log('Platform %s is not supported', process.platform);
    process.exit(0);
}

describe('syslog bindings', function (done) {
    describe('constants', function () {
        function makeConstantTest(name, actual, expected) {
            it(name +' === '+ expected, function () {
                assert.strictEqual(actual, expected);
            });
        }
        
        describe('priorities', function () {
            makeConstantTest('LOG_EMERG', bindings.LOG_EMERG, 0);
            makeConstantTest('LOG_ALERT', bindings.LOG_ALERT, 1);
            makeConstantTest('LOG_CRIT', bindings.LOG_CRIT, 2);
            makeConstantTest('LOG_ERR', bindings.LOG_ERR, 3);
            makeConstantTest('LOG_WARNING', bindings.LOG_WARNING, 4);
            makeConstantTest('LOG_NOTICE', bindings.LOG_NOTICE, 5);
            makeConstantTest('LOG_INFO', bindings.LOG_INFO, 6);
            makeConstantTest('LOG_DEBUG', bindings.LOG_DEBUG, 7);
        });
        
        describe('facilities', function () {
            makeConstantTest('LOG_KERN', bindings.LOG_KERN, 0 << 3);
            makeConstantTest('LOG_USER', bindings.LOG_USER, 1 << 3);
            makeConstantTest('LOG_MAIL', bindings.LOG_MAIL, 2 << 3);
            makeConstantTest('LOG_DAEMON', bindings.LOG_DAEMON, 3 << 3);
            makeConstantTest('LOG_AUTH', bindings.LOG_AUTH, 4 << 3);
            makeConstantTest('LOG_SYSLOG', bindings.LOG_SYSLOG, 5 << 3);
            makeConstantTest('LOG_LPR', bindings.LOG_LPR, 6 << 3);
            makeConstantTest('LOG_NEWS', bindings.LOG_NEWS, 7 << 3);
            makeConstantTest('LOG_UUCP', bindings.LOG_UUCP, 8 << 3);
            makeConstantTest('LOG_CRON', bindings.LOG_CRON, 9 << 3);
            makeConstantTest('LOG_AUTHPRIV', bindings.LOG_AUTHPRIV, 10 << 3);
            makeConstantTest('LOG_FTP', bindings.LOG_FTP, 11 << 3);
            
            makeConstantTest('LOG_LOCAL0', bindings.LOG_LOCAL0, 16 << 3);
            makeConstantTest('LOG_LOCAL1', bindings.LOG_LOCAL1, 17 << 3);
            makeConstantTest('LOG_LOCAL2', bindings.LOG_LOCAL2, 18 << 3);
            makeConstantTest('LOG_LOCAL3', bindings.LOG_LOCAL3, 19 << 3);
            makeConstantTest('LOG_LOCAL4', bindings.LOG_LOCAL4, 20 << 3);
            makeConstantTest('LOG_LOCAL5', bindings.LOG_LOCAL5, 21 << 3);
            makeConstantTest('LOG_LOCAL6', bindings.LOG_LOCAL6, 22 << 3);
            makeConstantTest('LOG_LOCAL7', bindings.LOG_LOCAL7, 23 << 3);
        });
        
        describe('openlog options', function () {
            makeConstantTest('LOG_PID', bindings.LOG_PID, 0x01);
            makeConstantTest('LOG_CONS', bindings.LOG_CONS, 0x02);
            makeConstantTest('LOG_ODELAY', bindings.LOG_ODELAY, 0x04);
            makeConstantTest('LOG_NDELAY', bindings.LOG_NDELAY, 0x08);
            makeConstantTest('LOG_NOWAIT', bindings.LOG_NOWAIT, 0x10);
            makeConstantTest('LOG_PERROR', bindings.LOG_PERROR, 0x20);
        });
        
        describe('priority names', function () {
            it('should exist object "prioritynames"', function () {
                assert.ok(typeof bindings.prioritynames == 'object');
            });
        });
        
        describe('facility names', function () {
            it('should exist object "facilitynames"', function () {
                assert.ok(typeof bindings.facilitynames == 'object');
            });
        });
    });
    
    describe('functions', function () {
        [
            'closelog', 'openlog', 'setlogmask', 'syslog',
            'closelogSync', 'openlogSync', 'setlogmaskSync', 'syslogSync'
        ].forEach(function (func) {
            it('should exist function "'+ func +'"', function () {
                assert.strictEqual(typeof bindings[func], 'function');
            });
        });
    });
});
