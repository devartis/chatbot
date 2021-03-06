#!/bin/bash

if uname | grep -qi linux; then
  target_os=linux32
  pkg_format=tar.gz
elif uname | grep -qi cygwin; then
  target_os=win32
  pkg_format=zip
else
  echo "ERROR: Unsupported OS type: " `uname` 
  exit 1
fi

if [ -z "$target_os" ] || ! [ -d "$target_os" ]; then
  echo "ERROR: Unsupported OS type: " `uname` 
  exit 1
fi

. common/release-config

if [ -z "$pkg_version" ]; then
  echo "Error: Package version not set"
  exit 1
fi

pkg_version="$pkg_version-open"

if [ -z "$pkg_name" ]; then
  echo "Error: Package name not set"
  exit 1
fi

echo "*************************"
echo "Packaging chatbot v$pkg_version"
echo "*************************"

pkg_filename=$pkg_name.$pkg_format

pushd $target_os

./build.sh && \
./package.sh $pkg_version && \
echo "*** Everything went OK! ***"
echo "Package built: $target_os/$pkg_filename"

popd
