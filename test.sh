#!/bin/sh

ONE_COLOR=./cmake-build-debug/onecolor
sample=sample2
[ $# -ne 0 ] && sample=$1

do_sample() {
  option=$1

  ${ONE_COLOR} -${option} images/${sample}.jpg images/${sample}-${option}.jpg
}

for opt in 0 R G B Y
do
  do_sample ${opt}
done

eog /home/bernard/git/onecolor/images/${sample}.jpg &
