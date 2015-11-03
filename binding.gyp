{
  "targets": [
    {
      "target_name": "syslog",
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "conditions": [
        ["OS!='win'", {
          "sources": [ "src/async.cc", "src/syslog.cc" ],
        }]
      ]
    },
  ]
}
