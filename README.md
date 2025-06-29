# Virtual Memory Simulation

## Overview

This project demonstrates how virtual memory works in modern operating systems by allocating a large memory block (e.g., 2 GB or more) in C++. The program measures access times for both sequential and random memory access patterns and shows how performance changes when memory usage exceeds available physical RAM, causing the operating system to use swap space.
Python scripts are provided for monitoring the process memory usage and visualizing it over time.

## Problem Description

Operating systems provide each process with an isolated *virtual memory* space, which may be much larger than the available physical RAM. When a program requests more memory than is physically present, the OS swaps out less-used memory pages to disk (swap), causing performance to drop dramatically.
This project lets you observe this behavior in practice by allocating a large array, accessing it in different ways, and measuring how long each operation takes. With the included monitoring and plotting scripts, you can visualize the actual memory usage of your process.

## Explanation of Key Topics

* **Virtual memory:** Each process gets its own large address space, mapped onto physical RAM by the OS.
* **Swap:** Disk space used as an extension of RAM when physical memory is full; access to swapped pages is much slower.
* **Sequential vs. random access:** Sequential access is cache-friendly and fast; random access becomes extremely slow if data is swapped out.
* **Timing:** The code uses `std::chrono` to measure how long each access pattern takes.

## Example Output

```
Allocating 536870912 ints (2048 MB)...

Sequential write time:      1.62199 seconds
Random read time:           19.4535 seconds

Sleeping for 30 seconds for system analysis...
```

If the allocated memory exceeds your available RAM, the random access time will increase drastically due to swapping.

## Explanation of Output

* **Sequential write time:** Time to write through the array in linear order. This is typically fast due to good cache and prefetch performance.
* **Random read time:** Time to sum the array in random order. If the array does not fit in RAM, this will be much slower due to page faults and swapping.
* **Sleeping for 30 seconds:** The program sleeps to give you a chance to inspect memory usage via tools (`top`, `htop`, etc.) or the provided monitoring script.

## Example: Heap Memory Usage Graph (Linux)

Below is an example of a memory usage graph generated by the provided monitoring and plotting scripts on a Linux system:

![heap_plot](https://github.com/user-attachments/assets/5da6caca-ce65-4aa7-9586-346d73376420)

**Interpretation:**

* The sharp increase at the start shows when the process allocates and initializes the large memory block.
* Memory usage then remains high and stable until the process terminates.
* If physical memory is insufficient, you would see system swap usage increase as well.

## How to Compile and Run

### 1. Clone the Repository

```sh
git clone https://github.com/LyudmilaKostanyan/Virtual-Memory-Simulation.git
cd Virtual-Memory-Simulation
```

### 2. Build the Project

Make sure you have a C++17 (or newer) compiler and CMake installed.

```sh
cmake -S . -B build
cmake --build build
```

### 3. Run the Program

#### On Linux/macOS

```sh
cd build
./main
```

#### On Windows

```sh
cd build
main.exe
```

### 4. Monitor Memory Usage (Optional)

#### Install required Python packages:

```sh
pip install psutil matplotlib
```

#### Run the memory monitoring script:

```sh
python monitor.py --duration 40 --executable ./build/main --log-file monitor_output.txt
```

* `--duration` - monitoring duration in seconds
* `--executable` - path to your program (use `main.exe` for Windows)
* `--log-file` - path to the log file to be written

#### Generate the memory usage plot:

```sh
python plot_memory.py --log-file monitor_output.txt --output heap_plot.png
```

* `--log-file` - the CSV file produced by the monitoring script
* `--output` - name of the output PNG image

## Parameters

**C++ program:**
Does not take command line parameters; memory size and other behavior are set in the source code (`num_elements`). You can adjust them if needed.

**monitor.py:**

* `--duration` (int): Total monitoring time in seconds.
* `--executable` (str): Path to the program you want to monitor.
* `--log-file` (str): Path to the CSV file for saving the memory usage log.

**plot\_memory.py:**

* `--log-file` (str): The CSV log file produced by monitor.py.
* `--output` (str): Name of the PNG image to be created.

## Full Example Workflow

```sh
# 1. Build and move to build folder
cmake -S . -B build
cmake --build build
cd build

# 2. Run memory monitoring (Linux example)
python ../monitor.py --duration 40 --executable ./main --log-file monitor_output.txt

# 3. Generate the memory usage plot
python ../plot_memory.py --log-file monitor_output.txt --output heap_plot.png
```

