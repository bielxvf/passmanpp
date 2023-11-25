# passmanpp
Simple password manager written in C++
Heavily inspired by another password manager written in C: `https://github.com/bielsalamimo/passman`

# Dependencies
`passmanpp` uses [cxxopts](https://github.com/jarro2783/cxxopts) to parse command-line arguments, you will need it set up before building `passmanpp`

# Build
```
git clone https://github.com/bielsalamimo/passmanpp
cd passmanpp
mkdir build
cd build
cmake .. && make
```
A binary executable will be created on `build` which you can run with the command `./passmanpp`

# Install
Firstly, build the `passmanpp` binary, then run `sudo install -D passmanpp /usr/bin/` while in the `build` directory to install it globally
