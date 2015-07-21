/* -*- Mode: IDL; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */

dictionary PasswordCredentialData {
  DOMString id;
  DOMString name;
  USVString iconURL;
  DOMString password;
};

[Constructor(optional PasswordCredentialData data), Exposed=Window]
interface PasswordCredential {
  readonly attribute DOMString id;
  readonly attribute DOMString name;
  readonly attribute DOMString iconURL;
  readonly attribute DOMString password;

  Promise<Response> send(USVString url);
};

dictionary CredentialRequestOptions {
  sequence<USVString> federations;
};
  
dictionary CredentialRequest {
  CredentialRequestOptions options;
  boolean suppressUI = false;
  sequence<DOMString> types;
};

[NoInterfaceObject]
interface CredentialContainer {
  Promise<PasswordCredential?> get(optional CredentialRequest request);
  /*Promise<PasswordCredential> store(PasswordCredential credential);
  Promise<void> requireUserMediation();*/
};
