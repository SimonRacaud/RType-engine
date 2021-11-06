#!/bin/bash

declare -a COMMANDS
myArray+=(item)
CMD_NB=0

for ARG in "$@" ; do
#  echo "$ARG"
  if [ "$ARG" = "-c" ]; then
    CMD_NB=$( expr $CMD_NB + 1 )
  else
    COMMANDS[$CMD_NB]="${COMMANDS[$CMD_NB]} $ARG"
  fi
done


for (( i = 1; i <= ${#COMMANDS[@]}; i++ )); do
#    echo ${COMMANDS[$i]}
  if ( (($i == ${#COMMANDS[@]})) ); then
    command ${COMMANDS[$i]}
  else
    command ${COMMANDS[$i]} &
  fi
done

#$1 $2 & $3 $4