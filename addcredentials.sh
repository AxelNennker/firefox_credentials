#!/bin/bash
srctopatch="/media/sdb1/mozilla/firefox"
w3credentials="/media/sdb1/mozilla/W3Credentials"
echo $srctopatch
echo $w3credentials
(cd $w3credentials && tar cf - credentials | (cd "$srctopatch/dom/" && tar xf -))
cp "$w3credentials/CredentialContainer.webidl" "$srctopatch/dom/webidl/"
/usr/local/bin/patch "$srctopatch/dom/moz.build" "$w3credentials/moz.build.patch"
/usr/local/bin/patch "$srctopatch/dom/bindings/Bindings.conf" "$w3credentials/Bindings.conf.patch"
/usr/local/bin/patch "$srctopatch/dom/webidl/moz.build" "$w3credentials/webidl-moz.build.patch"
#patch ../firefox/dom/webidl/Navigator.webidl" "Navigator.webidl.patch"
/usr/local/bin/patch "$srctopatch/dom/base/Navigator.h" "$w3credentials/Navigator.h.patch"
/usr/local/bin/patch "$srctopatch/dom/base/Navigator.cpp" "$w3credentials/Navigator.cpp.patch"
/usr/local/bin/patch "$srctopatch/dom/ipc/ContentChild.cpp" "$w3credentials/ContentChild.cpp-patch"
/usr/local/bin/patch "$srctopatch/dom/ipc/ContentChild.h" "$w3credentials/ContentChild.h-patch"
/usr/local/bin/patch "$srctopatch/dom/ipc/ContentParent.cpp" "$w3credentials/ContentParent.cpp-patch"
/usr/local/bin/patch "$srctopatch/dom/ipc/ContentParent.h" "$w3credentials/ContentParent.h-patch"
/usr/local/bin/patch "$srctopatch/dom/ipc/PContent.ipdl" "$w3credentials/PContent.ipdl-patch"
