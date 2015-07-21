#!/bin/sh
srctopatch="/home/ignisvulpis/mozilla/firefox"
w3credentials="/home/ignisvulpis/mozilla/W3Credentials"
echo $srctopatch
echo $w3credentials
rm -rf "$srctopatch/dom/credentials/"
rm -f "$srctopatch/dom/webidl/CredentialContainer.webidl"
rm -rf "$srctopatch/dom/interfaces/credentials/"
/usr/local/bin/patch -R "$srctopatch/dom/moz.build" "$w3credentials/moz.build.patch"
/usr/local/bin/patch -R "$srctopatch/dom/bindings/Bindings.conf" "$w3credentials/Bindings.conf.patch"
/usr/local/bin/patch -R "$srctopatch/dom/webidl/moz.build" "$w3credentials/webidl-moz.build.patch"
#patch -R ../firefox/dom/webidl/Navigator.webidl Navigator.webidl.patch"
/usr/local/bin/patch -R "$srctopatch/dom/base/Navigator.h" "$w3credentials/Navigator.h.patch"
/usr/local/bin/patch -R "$srctopatch/dom/base/Navigator.cpp" "$w3credentials/Navigator.cpp.patch"
/usr/local/bin/patch -R "$srctopatch/dom/ipc/ContentParent.cpp" "$w3credentials/ContentParent.cpp-patch"
/usr/local/bin/patch -R "$srctopatch/dom/ipc/ContentParent.h" "$w3credentials/ContentParent.h-patch"
/usr/local/bin/patch -R "$srctopatch/dom/ipc/PContent.ipdl" "$w3credentials/PContent.ipdl-patch"
