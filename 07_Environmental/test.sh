#!/bin/bash

TEST=test.txt
OUTPUT=output.txt
EXPECTED=expected.txt

echo "qwerty" > $TEST

echo "MD5 $TEST" | ./rhasher > $OUTPUT
printf "> %s\n> " $(md5sum test.txt | awk '{print $1}') > $EXPECTED
diff $OUTPUT $EXPECTED && echo "MD5 тест пройден"

echo "SHA1 $TEST" | ./rhasher > $OUTPUT
printf "> %s\n> " $(sha1sum test.txt | awk '{print $1}')  > $EXPECTED
diff $OUTPUT $EXPECTED && echo "SHA1 тест пройден"

rm $TEST $OUTPUT $EXPECTED
