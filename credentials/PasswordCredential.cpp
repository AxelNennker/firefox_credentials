#include "PasswordCredential.h"

#include "nsWrapperCache.h"

#include "mozilla/dom/CredentialContainerBinding.h"
#include "mozilla/dom/FetchBinding.h"
#include "mozilla/dom/RequestBinding.h"
#include "FormData.h"
#include "nsIDOMLocation.h"
#include "nsIIOService.h"
#include "nsIURI.h"
#include "nsNetUtil.h"
#include "mozilla/dom/Fetch.h"

namespace mozilla {
namespace dom {

// Only needed for refcounted objects.
NS_IMPL_ADDREF_INHERITED(PasswordCredential, SiteBoundCredential)
NS_IMPL_RELEASE_INHERITED(PasswordCredential, SiteBoundCredential)

NS_INTERFACE_MAP_BEGIN(PasswordCredential)
NS_INTERFACE_MAP_END_INHERITING(SiteBoundCredential)

PasswordCredential::PasswordCredential()
{
}

PasswordCredential::~PasswordCredential()
{
}

PasswordCredential::PasswordCredential(nsIGlobalObject* aGlobal, 
  const nsString& aUsername, const nsString& aPassword)
  : SiteBoundCredential(aGlobal, aUsername)
{
  mType.AssignLiteral("password");
  mPassword = aPassword;
}

PasswordCredential::PasswordCredential(nsIGlobalObject* aGlobal, const PasswordCredentialData& data)
  : SiteBoundCredential(aGlobal, data)
{
  mType.AssignLiteral("password");
  if (data.mPassword.WasPassed()) {
    mPassword = data.mPassword.Value();
  } else {
    // FIXME throw if not passed???
  }
}

#if 0
bool
PasswordCredential::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector)
{
  return PasswordCredentialBinding::Wrap(aCx, this, aGivenProto, aReflector);
}
#else
JSObject*
PasswordCredential::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto)
{
  return PasswordCredentialBinding::Wrap(aCx, this, aGivenProto);
}
#endif

/*
bool isInherentlyInsecure(nsIDOMLocation* aLocation)
{
  DOMString protocol;
  nsresult rv =  aLocation->GetProtocol(protocol);
  NS_ENSURE_SUCCESS(rv, false);
  nsString pString = protocol.AsAString();
  return pString.EqualsLiteral("http");
}

bool isInherentlyInsecure(nsCOMPtr<nsIURI> aUri)
{
  nsAutoCString schemeStr;
  nsresult rv =  aUri->GetScheme(schemeStr);
  NS_ENSURE_SUCCESS(rv, false);
  return (!(StringBeginsWith(schemeStr, NS_LITERAL_CSTRING("http")) &&
           (schemeStr.Length() == 4)));
}
*/

already_AddRefed<PasswordCredential>
PasswordCredential::Constructor(const GlobalObject& aGlobal,
    const PasswordCredentialData& data, ErrorResult& aRv)
{
  nsCOMPtr<nsIGlobalObject> global = do_QueryInterface(aGlobal.GetAsSupports());
  MOZ_ASSERT(global, "expected a DOM window");

  nsCOMPtr<nsPIDOMWindowInner> window = do_QueryInterface(aGlobal.GetAsSupports());
  nsIDOMLocation* location = window->GetLocation();
  // FIXME NS_ENSURE_SUCCESS(rv, nullptr);
  if ((location) && isInherentlyInsecure(location)) {
    NS_WARNING("Do not use PasswordCredential on inherently insecure pages");
  }
  RefPtr<PasswordCredential> ret = new PasswordCredential(global, data);
  return ret.forget();
}

/*
bool originMismatch(nsCOMPtr<nsIURI> uri) {
  // FIXME
  return false;
}
*/

already_AddRefed<Promise>
PasswordCredential::Send(const nsAString& url)
{
  MOZ_ASSERT(NS_IsMainThread(), "Called on the wrong thread");

  ErrorResult errorresult;
  nsresult rv;
  nsCOMPtr<nsIIOService> ioService(do_GetService(NS_IOSERVICE_CONTRACTID, &rv));
  if (NS_FAILED(rv)) {
    errorresult.Throw(rv);
    return nullptr;
  }
  nsCOMPtr<nsIURI> uri;
  rv = ioService->NewURI(NS_ConvertUTF16toUTF8(url), nullptr, nullptr,
                         getter_AddRefs(uri));
  if (NS_FAILED(rv)) {
    errorresult.Throw(rv);
    return nullptr;
  }
  if (originMismatch(uri)) {
    NS_WARNING("PasswordCredential::Send origin mismatch");
    return nullptr;
  }
  if (isInherentlyInsecure(uri)) {
    NS_WARNING("PasswordCredential::Send inherently insecure protocol");
    return nullptr;
  }
  RequestOrUSVString requestOrUSVString;
  requestOrUSVString.SetAsUSVString().Rebind(url.Data(), url.Length());

  RequestInit requestInit;
  requestInit.mMethod.Construct("POST");
  RefPtr<FormData> formData = new FormData();
  if (!mId.IsEmpty()) {
    formData->AddNameValuePair(NS_LITERAL_STRING("id"), mId);
  }
  if (!mName.IsEmpty()) {
    formData->AddNameValuePair(NS_LITERAL_STRING("name"), mName);
  }
  if (!mPassword.IsEmpty()) {
    formData->AddNameValuePair(NS_LITERAL_STRING("password"), mPassword);
  } else {
    NS_WARNING("password is not set in PasswordCredential. Send aborted");
    return nullptr;
  }
  ArrayBufferOrArrayBufferViewOrBlobOrFormDataOrUSVStringOrURLSearchParams body;
  requestInit.mBody.Construct();
  requestInit.mBody.Value().SetValue().SetAsFormData() = formData;

  return FetchRequest(mGlobal, requestOrUSVString, requestInit, errorresult);
}

} // namespace dom
} // namespace mozilla
