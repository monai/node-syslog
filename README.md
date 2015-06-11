# node-syslog

[![Build Status](http://img.shields.io/travis/monai/node-syslog/develop.svg)](https://travis-ci.org/monai/node-syslog)
[![NPM Version](http://img.shields.io/npm/v/syslog-bindings.svg)](https://www.npmjs.org/package/syslog-bindings)

Node.js bindings to syslog.

## API

API is as close as possible to `man 3 syslog`.

### closelog()

See manpage for details.

### openlog(ident, logopt, facility)

See manpage for details.

### setlogmask(maskpri)

Returns previous log mask level.

See manpage for details.

### syslog(priority, message)

`printf` functionality is suppressed by always interpolating `message` as `%s`.

See manpage for details.

### prioritynames

An object with human readable priority names.

See `<sys/syslog.h>` for details.

### facilitynames

An object with human readable facility names.

See `<sys/syslog.h>` for details.

### Constants

Following constants are exported.

Priorities:

- LOG_EMERG
- LOG_ALERT
- LOG_CRIT
- LOG_ERR
- LOG_WARNING
- LOG_NOTICE
- LOG_INFO
- LOG_DEBUG

Facilities:

- LOG_KERN
- LOG_USER
- LOG_MAIL
- LOG_DAEMON
- LOG_AUTH
- LOG_SYSLOG
- LOG_LPR
- LOG_NEWS
- LOG_UUCP
- LOG_CRON
- LOG_AUTHPRIV
- LOG_FTP
- LOG_LOCAL0
- LOG_LOCAL1
- LOG_LOCAL2
- LOG_LOCAL3
- LOG_LOCAL4
- LOG_LOCAL5
- LOG_LOCAL6
- LOG_LOCAL7

Openlog options:

- LOG_PID
- LOG_CONS
- LOG_ODELAY
- LOG_NDELAY
- LOG_NOWAIT
- LOG_PERROR

Internals:

- INTERNAL_NOPRI
- INTERNAL_MARK

## License

ISC
