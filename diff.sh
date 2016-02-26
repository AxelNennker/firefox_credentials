#!/bin/sh
echo "credentials/"
diff -r credentials/ ../firefox/dom/credentials/
echo "CredentialsContainer.webidl"
diff CredentialContainer.webidl ../firefox/dom/webidl/CredentialContainer.webidl
echo "webidl/moz.build"
(cd ../firefox && hg diff -U8 dom/webidl/moz.build > /tmp/webidl-moz.build.patch && diff /tmp/webidl-moz.build.patch ../W3Credentials/webidl-moz.build.patch)
echo "dom/base/Navigator.h"
(cd ../firefox && hg diff -U8 dom/base/Navigator.h > /tmp/Navigator.h.patch && diff /tmp/Navigator.h.patch ../W3Credentials/Navigator.h.patch)
echo "dom/base/Navigator.cpp"
(cd ../firefox && hg diff -U8 dom/base/Navigator.cpp > /tmp/Navigator.cpp.patch && diff /tmp/Navigator.cpp.patch ../W3Credentials/Navigator.cpp.patch)
echo "dom/ipc/ContentChild"
(cd ../firefox && hg diff -U8 dom/ipc/ContentChild.cpp > /tmp/ContentChild.cpp-patch && diff /tmp/ContentChild.cpp-patch ../W3Credentials/ContentChild.cpp-patch)
echo "dom/ipc/ContentChild.h"
(cd ../firefox && hg diff -U8 dom/ipc/ContentChild.h > /tmp/ContentChild.h-patch && diff /tmp/ContentChild.h-patch ../W3Credentials/ContentChild.h-patch)
echo "dom/ipc/ContentParent.cpp"
(cd ../firefox && hg diff -U8 dom/ipc/ContentParent.cpp > /tmp/ContentParent.cpp-patch && diff /tmp/ContentParent.cpp-patch ../W3Credentials/ContentParent.cpp-patch)
echo "dom/ipc/ContentParent.h"
(cd ../firefox && hg diff -U8 dom/ipc/ContentParent.h > /tmp/ContentParent.h-patch && diff /tmp/ContentParent.h-patch ../W3Credentials/ContentParent.h-patch)
echo "dom/ipc/PContent.ipdl"
(cd ../firefox && hg diff -U8 dom/ipc/PContent.ipdl > /tmp/PContentipdl-patch && diff /tmp/PContentipdl-patch ../W3Credentials/PContent.ipdl-patch)
echo "dom/bindings/Bindings.conf"
(cd ../firefox && hg diff -U8 dom/bindings/Bindings.conf > /tmp/Bindings.conf.patch && diff /tmp/Bindings.conf.patch ../W3Credentials/Bindings.conf.patch)
