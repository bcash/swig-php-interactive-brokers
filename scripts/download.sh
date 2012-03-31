#!/bin/sh

die () {
    echo >&2 "$@"
    exit 1
}

[ "$#" -eq 1 ] || die "1 argument required, $# provided"
echo $1 | grep -E -q '^[0-9]+$' || die "Numeric argument required, $1 provided"

src="../src"

[ -d "../src" ] || die "Directory not found ../src"

url="http://www.interactivebrokers.com/download/twsapi_unixmac_$1.jar"

command -v wget >/dev/null 2>&1 || die "Program wget is required"
command -v jar >/dev/null 2>&1 || die "Program jar is required"

wget -N -P $src -q $url
 
[ "$?" -eq 0 ] || die "Failed to get Interactive Brokers API version $1 source, wget failed with error code $?"

cd $src && jar xf twsapi_unixmac_$1.jar

