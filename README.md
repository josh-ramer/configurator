# Configurator

## Building & Running the Driver

```bash
cd ${repository root}
mkdir build
cd build

cmake ..
make -j config={Debug, Release}

./driver -h
./driver --files /path/f1 ... /path/fN

```

<!--// TODO: make sure these commands work-->
