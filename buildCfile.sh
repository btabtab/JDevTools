tput reset
printf '(buildCfile.sh):> Building main.c\n'
cat main.exe > main.exe.prev
clang main.c -g -o main.exe > most_recent_build_log.txt
cat most_recent_build_log.txt >> build_log_history.txt