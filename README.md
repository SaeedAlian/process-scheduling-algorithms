# Project: PSA Simulator

## Description

This project implements a process scheduling algorithm simulator. It allows users to specify scheduling algorithms, input data, and output configurations. The program processes input and generates output files for the specified algorithms.

## Features

- Support for multiple scheduling algorithms (e.g., FCFS, SJF, LJF, etc.).
- Input and output file management.
- Debug and release build configurations.
- Valgrind support for memory analysis.

## File Structure

```
process-scheduling-algorithms/
|-- Makefile            # Build system
|-- ex_input.txt        # Sample input file
|-- include/            # Header files
|   |-- args.h
|   |-- algorithms.h
|   |-- proc.h
|   |-- queue.h
|   |-- util.h
|-- src/                # Source files
|   |-- args.c
|   |-- algorithms.c
|   |-- main.c
|   |-- proc.c
|   |-- queue.c
|   |-- util.c
|-- bin/                # Generated binaries (created during build)
|   |-- psa             # Generated for release version
|   |-- psa_debug       # Generated for debug version
```

## Prerequisites

- G++ (or any compatible C compiler)
- Make

## Build Instructions

1. Open a terminal and navigate to the project directory.
2. Run the following command to build the release version:

   ```bash
   make
   ```

   The binary will be located at `bin/psa`.

3. To build the debug version:
   ```bash
   make build-debug
   ```
   The debug binary will be located at `bin/psa_debug`.

## Usage

### Running the Program

To run the program, use the following command:

```bash
./bin/psa -a <algorithms> -q <quantum> -c <context_switch_time> -i <input_file> -o <output_directory>
```

#### Example:

```bash
./bin/psa -a fcfs,sjf,lrjf -q 1 -c 1 -i ./input.txt -o ./outputs
```

#### Or you can ask for help with:

```bash
./bin/psa --help
```

### Debugging

To run the program in `gdb` and pass arguments:

```bash
make debug ARGS="-a <algorithms> -q <quantum> -c <context_switch_time> -i <input_file> -o <output_directory>
```

### Memory Leak Checks

To run the program with Valgrind and pass arguments:

```bash
make valgrind ARGS="-a <algorithms> -q <quantum> -c <context_switch_time> -i <input_file> -o <output_directory>
```

## Cleaning Up

To clean up build files and binaries, run:

```bash
make clean
```

## Contributing

Feel free to contribute by submitting issues or pull requests. Ensure all contributions adhere to the project's coding style and are thoroughly tested.

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE.
