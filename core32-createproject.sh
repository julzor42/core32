#!/bin/bash

if [ -z "$1" ]; then
 echo "Syntax: $0 <project name>"
 exit
fi

if [ -d "$1" ]; then
 echo "Directory $1 already exists!"
 exit
fi

cp -R `dirname $0`/template $1
echo "Project $1 created"

