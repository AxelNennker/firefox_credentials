/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_Credential_h

#include "nsCOMPtr.h"
#include "nsIGlobalObject.h"
#include "mozilla/dom/Promise.h"

namespace mozilla {
class ErrorResult;
namespace dom {
class GlobalObject;
struct CredentialData;
} /* namespace dom */
} /* namespace mozilla */

#define mozilla_dom_Credential_h

#include "mozilla/Attributes.h"
#include "mozilla/ErrorResult.h"
#include "nsCycleCollectionParticipant.h"

struct JSContext;
class nsIGlobalObject;

namespace mozilla {
namespace dom {

class Credential : public nsISupports /* or NonRefcountedDOMObject if this is a non-refcounted object */
{
public:
  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_CLASS(Credential)

public:
  Credential();
  Credential(nsIGlobalObject* aGlobal, const CredentialData& data);

protected:
  virtual ~Credential();
  nsCOMPtr<nsIGlobalObject> mGlobal;
  nsString mId;
  nsString mType;
public:
  nsIGlobalObject* GetParentObject() const { return mGlobal; }

  static already_AddRefed<Credential> Constructor(const GlobalObject& global, const CredentialData& data, ErrorResult& aRv);

  void GetId(nsString& aRetVal) const { aRetVal = mId; }

  void GetType(nsString& aRetVal) const { aRetVal = mType; }
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_Credential_h
