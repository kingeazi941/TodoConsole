# TodoConsole

A simple command-line Todo application written in **modern C++17** using only the Standard Library.

## Features

- Add, complete, and delete tasks
- Priority levels (Low / Medium / High)
- Optional due dates
- Filter tasks (All, Pending, High Priority)
- Persistent storage using a text file

## Technologies

- C++17
- STL only (`vector`, `optional`, `string`, `fstream`, etc.)
- CMake

## How to Build

```bash
git clone https://github.com/kingeazi941/TodoConsole.git
cd TodoConsole
mkdir build && cd build
cmake ..
cmake --build .
./TodoConsole
```

## Project Structure
TodoConsole/

├── main.cpp

├── Task.h

├── Storage.h

├── Storage.cpp

└── CMakeLists.txt

## Author
**Afun Ezekiel**
## License
This project is open source and available under the MIT License.