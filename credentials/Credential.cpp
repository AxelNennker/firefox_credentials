#include "Credential.h"

#include "mozilla/dom/CredentialContainerBinding.h"
#include "mozilla/dom/FetchBinding.h"
#include "mozilla/dom/RequestBinding.h"
#include "nsFormData.h"
#include "nsIDOMLocation.h"
#include "nsIIOService.h"
#include "nsIURI.h"
#include "nsNetUtil.h"
#include "mozilla/dom/Fetch.h"

namespace mozilla {
namespace dom {

// Only needed for refcounted objects.
// NS_IMPL_CYCLE_COLLECTION_WRAPPERCACHE_0(Credential)
NS_IMPL_CYCLE_COLLECTION(Credential, mGlobal)
NS_IMPL_CYCLE_COLLECTING_ADDREF(Credential)
NS_IMPL_CYCLE_COLLECTING_RELEASE(Credential)
NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(Credential)
  //NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY
  NS_INTERFACE_MAP_ENTRY(nsISupports)
NS_INTERFACE_MAP_END

Credential::Credential()
{
}

Credential::~Credential()
{
}

#if 0
bool
Credential::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector)
{
  return CredentialBinding::Wrap(aCx, this, aGivenProto, aReflector);
}
#endif

Credential::Credential(nsIGlobalObject* aGlobal, const CredentialData& data)
{
  mGlobal = aGlobal;
  if (data.mId.WasPassed()) {
    mId = data.mId.Value();
  } else {
    // FIXME throw if not passed???
  }
}

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

already_AddRefed<Credential>
Credential::Constructor(const GlobalObject& aGlobal,
    const CredentialData& data, ErrorResult& aRv)
{
  nsCOMPtr<nsIGlobalObject> global = do_QueryInterface(aGlobal.GetAsSupports());
  MOZ_ASSERT(global, "expected a DOM window");

  nsCOMPtr<nsPIDOMWindow> window = do_QueryInterface(aGlobal.GetAsSupports());
  nsIDOMLocation* location;
  nsresult rv =  window->GetLocation(&location);
  NS_ENSURE_SUCCESS(rv, nullptr);
  if (isInherentlyInsecure(location)) {
    NS_WARNING("Do not use Credential on inherently insecure pages");
  }
  nsRefPtr<Credential> ret = new Credential(global, data);
  return ret.forget();
}

bool originMismatch(nsCOMPtr<nsIURI> uri) {
  // FIXME
  return false;
}

} // namespace dom
} // namespace mozilla
