#!/bin/sh
diff -r credentials/ ../firefox/dom/credentials/
diff CredentialContainer.webidl ../firefox/dom/webidl/CredentialContainer.webidl
(cd ../firefox && hg diff -U8 dom/webidl/moz.build > /tmp/webidl-moz.build.patch && diff /tmp/webidl-moz.build.patch ../W3Credentials/webidl-moz.build.patch)
(cd ../firefox && hg diff -U8 dom/base/Navigator.h > /tmp/Navigator.h.patch && diff /tmp/Navigator.h.patch ../W3Credentials/Navigator.h.patch)
(cd ../firefox && hg diff -U8 dom/base/Navigator.cpp > /tmp/Navigator.cpp.patch && diff /tmp/Navigator.cpp.patch ../W3Credentials/Navigator.cpp.patch)
#(cd ../firefox && hg diff -U8 dom/webidl/Navigator.webidl > /tmp/Navigator.webidl.patch && diff /tmp/Navigator.webidl.patch ../W3Credentials/Navigator.webidl.patch)
(cd ../firefox && hg diff -U8 dom/ipc/ContentParent.cpp > /tmp/ContentParent.cpp-patch && diff /tmp/ContentParent.cpp-patch ../W3Credentials/ContentParent.cpp-patch)
(cd ../firefox && hg diff -U8 dom/ipc/ContentParent.h > /tmp/ContentParent.h-patch && diff /tmp/ContentParent.h-patch ../W3Credentials/ContentParent.h-patch)
(cd ../firefox && hg diff -U8 dom/ipc/PContent.ipdl > /tmp/PContentipdl-patch && diff /tmp/PContentipdl-patch ../W3Credentials/PContent.ipdl-patch)
(cd ../firefox && hg diff -U8 dom/bindings/Bindings.conf > /tmp/Bindings.conf.patch && diff /tmp/Bindings.conf.patch ../W3Credentials/Bindings.conf.patch)
