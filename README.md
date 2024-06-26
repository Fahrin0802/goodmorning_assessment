# goodmorning_assessment

## Summary
The MyRequest project is aimed at providing a framework for processing requests at various URIs while tracking processing times. It includes a derived class `MyRequest` from the base class `Request`, enabling users to start, finish, and analyze processing times for different URIs.

### Prerequisites
- `g++`: Install a C++ compiler on your system.
- Python Development Headers: Required as we will use matplotlib for drawing histograms
  - On Linux, you can install them using:
    ```sh
    sudo apt-get install python3-dev
    ```

### Third party Libraries used
- [MatplotLibcpp.h](https://github.com/lava/matplotlib-cpp)
- [doctest.h](https://github.com/doctest/doctest/blob/master/doc/markdown/readme.md)

### Compilation Steps
1. Clone the project repository from [GitHub](https://github.com/Fahrin0802/goodmorning_assessment.git).
2. Navigate to the project directory.
3. Open the `Makefile` and update the `CXXFLAGS` variable to include your python path
    - python path can be found using the command
    ```
        python3-config --include
    ```
4. Update main.cpp to input your URIs that need processing
5. Compile the project by running:
   ```sh
   make all
   ```

### Running the project
```sh
   ./app
```

### Running Tests
```sh
   make test
```
