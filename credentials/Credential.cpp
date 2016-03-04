#include "Credential.h"

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

NS_IMPL_CYCLE_COLLECTION_WRAPPERCACHE(Credential, mGlobal)
NS_IMPL_CYCLE_COLLECTING_ADDREF(Credential)
NS_IMPL_CYCLE_COLLECTING_RELEASE(Credential)
NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(Credential)
  NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY
  NS_INTERFACE_MAP_ENTRY(Credential)
  NS_INTERFACE_MAP_ENTRY(nsISupports)
NS_INTERFACE_MAP_END

Credential::Credential()
{
}

Credential::~Credential()
{
}

JSObject* 
Credential::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto)
{
  return CredentialBinding::Wrap(aCx, this, aGivenProto);
}

Credential::Credential(nsIGlobalObject* aGlobal, const nsString aId)
{
  mGlobal = aGlobal;
  mId = aId;
  // assigned in constructor of derived type: mType = aType;
}

Credential::Credential(nsIGlobalObject* aGlobal, const CredentialData& data)
{
  mGlobal = aGlobal;
  if (data.mId.WasPassed()) {
    mId = data.mId.Value();
  } else {
    // FIXME throw if not passed???
  }
}

static bool isInherentlyInsecure(nsIDOMLocation* aLocation)
{
  DOMString protocol;
  nsresult rv =  aLocation->GetProtocol(protocol);
  NS_ENSURE_SUCCESS(rv, false);
  nsString pString = protocol.AsAString();
  return pString.EqualsLiteral("http");
}

static bool isInherentlyInsecure(nsCOMPtr<nsIURI> aUri)
{
  nsAutoCString schemeStr;
  nsresult rv =  aUri->GetScheme(schemeStr);
  NS_ENSURE_SUCCESS(rv, false);
  return (!(StringBeginsWith(schemeStr, NS_LITERAL_CSTRING("http")) &&
           (schemeStr.Length() == 4)));
}

already_AddRefed<Credential>
Credential::Constructor(const GlobalObject& aGlobal,
    const CredentialData& data, ErrorResult& aRv)
{
  nsCOMPtr<nsIGlobalObject> global = do_QueryInterface(aGlobal.GetAsSupports());
  MOZ_ASSERT(global, "expected a DOM window");

  nsCOMPtr<nsPIDOMWindowInner> window = do_QueryInterface(aGlobal.GetAsSupports());
  nsIDOMLocation* location =  window->GetLocation();
  if (location && isInherentlyInsecure(location)) {
    NS_WARNING("Do not use Credential on inherently insecure pages");
  }
  RefPtr<Credential> ret = new Credential(global, data);
  return ret.forget();
}

static bool originMismatch(nsCOMPtr<nsIURI> uri) {
  // FIXME
  return false;
}

} // namespace dom
} // namespace mozilla
