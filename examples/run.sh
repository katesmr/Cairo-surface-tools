#!/bin/sh

gcc `pkg-config --cflags gtk+-3.0` -o app $1 `pkg-config --libs gtk+-3.0`
./app