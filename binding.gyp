{
  "targets": [
    {
      "target_name": "syslog",
      "sources": [ "src/async.cc", "src/syslog.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    },
  ]
}
