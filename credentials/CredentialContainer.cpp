/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/CredentialContainer.h"
#include "mozilla/dom/CredentialContainerBinding.h"

#include "mozilla/dom/ContentChild.h"
#include "jsfriendapi.h"
#include "nsCOMPtr.h"
#include "MainThreadUtils.h"
#include "nsXULAppAPI.h"


#include "mozilla/dom/PasswordCredential.h"


namespace mozilla {
namespace dom {

// Only needed for refcounted objects.
NS_IMPL_CYCLE_COLLECTING_ADDREF(CredentialContainer)
NS_IMPL_CYCLE_COLLECTION_WRAPPERCACHE(CredentialContainer, mWindow)
NS_IMPL_CYCLE_COLLECTING_RELEASE(CredentialContainer)
NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(CredentialContainer)
  NS_WRAPPERCACHE_INTERFACE_MAP_ENTRY
      NS_INTERFACE_MAP_ENTRY(nsISupports)
      NS_INTERFACE_MAP_END

CredentialContainer::CredentialContainer(nsPIDOMWindowInner* aWindow) :
    mWindow(aWindow)
{
  // Add |MOZ_COUNT_CTOR(CredentialContainer);| for a non-refcounted object.
}

CredentialContainer::~CredentialContainer()
{
  // Add |MOZ_COUNT_DTOR(CredentialContainer);| for a non-refcounted object.
}

#if 0
JSObject*
CredentialContainer::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector)
{
  return CredentialContainerBinding::Wrap(aCx, this, aGivenProto, aReflector);
}
#else
JSObject*
CredentialContainer::WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto)
{
  return CredentialContainerBinding::Wrap(aCx, this, aGivenProto);
}
#endif

 
/*
  if (!mLoginManager) {
    mLoginManager = do_GetService("@mozilla.org/login-manager;1");
  }
  nsILoginInfo** loginInfos;
  nsAutoString httpRealm;
  nsAutoString actionUrl;
  nsAutoString hostname;
  unsigned int count;
  mLoginManager->FindLogins(&count, hostname, actionUrl, httpRealm, &loginInfos);

 */

already_AddRefed<Promise>
CredentialContainer::Get(
    mozilla::dom::CredentialRequestOptions const& aCredentialRequest)
{
  MOZ_ASSERT(NS_IsMainThread(), "Called on the wrong thread");
  if (XRE_GetProcessType() != GeckoProcessType_Default) {
    ErrorResult result;
    nsCOMPtr<nsIGlobalObject> go = do_QueryInterface(mWindow);
    RefPtr<Promise> p = Promise::Create(go, result);
    if (result.Failed()) {
      return nullptr;
    }

    // Tell the parent process to get login credentials via PContent

#ifndef __AXEL_IPC__
    nsString prepath = NS_LITERAL_STRING("boink");    // FIXME
    ContentChild* cc = ContentChild::GetSingleton();
    RefPtr<Promise> ipcRef(p);
    cc->SendFindLogins(reinterpret_cast<uint64_t>(ipcRef.forget().take()), prepath);
#else
    PasswordCredentialData data;
    nsString username  = NS_LITERAL_STRING("20 an username");
    nsString password  = NS_LITERAL_STRING("40 an password");
    data.mIconURL.Construct();
    data.mIconURL.Value() = NS_LITERAL_STRING("30 an iconurl");
    data.mId.Construct();
    data.mId.Value() = NS_LITERAL_STRING("10 an id");
    data.mPassword.Construct();
    data.mPassword.Value() = password;
    data.mName.Construct();
    data.mName.Value() = username;
    PasswordCredential* passwordCredential = new PasswordCredential(go, data);
    p->MaybeResolve(passwordCredential);
#endif

    return p.forget();
  } else {
    return nullptr;
  }
}

already_AddRefed<Promise> 
CredentialContainer::Store(Credential& credential) {
  ErrorResult result;
  nsCOMPtr<nsIGlobalObject> go = credential.GetParentObject();
  RefPtr<Promise> p = Promise::Create(go, result);
  if (result.Failed()) {
    return nullptr;
  }
  // FIXME not implemennted
  return p.forget();
}

// Return a raw pointer here to avoid refcounting, but make sure it's safe (the object should be kept alive by the callee).
already_AddRefed<Promise> 
CredentialContainer::RequireUserMediation() {
  ErrorResult result;
  nsCOMPtr<nsIGlobalObject> go = do_QueryInterface(mWindow);
  RefPtr<Promise> p = Promise::Create(go, result);
  if (result.Failed()) {
    return nullptr;
  }
  // FIXME not implemennted
  return p.forget();
}

} // namespace dom
} // namespace mozilla

