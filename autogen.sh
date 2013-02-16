#!/bin/sh
#echo "Creating AUTHORS file from git ..."
#git log --format='%aN <%aE>' | awk '{arr[$0]++} END{for (i in arr){print arr[i], i;}}' | sort -rn | cut -d\  -f2- > AUTHORS
echo "Regenerating autotools files"
autoreconf --install --force --symlink || exit 1
