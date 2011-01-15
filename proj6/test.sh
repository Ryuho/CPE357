./parseline > MINE.txt

./koparseline > HIS.txt


diff -s -U 10 -b -B MINE.txt HIS.txt

rm MINE.txt HIS.txt
