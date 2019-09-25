# ZILMiner

> Zilliqa miner with OpenCL and CUDA support. It supports both Ubuntu and Windows OS.

**ZILMiner** is an Ethash GPU mining software that supports the [Zilliqa](https://github.com/Zilliqa) Proof-of-Work process.  

This project is a fork of [ethminer](https://github.com/ethereum-mining/ethminer). Please do see [ethminer README](https://github.com/ethereum-mining/ethminer/blob/master/README.md) for more details of the implementation.

## Features

* Zilliqa Getwork protocol
* Dual-Mining support
* All current ethminer features

## Install

Standalone **executables** for *Linux*, *macOS* and *Windows* are provided in
the [**Releases**](https://github.com/DurianStallSingapore/ZILMiner/releases) section.
Download an archive for your operating system and unpack the content to a place
accessible from command line. After which, zilminer will be ready to go.

## Usage

**ZILMiner** is a command line program. This means you will have to launch it either
from a Windows command prompt or Linux Bash console. You can also create shortcuts to
predefined commands using a Linux Bash script or Windows batch/cmd file.
For the full list of available commands, please enter the following:

```sh
zilminer --help
```

## Settings on Zilliqa Node Work in GetWork Server Mode

1. Setup Zilliqa Node by following the [Zilliqa Mining Guide](https://github.com/Zilliqa/Zilliqa/wiki/Mining)
1. Change the `constants.xml` for the following parameter:
    * Set `GETWORK_SERVER_MINE` to `true`
    * Set `GETWORK_SERVER_PORT` to the port you will be using to GetWork (default is `4202`)
    * Set the other mining parameters to `false`:

       ```xml
       <CUDA_GPU_MINE>false</CUDA_GPU_MINE>
       <FULL_DATASET_MINE>false</FULL_DATASET_MINE>
       <OPENCL_GPU_MINE>false</OPENCL_GPU_MINE>
       <REMOTE_MINE>false</REMOTE_MINE>
       ```

1. Launch your node and find out your IP address with the following command:

    ```bash
    curl https://ipinfo.io/ip
    ./launch_docker.sh
    ```

## Settings on ZILMiner client

Key in the following command in your command prompt:

```sh
zilminer -P zil://wallet_address.worker_name@zil_node_ip:get_work_port
```

> Please change the *wallet_address*, *worker_name*, *zil_node_ip*, and *get_work_port* accordingly.

* For `wallet_address`: You can use the [Moonlet](https://moonlet.xyz/) to create a new keypair and a Zilliqa address
* For `worker_name` You can key in any abitrary worker name you desire
* For `zil_node_ip`: Please key in the IP address of the Zilliqa node
* For `get_work_port`: Please key in the port used in `GETWORK_SERVER_PORT`. Default is `4202`

## Dual Mining

1. Create 2 `bat` scripts yourself to start/stop other coin's miner
1. Add arg `--pow-start` to stop the other miner before ZIL PoW process starts
1. Add arg `--pow-end` to start the other miner after ZIL PoW process stops

   Example:

   ```sh
   zilminer --pow-start stopAE.bat --pow-end startAE.bat -P zil://wallet_address.worker_name@zil_node_ip:get_work_port
   ```

1. **(Optional)** If your GPU's memory is insufficient, add the arg `--clear-dag` to clear Zilliqa's DAG after ZIL PoW has stopped.

## Dual Mining Scripts

### Zilminer + GMiner

Here is an example of how to create the 2 batch files necessary for dual mining BEAM and ZIL:

* To create the `start_beam.bat` batch file that is needed to start the BEAM miner, do the following:

   ```bat
   taskkill /f /im miner.exe >null
   START cmd /c "miner.exe --algo 150_5 --server beam-us.leafpool.com --port 4444 --ssl 1 --user walletxxx.namexxx"
   ```

* To create the `stop_beam.bat` batch file that is needed to stop the BEAM miner, do the following:

   ```bat
   taskkill /f /im miner.exe >null
   ```

Then, run both `bat` scripts by following the example command below:

```bat
zilminer.exe --pow-start stop_beam.bat --pow-end start_beam.bat --pow-end-at-startup -P zil://wallet_address.worker_name@proxy.getzil.com:5000/api
```

If your GPU's memory is not sufficient for these 2 miners to run concurrently, add the arg `--clear-dag` to the command above.

## Build

### Building from source

See [docs/BUILD.md](docs/BUILD.md) for build/compilation details.
