'r' = "sh -c 'date +%s > /tmp/stopwatch-start'"
'l' = "sh -c 'start=$(cat /tmp/stopwatch-start); echo $((start-5)) > /tmp/stopwatch-start'"
'h' = "sh -c 'start=$(cat /tmp/stopwatch-start); echo $((start+5)) > /tmp/stopwatch-start'"
