/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_CredentialContainer_h
#define mozilla_dom_CredentialContainer_h

#include "mozilla/Attributes.h"
#include "mozilla/ErrorResult.h"
#include "nsCOMPtr.h"
#include "nsCycleCollectionParticipant.h"
#include "nsWrapperCache.h"
#include "Promise.h"

struct JSContext;
class nsPIDOMWindow;
class nsILoginManager;

namespace mozilla {
namespace dom {

struct CredentialRequest;
class PasswordCredential;

class CredentialContainer final : public nsISupports /* or NonRefcountedDOMObject if this is a non-refcounted object */,
                                   public nsWrapperCache /* Change wrapperCache in the binding configuration if you don't want this */
{
public:
  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(CredentialContainer)

public:
  CredentialContainer(nsPIDOMWindow *aWindow);

protected:
  // FIXME add to cycle collection
  nsCOMPtr<nsPIDOMWindow> mWindow;
  ~CredentialContainer();

public:
  nsPIDOMWindow* GetParentObject() const { return mWindow; }

#if 0
  JSObject* WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector);
#else
  JSObject* WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto);
#endif
  // Return a raw pointer here to avoid refcounting, but make sure it's safe (the object should be kept alive by the callee).
  already_AddRefed<Promise> Get(const CredentialRequest& request);

  // Return a raw pointer here to avoid refcounting, but make sure it's safe (the object should be kept alive by the callee).
  already_AddRefed<Promise> Store(PasswordCredential& credential);

  // Return a raw pointer here to avoid refcounting, but make sure it's safe (the object should be kept alive by the callee).
  already_AddRefed<Promise> RequireUserMediation();
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_CredentialContainer_h
