#!/bin/sh
# AUTO-GENERATED FILE, DO NOT EDIT!
if [ -f $1.org ]; then
  sed -e 's!^C:/Users/Matias/Documents/Ohjelmointi/Android/cygwin/lib!/usr/lib!ig;s! C:/Users/Matias/Documents/Ohjelmointi/Android/cygwin/lib! /usr/lib!ig;s!^C:/Users/Matias/Documents/Ohjelmointi/Android/cygwin/bin!/usr/bin!ig;s! C:/Users/Matias/Documents/Ohjelmointi/Android/cygwin/bin! /usr/bin!ig;s!^C:/Users/Matias/Documents/Ohjelmointi/Android/cygwin/!/!ig;s! C:/Users/Matias/Documents/Ohjelmointi/Android/cygwin/! /!ig;s!^C:/users/kat11sJermuj/desktop/asdk!/build!ig;s! C:/users/kat11sJermuj/desktop/asdk! /build!ig;s!^F:!/cygdrive/f!ig;s! F:! /cygdrive/f!ig;s!^D:!/cygdrive/d!ig;s! D:! /cygdrive/d!ig;s!^C:!/cygdrive/c!ig;s! C:! /cygdrive/c!ig;' $1.org > $1 && rm -f $1.org
fi
