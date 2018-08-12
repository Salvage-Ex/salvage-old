# Salvage Installation

If you want to compile the binaries from souce, do the following on Ubuntu 16.04.

# Create SWAP

sudo fallocate -l 2G /swapfile

sudo chmod 600 /swapfile

sudo mkswap /swapfile

sudo swapon /swapfile


# Install Prerequisites

sudo add-apt-repository ppa:bitcoin/bitcoin

sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3

sudo apt-get update

sudo apt-get upgrade

sudo apt-get install libboost-all-dev

sudo apt-get install software-properties-common

sudo apt-get update

sudo apt-get install libdb4.8-dev libdb4.8++-dev

sudo apt-get install libzmq3-dev

sudo apt-get install libminiupnpc-dev


# Download source

git clone https://github.com/Salvage-Ex/salvage

cd salvage


# Compile

./autogen.sh

./configure

make

make install # optional


# Run

from salvage/src directory:

./salvaged

once running, to issue RPC commands use:

./salvage-cli <command>
