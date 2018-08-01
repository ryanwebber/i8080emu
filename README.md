# Bloom
An intel 8080 emulator written in C. 

## Getting Started

Build the project as follows:
```
$ git clone git@github.com:ryanwebber/bloom.git
$ cd bloom
$ cmake .
$ make
```

This will build the Bloom executable as well as the libbloom library.

## Running Bloom
Running the executable:
```
$ ./src/main <rom file>
```

## Testing
You can make the tests with a top level `$ make`, or a `$ make` from the test dir. 
The tests can be run with:
```
$ make test
```

For more details of test failures, run:
```
./test/check_bloom
```

