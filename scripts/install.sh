#!/bin/bash

# check if systemd unit file already exists

## List to install
# Git
# PiMesh
# Gum?

# Find architechture somehow

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi


if [[ -f "/lib/systemd/system/pimesh.service" ]]; then
	echo "pimesh is already installed on your machine!"
else
    if ! command -v git &> /dev/null
    then
        echo "Installing Git"
        sudo apt-get update
        sudo apt-get install git -y
    fi

    if [ -d "/tmp/pmdmn" ]; then
        rm -r /tmp/pmdmn/*
    fi

    mkdir /tmp/pmdmn
    cd /tmp/pmdmn

    git clone https://github.com/digitalpancake/pimesh-daemon.git
    wget https://github.com/charmbracelet/gum/releases/download/v0.14.1/gum_0.14.1_amd64.deb

    apt install -y ./gum_0.14.1_amd64.deb

    clear
    gum style --border normal --margin "1" --padding "1 2" --border-foreground 212 "Welcome to the PiMesh Daemon"
fi
