#!/bin/sh

cp bin/ARM/Debug/BonnetShutdown /usr/local/bin

echo Initializing program GPIO pins...
gpio mode 4 in
gpio mode 3 in
gpio mode 25 in
gpio mode 28 in
gpio mode 26 in
gpio mode 22 in
gpio mode 27 in
gpio mode 23 in
gpio mode 4 up
gpio mode 3 up
gpio mode 25 up
gpio mode 28 up
gpio mode 26 up
gpio mode 22 up
gpio mode 27 up
gpio mode 23 up