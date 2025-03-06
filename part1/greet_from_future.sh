#!/bin/bash

echo "Hello $(whoami) from the future. \
Today is $(date --date="+3 days" +%A), \
$(date --date="+3 days" +%d) $(date --date="+3 days" +%B) $(date --date="+3 days" +%Y), \
and the time is $(date +%T)." # No need \"+3 days\" for time as same time
