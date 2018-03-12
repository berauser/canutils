# CANUTILS #

Canutils is a C ++ library for accessing the CAN bus. It abstracts the socket interface of the Linux kernel and provides an interface to query the settings and statistics of the CAN bus. In addition, canutils provides various buffer implementations and a software CAN mux to split the messages.

## Classes ##
### SocketCan ###

Interface to access the CAN bus.

### SocketCanBuffer ###

Interface for various CAN buffer implementations.

### SocketCanStatistics ###

Interface for CAN bus statistics

### SocketCanInfo ###

Interface to query CAN bus and device settings

### SocketCanWorker ###

Interface for software CAN mux.

## Build ##

### Requirements ###

* make
* cmake
* doxygen  (documentation)
* graphviz (documentation)
* ibgtest-dev (testing)
* google-mock (testing)

### compile ###

#### cmake options ####
```
Options        Description               Default
BUILD_EXAMPLE  "Build exmaples"          FALSE
BUILD_TEST     "Build test"              FALSE
BUILD_DOC      "Create documentation"    FALSE
BUILD_PARANOID "Use paranoid gcc checks" TRUE
USE_GCOV       "Enable gcov flags"       FALSE
```
#### execute ####

Build with default settings
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Build with all options
```
$ mkdir build/
$ cd build/
$ cmake -DBUILD_EXAMPLE=ON -DBUILD_TEST=ON -DBUILD_DOC=ON -DBUILD_PARANOID=true -DUSE_GCOV ..
$ make
```

### clean up ####

```
rm -r build/
```

### create documentation ###

Enable the option 'BUILD_DOC' during cmake configuration and execute
```
$ cd build/
$ make doc
```

### Wrapper Makefile ###

There is a wrapper makefile that executes the build steps described above. To use this, the following commands must be executed.

```
$ ln -s makefile.linux Makefile
$ make

# other commands
$ make all          # compile all
$ make install      # install binaries and libraries
$ make clean        # delete compiled sources
$ make dist-clean   # delete cmake work dir
```

## Testing ##

To run the test the cmake option BUILD_TEST must be enabled.

Start vcan interface:
```
$ sudo ./scripts/vcan.sh start vcan0
$ sudo ./scripts/vcan.sh up vcan0
```

### Run tests ###
```
$ ./scripts/run_test.sh
```

### Run code coverage ###
```
$ ./scripts/run_gcov.sh
```

### Run valgrind ###
```
$ ./scripts/run_cppcheck.sh
```

### Run valgrind ###
```
$ ./scripts/run_valgrind.sh
```



