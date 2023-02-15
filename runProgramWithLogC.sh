printf 'Running C Program...\n'
sha1sum main.exe > programLog.txt
printf '\n' >> programLog.txt
./main.exe logging_output_to_file >> programLog.txt
printf 'Finished running C program.\n'