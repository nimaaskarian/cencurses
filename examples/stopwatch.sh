#!/bin/sh

BASE=$(dirname "$0")
date +%s >/tmp/stopwatch-start
numcurses -f "$BASE/stopwatch.nc" -m 'date -u -d "@$(($(date +%s) - $(cat /tmp/stopwatch-start)))" +%H:%M:%S' -a "figlet"
