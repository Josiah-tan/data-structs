#!/usr/bin/env bash

echo "Hello world"
working_directory=$(pwd)
echo "working directory = $working_directory"

if [ -z "$(ls -A "$working_directory")" ]; then 
	echo "empty"
	script_dir=$(dirname "$0")
	echo "script_dir = $script_dir"
	cp -r $script_dir/* $working_directory
fi

