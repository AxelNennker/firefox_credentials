dictionary CredentialData {
  DOMString id;
};

dictionary LocallyStoredCredentialData : CredentialData {
  DOMString name;
  USVString iconURL;
};

dictionary PasswordCredentialData : LocallyStoredCredentialData {
  DOMString password;
};

dictionary FederatedCredentialData : LocallyStoredCredentialData {
  USVString provider;
  DOMString protocol;
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

[Constructor(PasswordCredentialData data), Exposed=Window]
interface PasswordCredential : LocallyStoredCredential {
  Promise<Response> send(USVString url);
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

