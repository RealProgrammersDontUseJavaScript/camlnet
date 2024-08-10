#!/bin/sh
# This script will replace the old version of inet,
# and install the new binary
# Unfortunately, it doesn't work until reboot


service down inet && rm /service/inet && cp ./inet /service/inet
if [ $? != 0 ]; then
  exit 126
fi

echo "Do you want to reboot your minix install right now?\n[y] [n]"
if [ "$REPLY" == "y" ] || [ "$REPLY" == "yes" ] || [ "$REPLY" == "Y" ]
|| [ "$REPLY" == "Yes" ] || [ " $REPLY" == "YES" ]; then
  sleep 10
  reboot
  exit 0
fi
if [ "$REPLY" == "n" ] || [ "$REPLY" == "no" ] || [ "$REPLY" == "N" ]
|| [ "$REPLY" == "No" ] || [ "$REPLY" == "NO" ]; then
  echo "Script done."
  exit 0
fi 
exit 65
