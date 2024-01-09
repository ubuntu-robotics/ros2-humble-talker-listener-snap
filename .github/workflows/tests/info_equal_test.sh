#!/bin/bash

expected_output_file=$(cat ".github/workflows/tests/info_expected_output.txt")
snap_info_output=$(snap info ros2-talker-listener)
if [ "${expected_output_file%%refresh-date*}" = "${snap_info_output%%refresh-date*}" ]; then
   echo "Strings are equal until refresh-date"
else
    echo "Strings are not equal until refresh-date"
    exit 1
fi
