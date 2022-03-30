#!/bin/sh

export ONE_COLOR=./cmake-build-debug/one-color

[ $# -ne 2 ] && echo "$0 sample_number hue" && exit 1
src=images/sample$1.jpg
dst=images/sample$1-$2.jpg

${ONE_COLOR} -h $2 ${src} ${dst}
eog ${dst} &
