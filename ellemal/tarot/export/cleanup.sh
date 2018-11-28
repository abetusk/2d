#!/bin/bash

ifn="$1"

if [[ "$ifn" == "" ]] ; then
  echo "provide file"
  exit 1
fi

dos2unix $ifn
sed -i 's/;.*//' $ifn

