#!/bin/bash

## List to install
# Git
# PiMesh
# Gum?

# check if systemd unit file already exists
if [[ -f "/lib/systemd/system/pimesh.service" ]]; then
	echo "PiMesh is already installed on your machine!"
# otherwise, install pimesh and dependencies
else
    if ! command -v git &> /dev/null
    then
        echo "Installing Git..."
        sudo apt-get update
        sudo apt-get install git -y
    fi

    git clone https://github.com/digitalpancake/pimesh-daemon.git /tmp/pimesh-daemon

    rm -r /tmp/pimesh-daemon
fi
