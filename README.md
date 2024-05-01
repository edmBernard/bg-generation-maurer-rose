# bg-generation-maurer-rose

Small executable that generate [Maurer Rose](https://en.wikipedia.org/wiki/Maurer_rose) and save it in svg.

- Github : [https://github.com/edmBernard/bg-generation-maurer-rose](https://github.com/edmBernard/bg-generation-maurer-rose)


## Build and Dependencies

### Dependencies

We use [vcpkg](https://github.com/Microsoft/vcpkg) to manage dependencies. they are define in the vcpkg.json file.

To install dependencies just run the following command in the folder.

```
./vcpkg install
```

### Build

The recommended way to obtain the source code is to clone the entire repository from GitHub:

```
git clone git@github.com:edmBernard/bg-generation-maurer-rose
```

Building the main executable is done by the following command :

```bash
mkdir build
cd build
# configure cmake with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake
# on Windows : cmake .. -DCMAKE_TOOLCHAIN_FILE=${env:VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

The executable is named `bg-generation-maurer-rose`

## Disclaimer

It's a toy project. So if you spot error, improvement comments are welcome.
