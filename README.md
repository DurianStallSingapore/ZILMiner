# zilminer

> Zilliqa miner with OpenCL, CUDA support

**zilminer** is an Ethash GPU mining worker to support Zilliqa Proof of Work mining. 

This project is forked from [ethminer](https://github.com/ethereum-mining/ethminer). See [ethminer README](ethminer.README.md) for more details.

## Features

* Zilliqa Getwork Protocol
* All ethminer Features 


## Install

Standalone **executables** for *Linux*, *macOS* and *Windows* are provided in
the [Releases] section.
Download an archive for your operating system and unpack the content to a place
accessible from command line. The zilminer is ready to go.


## Usage

The **zilminer** is a command line program. This means you launch it either
from a Windows command prompt or Linux console, or create shortcuts to
predefined command lines using a Linux Bash script or Windows batch/cmd file.
For a full list of available command, please run:

```sh
zilminer --help
```

## Settings on client

```sh
zilminer --max-submit=1 --farm-recheck 10000 --work-timeout=7200 --farm-retries=10 --retry-delay=10 \
         -P zil://wallet_address.worker_name@zil_node_ip:4202
```
please change the *wallet_address*, *worker_name* and *zil_node_ip* accodingly.


## Settings on Zilliqa Node
1. Setup Zilliqa Node follow [Zilliqa Mining Guide](https://github.com/Zilliqa/Zilliqa/wiki/Mining)
2. Change `constans.xml`
    * Set `GETWORK_SERVER_MINE` to `true`
    * Set other mining method to `false`
3. Start the node, connect *zilminer* to your Node

## Build

### Building from source

See [docs/BUILD.md](docs/BUILD.md) for build/compilation details.
