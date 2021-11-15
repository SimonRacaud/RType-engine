#!/bin/bash

declare -a COMMANDS
CMD_NB=0

for ARG in "$@" ; do
#  echo "$ARG"
  if [ "$ARG" = "-c" ]; then
    CMD_NB=$( expr $CMD_NB + 1 )
  else
    COMMANDS[$CMD_NB]="${COMMANDS[$CMD_NB]} $ARG"
  fi
done


declare -a PIDS
PID_NB=0

RET_VAL=0

for (( i = 1; i <= ${#COMMANDS[@]}; i++ )); do
#    echo ${COMMANDS[$i]}
  if ( (($i == ${#COMMANDS[@]})) ); then
    command ${COMMANDS[$i]}
    RET=$?
    if (( $RET != 0 )) ; then
        RET_VAL=$RET
    fi
  else
    command ${COMMANDS[$i]} &
    PID_NB=$( expr $PIOAD_NB + 1 )
    PIDS[$PID_NB]="$!"
  fi
done

for (( i = 1; i <= ${#PIDS[@]}; i++ )); do
    wait ${PIDS[$i]}
    RET=$?
    if (( $RET != 0 )) ; then
        RET_VAL=$RET
    fi
done

exit $RET_VAL
