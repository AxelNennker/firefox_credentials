/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_FederatedCredential_h
#define mozilla_dom_FederatedCredential_h

#include "mozilla/Attributes.h"
#include "mozilla/ErrorResult.h"
#include "nsCycleCollectionParticipant.h"
#include "nsWrapperCache.h"

#include "mozilla/dom/LocallyStoredCredential.h"

struct JSContext;

namespace mozilla {
namespace dom {

class FederatedCredential : public LocallyStoredCredential
{
public:
  NS_DECL_ISUPPORTS_INHERITED

public:
  FederatedCredential();

protected:
  ~FederatedCredential();
  FederatedCredential(nsIGlobalObject* aGlobal, const FederatedCredentialData& data);
  nsString mProvider;
  nsString mProtocol;

public:
  bool WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector);

  static already_AddRefed<FederatedCredential> Constructor(const GlobalObject& global, const FederatedCredentialData& data, ErrorResult& aRv);

  void GetProvider(nsString& aRetVal) const { aRetVal = mProvider; }

  void GetProtocol(nsString& aRetVal) const { aRetVal = mProtocol; }
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_FederatedCredential_h
