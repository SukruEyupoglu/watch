#!/bin/bash
./stm8flash -c stlinkv2 -p stm8s103f3 -s flash -w stm8/stm8.ihx
# ./stm8flash -c stlinkv2 -p stm8s003f3 -s flash -w stm8/stm8.ihx
# ./stm8flash -c stlinkv2 -p stm8s003f3 -s eeprom -w eepromdata_128_byte.bin
# ./stm8flash -c stlinkv2 -p stm8s003f3 -s eeprom -r eepromdata_128_byte.bin
# ./stm8flash -c stlinkv2 -p stm8s003f3 -s eeprom -v eepromdata_128_byte.bin
