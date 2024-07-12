#!/bin/bash

# check if systemd unit file already exists
## List to install
# Git
# PiMesh
# Gum?

if [[ -f "/lib/systemd/system/pimesh.service" ]]; then
	echo "pimesh is already installed on your machine!"
else
    if ! command -v git &> /dev/null
    then
        echo "Installing Git"
        sudo apt-get update
        sudo apt-get install git -y
    fi

    git clone https://github.com/digitalpancake/pimesh-daemon.git
fi
