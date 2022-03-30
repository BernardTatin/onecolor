#!/bin/sh

. $(dirname $0)/set-environment.sh

[ $# -ne 2 ] && echo "$0 sample_number hue" && exit 1
src=images/sample$1.jpg
dst=images/sample$1-$2.jpg

${ONE_COLOR} -V -h $2 ${src} ${dst} || exit 1
eog ${dst} &
