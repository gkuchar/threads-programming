#! /bin/bash

if ! [[ -x pthii ]]; then
    echo "pthii executable does not exist"
    exit 1
fi

../../tester/run-tests.sh $*


