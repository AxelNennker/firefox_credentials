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

#include "mozilla/dom/OriginBoundCredential.h"

#include "Promise.h"

struct JSContext;

namespace mozilla {
namespace dom {

#define FEDERATEDCREDENTIAL_IID \
{ 0xec9fef4b, 0x8c3b, 0x9fd7, \
 { 0xec, 0x03, 0xd4, 0xc2, 0x59, 0xa1, 0xe1, 0x88 } }

class FederatedCredential : public OriginBoundCredential
{
public:
  NS_DECL_ISUPPORTS_INHERITED

public:
  FederatedCredential();

protected:
  ~FederatedCredential();
  FederatedCredential(nsIGlobalObject* aGlobal, const FederatedCredentialData& data);

  NS_DECLARE_STATIC_IID_ACCESSOR(FEDERATEDCREDENTIAL_IID)

  nsString mProvider;
  nsString mProtocol;

public:
#if 0
  virtual bool WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector) override;
#else
  virtual JSObject* WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto) override;
#endif

  static already_AddRefed<FederatedCredential> Constructor(const GlobalObject& global, const FederatedCredentialData& data, ErrorResult& aRv);

  void GetProvider(nsString& aRetVal) const { aRetVal = mProvider; }

  void GetProtocol(nsString& aRetVal) const { aRetVal = mProtocol; }

  static // Return a raw pointer here to avoid refcounting, but make sure it's safe (the object should be kept alive by the callee).
  already_AddRefed<Promise> RegisterAsProvider(const GlobalObject& global, const nsAString& protocol);
};

NS_DEFINE_STATIC_IID_ACCESSOR(FederatedCredential, FEDERATEDCREDENTIAL_IID)

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_FederatedCredential_h
