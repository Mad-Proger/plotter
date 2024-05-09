# Plotter

Simple gui application capable of plotting implicit functions using
marching squares algorithm

### Build & Run

Fetch submodules:
```shell
git submodule update --init --recursive
```

Compile and run:
```shell
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=./install
cmake --build build
cmake --install build
install/bin/plotter
```
