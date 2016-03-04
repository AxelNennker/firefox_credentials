#!/bin/sh
srctopatch="/d/Users/nennker.axel/mozilla-source/firefox"
w3credentials="/d/Users/nennker.axel/mozilla-source/W3Credentials"
echo $srctopatch
echo $w3credentials
rm -rf "$srctopatch/dom/credentials/"
rm -f "$srctopatch/dom/webidl/CredentialContainer.webidl"
rm -rf "$srctopatch/dom/interfaces/credentials/"
/bin/patch -R "$srctopatch/dom/moz.build" "$w3credentials/moz.build.patch"
/bin/patch -R "$srctopatch/dom/bindings/Bindings.conf" "$w3credentials/Bindings.conf.patch"
/bin/patch -R "$srctopatch/dom/webidl/moz.build" "$w3credentials/webidl-moz.build.patch"
#patch -R ../firefox/dom/webidl/Navigator.webidl Navigator.webidl.patch"
/bin/patch -R "$srctopatch/dom/base/Navigator.h" "$w3credentials/Navigator.h.patch"
/bin/patch -R "$srctopatch/dom/base/Navigator.cpp" "$w3credentials/Navigator.cpp.patch"
/bin/patch -R "$srctopatch/dom/ipc/ContentChild.cpp" "$w3credentials/ContentChild.cpp-patch"
/bin/patch -R "$srctopatch/dom/ipc/ContentChild.h" "$w3credentials/ContentChild.h-patch"
/bin/patch -R "$srctopatch/dom/ipc/ContentParent.cpp" "$w3credentials/ContentParent.cpp-patch"
/bin/patch -R "$srctopatch/dom/ipc/ContentParent.h" "$w3credentials/ContentParent.h-patch"
/bin/patch -R "$srctopatch/dom/ipc/PContent.ipdl" "$w3credentials/PContent.ipdl-patch"
