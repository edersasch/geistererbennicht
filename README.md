# Geister erben nicht Solution Helper

- letter extraction and pictures for German version of "Geister erben nicht"
  puzzle
- [Manual](docs/manuals/geistererbennicht_en.md) [Anleitung](docs/manuals/geistererbennicht_de.md)
- Available under [MIT license](LICENSE)


# Build Requirements

- C++ 17 toolchain (e.g. [gcc](https://gcc.gnu.org/) >= 7.3.0)
- [CMake](https://cmake.org) >= 3.16.0
- [Qt](https://qt.io) >= 5.15.0


# Optional Tools

- [GTest](https://github.com/google/googletest) >= 1.15.2, downloaded automatically if option `GEISTERERBENNICHT_BUILD_TESTS` is `ON`
- [Pandoc](https://pandoc.org) >= 2.19 enables `manuals` build target


# Directory Structure

The top level structure follows [the pitchfork layout](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs).


- `data/`: Pictures
- `docs/`: Manuals, [Changelog.md](docs/Changelog.md)
- `src/`: Source code
- `tests/`:
  - Unit tests are
[placed separately](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs#src.tests.separate).
  - Naming unit test files is done as described in the pitchfork paragraph
[Merged Test Placement](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs#src.tests.merged).


# Included Resources

CMake file `AddGoogleTest.cmake` adapted from
<https://github.com/CLIUtils/cmake/blob/4e52e4d0bc2e9fd27171926d0b5d9f396dd8637c/AddGoogleTest.cmake>
is licensed under a
[BSD 3-Clause License](https://github.com/CLIUtils/cmake/blob/master/LICENSE) ([local copy](docs/LICENSE_CLIUtils_cmake)):
use URL instead of GIT, remove old DownloadProject method for old cmake

CMake file `DeployQt.cmake` adapted from <https://github.com/nitroshare/nitroshare-desktop/blob/f4feebef29d9d3985d1699ab36f0fac59d3df7da/cmake/DeployQt.cmake>
is licensed under MIT License included in the file itself.
