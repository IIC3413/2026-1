# IIC3413-DB

> [!IMPORTANT]
> For lab 3 you need to install boost to compile

## Project Build

Install Dependencies:

This project needs the following dependencies:

- GCC >= 8.1
- CMake >= 3.12
- Boost

On recent Debian and Ubuntu based distributions they can be installed by running:

```bash
sudo apt update && sudo apt install g++ cmake
```

For Mac you need to install the **Xcode Command Line Tools** and [Homebrew](https://brew.sh/). After installing homebrew you can install cmake:

```bash
brew install cmake
```

### Install Boost

--------------------------------------------------------------------------------

``` bash
wget -q --show-progress https://archives.boost.io/release/1.84.0/source/boost_1_84_0.tar.gz
tar -xf boost_1_84_0.tar.gz
mkdir -p third_party/boost_1_84/include
mv boost_1_84_0/boost third_party/boost_1_84/include
rm -r boost_1_84_0.tar.gz boost_1_84_0
```

### Build the Project

--------------------------------------------------------------------------------
Open a terminal in the project root directory, then execute the commands:

For the Release version:

```bash
cmake -Bbuild/Release -DCMAKE_BUILD_TYPE=Release && cmake --build build/Release/
```

For the Debug Version:

```bash
cmake -Bbuild/Debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/Debug/
```

To use multiple cores during compilation (much faster) add `-j n` at the end of the previous commands, replacing `n` with the desired number of threads. Example for 8 threads:

```bash
cmake -Bbuild/Debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/Debug/ -j 8
```


