dictionary CredentialData {
  DOMString id;
  DOMString name;
  USVString iconURL;
};

interface Credential {
  readonly attribute DOMString id;
  readonly attribute DOMString type;
};
/*Credential implements Transferable;*/

interface LocallyStoredCredential : Credential {
  readonly attribute DOMString name;
  readonly attribute USVString iconURL;
};

dictionary PasswordCredentialData : CredentialData {
  DOMString password;
};

[Constructor(PasswordCredentialData data), Exposed=Window]
interface PasswordCredential : LocallyStoredCredential {
  Promise<Response> send(USVString url);
};

dictionary FederatedCredentialData : CredentialData {
  USVString provider;
  DOMString? protocol;
};

[Constructor(FederatedCredentialData data), Exposed=Window]
interface FederatedCredential : LocallyStoredCredential {
  readonly attribute USVString provider;
  readonly attribute DOMString? protocol;
};

partial interface Navigator {
  readonly attribute CredentialContainer credentials;
};

interface CredentialContainer {
  Promise<Credential?> get(optional CredentialRequest request);
  /*Promise<Credential> store(optional Credential credential);
  Promise<void> requireUserMediation();*/
};

dictionary FederatedCredentialRequestOptions {
  sequence<USVString> providers;
  sequence<DOMString> protocols;
};

typedef FederatedCredentialRequestOptions CredentialRequestOptions;

dictionary CredentialRequest {
  CredentialRequestOptions options;
  boolean suppressUI = false;
  sequence<DOMString> types;
};

