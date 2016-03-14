dictionary CredentialData {
  USVString id;
};

interface Credential {
  readonly attribute USVString id;
  readonly attribute DOMString type;
};

dictionary SiteBoundCredentialData : CredentialData {
  USVString name;
  USVString iconURL;
};

interface SiteBoundCredential : Credential {
  readonly attribute USVString name;
  readonly attribute USVString iconURL;
};

dictionary PasswordCredentialData : SiteBoundCredentialData {
  USVString password;
};

typedef (FormData or URLSearchParams) CredentialBodyType;

[Constructor(PasswordCredentialData data), Exposed=Window]
interface PasswordCredential : SiteBoundCredential {
  attribute USVString idName;
  attribute USVString passwordName;

  attribute CredentialBodyType? additionalData;
};

dictionary FederatedCredentialData : SiteBoundCredentialData {
  USVString provider;
  DOMString protocol;
};

[Constructor(FederatedCredentialData data), Exposed=Window]
interface FederatedCredential : SiteBoundCredential {
  readonly attribute USVString provider;
  readonly attribute DOMString? protocol;
};

partial interface Navigator {
  readonly attribute CredentialContainer credentials;
};

interface CredentialContainer {
  Promise<Credential?> get(optional CredentialRequestOptions options);
  Promise<Credential> store(Credential credential);
  Promise<void> requireUserMediation();
};

dictionary CredentialRequestOptions {
  boolean password = false;
  FederatedCredentialRequestOptions federated;

  boolean suppressUI = false;
};

dictionary FederatedCredentialRequestOptions {
  sequence<USVString> providers;
  sequence<DOMString> protocols;
};
