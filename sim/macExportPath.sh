#!/bin/bash

echo Exporting path
export PKG_CONFIG_PATH="/usr/local/opt/opencv@4/lib/pkgconfig"
export PKG_CONFIG_PATH="/usr/local/opt/opencv@/lib/pkgconfig"
echo 'export PKG_CONFIG_PATH="/usr/local/opt/opencv@4/lib/pkgconfig"' > ~/.bash_profile
echo 'export PKG_CONFIG_PATH="/usr/local/opt/opencv@/lib/pkgconfig"' > ~/.bash_profile
