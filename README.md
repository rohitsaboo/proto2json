Setup
-----

Run `./setup.sh` to install the necessary dependencies in order to run this 
tool.

Running
-------

Example
```
$ ./proto2json.sh --schema=test/test.proto --root=Recording --in=test/test.pb --out=out.json
```

Limitations
-----------

* This has been barely tested or written in a clean way.
* It only operates with protobuf schemas that do not have dependencies in other 
  files.
* Pull requests are welcome to clean up, have a better setup, extend 
  functionality, etc.
