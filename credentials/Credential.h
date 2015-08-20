/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_Credential_h
#define mozilla_dom_Credential_h

#include "js/TypeDecls.h"
#include "mozilla/Attributes.h"
#include "mozilla/ErrorResult.h"
#include "mozilla/dom/BindingDeclarations.h"
#include "nsCycleCollectionParticipant.h"
#include "nsWrapperCache.h"

#include "nsCOMPtr.h"
#include "nsIGlobalObject.h"
#include "mozilla/dom/Promise.h"

#define CREDENTIAL_IID \
{ 0xec9fef4b, 0x8c3b, 0x9fd7, \
 { 0xec, 0x03, 0xd4, 0xc2, 0x59, 0xa1, 0xe1, 0x66 } }

namespace mozilla {
class ErrorResult;
namespace dom {
class GlobalObject;
struct CredentialData;
} /* namespace dom */
} /* namespace mozilla */


struct JSContext;
class nsIGlobalObject;

namespace mozilla {
namespace dom {

class Credential : public nsISupports /* or NonRefcountedDOMObject if this is a non-refcounted object */
                 , public nsWrapperCache
{
public:
  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(Credential)

  NS_DECLARE_STATIC_IID_ACCESSOR(CREDENTIAL_IID)

public:
  Credential();
  Credential(nsIGlobalObject* aGlobal, const CredentialData& data);

protected:
  virtual ~Credential();
  nsCOMPtr<nsIGlobalObject> mGlobal;
  nsString mId;
  nsString mType;
public:
  virtual JSObject* WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto) override;

  nsIGlobalObject* GetParentObject() const { return mGlobal; }

  static already_AddRefed<Credential> Constructor(const GlobalObject& global, const CredentialData& data, ErrorResult& aRv);

  void GetId(nsString& aRetVal) const { aRetVal = mId; }

  void GetType(nsString& aRetVal) const { aRetVal = mType; }
};

NS_DEFINE_STATIC_IID_ACCESSOR(Credential, CREDENTIAL_IID)

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_Credential_h
