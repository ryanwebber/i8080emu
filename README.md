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
Each of the opcodes in Bloom are unit tested. A cpu state is created and given to the opcode unit test, which allocates memory at the program counter (usually offset 0). The cpu is stepped and the new state is compared to the expected new state. Memory writes are also asserted on where applicable, along with changes to the program counter, stack pointer, and in important cases, the cpu flags.

The tests can be run using:
```
$ make test
```

For more details of test failures, run:
```
./test/run_tests > /dev/null
```

## Debugging Bloom
A correct implementation of the Intel 8080 cpu can be built with Bloom and will be executed step-by-step alongside Bloom until the two states diverge. The debugger will panic, print, and exit at this point. When this happens, it indicates a bug in Bloom not caught in the tests has caused the cpu to start executing incorrectly. 

Note that there may be bugs in the 'correct' implementation of the Intel 8080 emulator but this is less likely than one being in this project. 

To run the debugger:
```
$ cd debug
$ make
$ ./bloomdbg <rom file>
```

