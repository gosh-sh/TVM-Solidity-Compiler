<meta name="title" content="TVM-Solidity-Compiler">
<meta name="description" content="Solidity compiler for TVM">
<meta name='keywords' content='compiler, smart-contracts, blockchain, solidity, tvm, everscale, everos, venom-blockchain, venom-developer-program'>

# The TVM Solidity compiler

[![GitHub](https://img.shields.io/github/license/everx-labs/TVM-Solidity-Compiler?style=for-the-badge)](./LICENSE)
[![Everscale](https://custom-icon-badges.demolab.com/badge/-everscale-13173e?style=for-the-badge&logoColor=yellow&logo=everscale)](https://everscale.network/)


Port of the Solidity smart-contract [compiler](https://github.com/ethereum/solidity) generating TVM bytecode for TVM compatible blockchains (Everscale, Venom, Gosh, TON). Please refer to upstream README.md for information on the language itself.

## TVM Solidity API reference

[API documentation is here](https://github.com/everx-labs/TVM-Solidity-Compiler/blob/master/API.md)

## Build and Install

### Sold driver

We recommend using `sold` to compile smart-contracts. Documentation is available at [README.md](https://github.com/everx-labs/TVM-Solidity-Compiler/blob/master/sold/README.md).

### Building compiler

Original Instructions about how to build and install the Solidity compiler can be found in the [Solidity documentation](https://solidity.readthedocs.io/en/latest/installing-solidity.html#building-from-source).

#### Ubuntu Linux

```shell
git clone https://github.com/everx-labs/TVM-Solidity-Compiler
cd TVM-Solidity-Compiler
sh ./compiler/scripts/install_deps.sh
mkdir build
cd build
cmake ../compiler/ -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j8
```

#### MacOS

Clone repo
```
git clone https://github.com/everx-labs/TVM-Solidity-Compiler
cd TVM-Solidity-Compiler
```

Update variable [`CMAKE_OSX_DEPLOYMENT_TARGET`](https://github.com/gosh-sh/TVM-Solidity-Compiler/blob/92f893433651c9bcd94975832388930f2ac8fe0f/compiler/CMakeLists.txt#L28) in `compiler/CMakeLists.txt` with the appropriate version for your architecture. 
In order to get your architecture version, run `cargo build --release` to get the compilation error displaying your acrhitecture. 
Here, for example, the right version should be 15.2
```
clang++: warning: overriding '-mmacosx-version-min=11.0' option with '--target=arm64-apple-macosx15.2' [-Woverriding-t-option]
```

Now build and copy to the `~/.cargo/bin` folder (or any other folder that you use for global binaries) to be available globally 

```shell
cargo build --release
cp target/release/sold ~/.cargo/bin/sold
```


#### Windows 10

Install Visual Studio Build Tools 2019, Git bash, cmake.
Run Developer PowerShell for VS 2019

```shell
git clone https://github.com/everx-labs/TVM-Solidity-Compiler
cd TVM-Solidity-Compiler
compiler\scripts\install_deps.ps1
mkdir build
cd build
cmake -DBOOST_ROOT="..\compiler\deps\boost\" -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded ..\compiler
cmake --build . --config Release -- /m
```

## Links

 * [Ever assembler and disassembler](https://github.com/everx-labs/ever-assembler)
 * [Code samples](https://github.com/everx-labs/samples/tree/master/solidity) in TVM Solidity
 * [ever-cli](https://github.com/everx-labs/ever-cli) command line interface for TVM compatible blockchains
 * Example of usage `ever-cli` for working (deploying, calling etc.) with TVM compatible blockchains can be found there: [Write smart contract in Solidity](https://docs.ton.dev/86757ecb2/p/950f8a-write-smart-contract-in-solidity)
 * [Changelog](https://github.com/everx-labs/TVM-Solidity-Compiler/blob/master/Changelog_TON.md)

## License
[GNU GENERAL PUBLIC LICENSE Version 3](./LICENSE)
