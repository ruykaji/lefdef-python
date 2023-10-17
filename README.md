# LEFDEF Python

This repository provides a Python interface to parse LEF (Library Exchange Format) and DEF (Design Exchange Format) files. The project is designed to read LEF files and extract relevant information about the design.

## Features

- **LEF Reader**: A Python class `C_LefReader` that allows reading LEF files and extracting the design data. [View Code](https://github.com/ruykaji/lefdef-python/blob/main/lefdef/lef_reader.py)
  
- **LEF Data Structures**: The repository defines various data structures to represent the design elements in a LEF file, such as `C_Lef`, `C_Macro`, `C_Pin`, `C_Port`, `C_Rect`, and `C_Obstruction`. These structures provide a Pythonic way to access the design data. [View Code](https://github.com/ruykaji/lefdef-python/blob/main/lefdef/lef.py)

- **Test Script**: A simple test script to demonstrate the usage of the LEF reader. [View Code](https://github.com/ruykaji/lefdef-python/blob/main/test.py)

## Usage

To use the LEF reader, you can follow the example provided in the `test.py` file:

```python
from lefdef import C_LefReader

lef_reader = C_LefReader()
lef = lef_reader.read("/path/to/your/LEF/file.lef")
```

## Building the Library using CMake

1. **Prerequisites**: Ensure you have CMake (version 3.19 or higher) installed on your system.

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/ruykaji/lefdef-python.git
   cd lefdef-python
   ```

3. **Create a Build Directory**:
   ```bash
   mkdir build
   cd build
   ```

4. **Run CMake**:
   ```bash
   cmake ..
   ```

5. **Build the Project**:
   ```bash
   make
   ```

6. **Install the Library**:
   After building, you can install the `lefdef` shared library to the `lefdef/lib/` directory within the repository:
   ```bash
   make install
   ```

This will produce an executable named `test` and a shared library named `lefdef`. The library links against the external DEF and LEF libraries provided in the repository.

You can view the CMake configuration file [here](https://github.com/ruykaji/lefdef-python/blob/main/CMakeLists.txt).

Certainly! Here's a draft for the "Contribution" section that you can add to the README:

---

## Contributing

We welcome contributions from the community! Whether it's a bug report, new feature, or a correction, your help is greatly appreciated. Here's how you can contribute:

1. **Fork the Repository**: Start by forking the [lefdef-python repository](https://github.com/ruykaji/lefdef-python).

2. **Clone Your Fork**:
   ```bash
   git clone https://github.com/YOUR_USERNAME/lefdef-python.git
   cd lefdef-python
   ```

3. **Create a New Branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

4. **Make Your Changes**: Implement your changes, enhancements, or bug fixes.

5. **Commit and Push**:
   ```bash
   git add .
   git commit -m "Your detailed commit message"
   git push origin feature/your-feature-name
   ```

6. **Open a Pull Request**: Go to the [lefdef-python repository](https://github.com/ruykaji/lefdef-python) on GitHub and click on the "New Pull Request" button. Select your fork and the branch you created to submit a pull request.

7. **Wait for Review**: Once your pull request is submitted, maintainers will review your changes. Address any feedback to get your changes merged.

### Reporting Bugs

If you find a bug or an issue, please create a new issue in the [issue tracker](https://github.com/ruykaji/lefdef-python/issues) describing the problem and providing steps to reproduce it.