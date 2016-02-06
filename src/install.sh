#!/bin/sh
#
# src/install.sh
# This script is part of the IPTraf installation system.  Do not attempt
# to run this directly from the command prompt.
#
# Version 3.0.0 Copyright (c) Gerard Paul Java 2002
#

if [ "$1" = "" ]; then
    echo "This script is part of the IPTraf installation system, and"
    echo "should not be run by itself."
    exit 1
fi

INSTALL=/usr/bin/install
TARGET=$1
WORKDIR=$2
LOGDIR=$3
DESTDIR=$4

echo
echo "*** Installing executable programs and preparing work directories"
echo
echo ">>> Installing iptraf in $TARGET"
$INSTALL -m 0700 -o root -g root iptraf $DESTDIR/$TARGET
echo ">>> Installing rvnamed in $TARGET"
$INSTALL -m 0700 -o root -g root rvnamed $DESTDIR/$TARGET

if [ ! -d $DESTDIR/$WORKDIR ]; then
    echo ">>> Creating IPTraf work directory $WORKDIR"
else
    echo ">>> IPTraf work directory $WORKDIR already exists"
    rm -f $DESTDIR/$WORKDIR/othfilter.dat
fi

$INSTALL -m 0700 -o root -g root -d $DESTDIR/$WORKDIR

if [ ! -d $DESTDIR/$LOGDIR ]; then
    echo ">>> Creating IPTraf log directory $LOGDIR"
else
    echo ">>> IPTraf log directory $LOGDIR already exists"
fi
$INSTALL -m 0700 -o root -g root -d $DESTDIR/$LOGDIR

echo
echo
echo "*** iptraf, and rvnamed executables are in $TARGET"
echo "*** Log files are placed in $LOGDIR"

################# Filter clearing for 3.0 ##########################

if [ ! -f $DESTDIR/$WORKDIR/version ]; then
    echo ">>> Clearing old filter list"
    if [ -f $DESTDIR/$WORKDIR/tcpfilters.dat ]; then
        mv -f $DESTDIR/$WORKDIR/tcpfilters.dat $DESTDIR/$WORKDIR/tcpfilters.dat~
    fi
    
    if [ -f $DESTDIR/$WORKDIR/udpfilters.dat ]; then
        mv -f $DESTDIR/$WORKDIR/udpfilters.dat $DESTDIR/$WORKDIR/udpfilters.dat~
    fi

    if [ -f $DESTDIR/$WORKDIR/othipfilters.dat ]; then
        mv -f $DESTDIR/$WORKDIR/othipfilters.dat $DESTDIR/$WORKDIR/othipfilters.dat~
    fi

    rm -f $DESTDIR/$WORKDIR/savedfilters.dat
fi
####################################################################

cat version > $DESTDIR/$WORKDIR/version

exit 0

echo 
echo

echo "======================================================================"
echo
echo "Please read the RELEASE-NOTES file for important new information about"
echo "this version. You can view this file now (will require the 'less'"
echo "program in /usr/bin.  Press Q to quit when done)."
echo
echo -n "Would you like to view the RELEASE-NOTES file now (Y/N)? "; read YESNO

if [ "$YESNO" = "y" -o "$YESNO" = "Y" ]; then
    less ../RELEASE-NOTES
fi

clear
echo
echo "====================================================================="
echo
echo "Thank you for installing IPTraf.  You can now start IPTraf by issuing"
echo "the command"
echo
echo "    $TARGET/iptraf"
echo
echo "at your shell prompt.  You can also add $TARGET to your PATH environment"
echo "variable to avoid having to type the pathname when invoking the program."
echo

exit 0

