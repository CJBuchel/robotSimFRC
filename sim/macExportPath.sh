#!/bin/bash

echo Exporting path
export PKG_CONFIG_PATH="/usr/local/opt/opencv@4/lib/pkgconfig"
export PKG_CONFIG_PATH="/usr/local/opt/opencv@/lib/pkgconfig"
echo 'export PKG_CONFIG_PATH="/usr/local/opt/opencv@4/lib/pkgconfig"' >> ~/.bashrc
echo 'export PKG_CONFIG_PATH="/usr/local/opt/opencv@/lib/pkgconfig"' >> ~/.bashrc
