#!/bin/bash

# check if systemd unit file already exists
if [[ -f "/lib/systemd/system/pimesh.service" ]]; then
	echo "pimesh is already installed on your machine!"
else
	echo "installing pimesh..."
fi
