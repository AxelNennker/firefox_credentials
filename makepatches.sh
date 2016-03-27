#!/bin/sh
echo "credentials/"
cp -r ../firefox/dom/credentials/* credentials/
echo "CredentialsContainer.webidl"
cp  ../firefox/dom/webidl/CredentialContainer.webidl CredentialContainer.webidl
echo "webidl/moz.build"
(cd ../firefox && hg diff -U8 dom/webidl/moz.build > ../W3Credentials/webidl-moz.build.patch)
echo "dom/base/Navigator.h"
(cd ../firefox && hg diff -U8 dom/base/Navigator.h > ../W3Credentials/Navigator.h.patch)
echo "dom/base/Navigator.cpp"
(cd ../firefox && hg diff -U8 dom/base/Navigator.cpp > ../W3Credentials/Navigator.cpp.patch)
echo "dom/ipc/ContentChild.cpp"
(cd ../firefox && hg diff -U8 dom/ipc/ContentChild.cpp > ../W3Credentials/ContentChild.cpp-patch)
echo "dom/ipc/ContentChild.h"
(cd ../firefox && hg diff -U8 dom/ipc/ContentChild.h > ../W3Credentials/ContentChild.h-patch)
echo "dom/ipc/ContentParent.cpp"
(cd ../firefox && hg diff -U8 dom/ipc/ContentParent.cpp > ../W3Credentials/ContentParent.cpp-patch)
echo "dom/ipc/ContentParent.h"
(cd ../firefox && hg diff -U8 dom/ipc/ContentParent.h > ../W3Credentials/ContentParent.h-patch)
echo "dom/ipc/PContent.ipdl"
(cd ../firefox && hg diff -U8 dom/ipc/PContent.ipdl > ../W3Credentials/PContent.ipdl-patch)
echo "dom/bindings/Bindings.conf"
(cd ../firefox && hg diff -U8 dom/bindings/Bindings.conf > ../W3Credentials/Bindings.conf.patch)
