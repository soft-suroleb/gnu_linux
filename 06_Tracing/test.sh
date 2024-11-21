#!/bin/bash

INFILE=infile
OUTFILE=outfile

echo 'simple string' >> $INFILE

strace -e fault=openat:error=EACCES:when=3 ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 1 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

strace -e fault=fstat:error=EACCES:when=3  ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 2 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

strace -e fault=openat:error=EACCES:when=4 ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 3 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

strace -e fault=write:error=EACCES:when=1 ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 4 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

strace -e fault=read:error=EACCES:when=2 ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 5 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

strace -e fault=close:error=EACCES:when=3 ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 6 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

strace -e fault=close:error=EACCES:when=4 ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 7 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

strace -e fault=unlink:error=EACCES:when=1 ./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 8 ] && [ -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

./move $INFILE $OUTFILE 1>/dev/null 2>&1 
if [ $? = 0 ] && [ -f $OUTFILE ] && [ ! -f $INFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

PROTECT=PROTECT_infile
PROTECT_SO=protect.so
echo protect >> $PROTECT

LD_PRELOAD=`pwd`/$PROTECT_SO ./move $PROTECT $OUTFILE 1>/dev/null 2>&1
if [ $? = 0 ] && [ -f $PROTECT ] && [ -f $OUTFILE ]
then
   echo "PASSED"
else
   echo "FAILURE"
fi

rm $PROTECT
rm $OUTFILE
