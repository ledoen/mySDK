#!/bin/sh

make clean
make
cp mysdk_app.bin /tftpboot/
