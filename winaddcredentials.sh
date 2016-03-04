#!/bin/bash
srctopatch="/d/Users/nennker.axel/mozilla-source/firefox"
w3credentials="/d/Users/nennker.axel/mozilla-source/W3Credentials"
echo $srctopatch
echo $w3credentials
(cd $w3credentials && tar cf - credentials | (cd "$srctopatch/dom/" && tar xf -))
cp "$w3credentials/CredentialContainer.webidl" "$srctopatch/dom/webidl/"
/bin/patch "$srctopatch/dom/moz.build" "$w3credentials/moz.build.patch"
/bin/patch "$srctopatch/dom/bindings/Bindings.conf" "$w3credentials/Bindings.conf.patch"
/bin/patch "$srctopatch/dom/webidl/moz.build" "$w3credentials/webidl-moz.build.patch"
#patch ../firefox/dom/webidl/Navigator.webidl" "Navigator.webidl.patch"
/bin/patch "$srctopatch/dom/base/Navigator.h" "$w3credentials/Navigator.h.patch"
/bin/patch "$srctopatch/dom/base/Navigator.cpp" "$w3credentials/Navigator.cpp.patch"
/bin/patch "$srctopatch/dom/ipc/ContentChild.cpp" "$w3credentials/ContentChild.cpp-patch"
/bin/patch "$srctopatch/dom/ipc/ContentChild.h" "$w3credentials/ContentChild.h-patch"
/bin/patch "$srctopatch/dom/ipc/ContentParent.cpp" "$w3credentials/ContentParent.cpp-patch"
/bin/patch "$srctopatch/dom/ipc/ContentParent.h" "$w3credentials/ContentParent.h-patch"
/bin/patch "$srctopatch/dom/ipc/PContent.ipdl" "$w3credentials/PContent.ipdl-patch"
