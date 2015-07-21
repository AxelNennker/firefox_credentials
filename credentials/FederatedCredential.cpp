/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/CredentialContainerBinding.h"
#include "mozilla/dom/FederatedCredential.h"
#include "mozilla/dom/LocallyStoredCredential.h"

namespace mozilla {
namespace dom {


NS_IMPL_ADDREF_INHERITED(FederatedCredential, LocallyStoredCredential)
NS_IMPL_RELEASE_INHERITED(FederatedCredential, LocallyStoredCredential)
NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(FederatedCredential)
NS_INTERFACE_MAP_END_INHERITING(LocallyStoredCredential)

FederatedCredential::FederatedCredential()
{
    // Add |MOZ_COUNT_CTOR(FederatedCredential);| for a non-refcounted object.
}

FederatedCredential::~FederatedCredential()
{
    // Add |MOZ_COUNT_DTOR(FederatedCredential);| for a non-refcounted object.
}

FederatedCredential::FederatedCredential(nsIGlobalObject* aGlobal,
    const FederatedCredentialData& data)
{
  mGlobal = aGlobal;
  if (data.mName.WasPassed()) {
    mName = data.mName.Value();
  }
  if (data.mIconURL.WasPassed()) {
    mIconURL = data.mIconURL.Value();
  }
  /*
  if (data.mId.WasPassed()) {
    mId = data.mId.Value();
  }
  if (data.mName.WasPassed()) {
    mName = data.mName.Value();
  }
  if (data.mIconURL.WasPassed()) {
    mIconURL = data.mIconURL.Value();
  }
  if (data.mPassword.WasPassed()) {
    mPassword = data.mPassword.Value();
  } else {
    // FIXME throw if not passed???
  }
  */
}

already_AddRefed<FederatedCredential>
FederatedCredential::Constructor(const GlobalObject& aGlobal,
    const FederatedCredentialData& data, ErrorResult& aRv)
{
  nsCOMPtr<nsIGlobalObject> global = do_QueryInterface(aGlobal.GetAsSupports());
  MOZ_ASSERT(global, "expected a DOM window");

  nsCOMPtr<nsPIDOMWindow> window = do_QueryInterface(aGlobal.GetAsSupports());
  nsIDOMLocation* location;
  nsresult rv =  window->GetLocation(&location);
  NS_ENSURE_SUCCESS(rv, nullptr);
  /*if (isInherentlyInsecure(location)) {
    NS_WARNING("Do not use FederatedCredential on inherently insecure pages");
  }*/
  nsRefPtr<FederatedCredential> ret = new FederatedCredential(global, data);
  return ret.forget();
}

bool
FederatedCredential::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector)
{
  return FederatedCredentialBinding::Wrap(aCx, this, aGivenProto, aReflector);
}

} // namespace dom
} // namespace mozilla
