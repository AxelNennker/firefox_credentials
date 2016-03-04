/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_PasswordCredential_h

#include "nsCOMPtr.h"
#include "nsIGlobalObject.h"
#include "mozilla/dom/Promise.h"
#include "FormData.h"
#include "mozilla/dom/URLSearchParams.h"

namespace mozilla {
class ErrorResult;
namespace dom {
class GlobalObject;
struct PasswordCredentialData;
} /* namespace dom */
} /* namespace mozilla */

#define mozilla_dom_PasswordCredential_h

#include "mozilla/Attributes.h"
#include "mozilla/ErrorResult.h"

#include "mozilla/dom/OriginBoundCredential.h"

struct JSContext;
class nsIGlobalObject;

#define PASSWORDCREDENTIAL_IID \
{ 0xec9fef4b, 0x8c3b, 0x9fd7, \
 { 0xec, 0x03, 0xd4, 0xc2, 0x59, 0xa1, 0xe1, 0x77 } }

namespace mozilla {
namespace dom {

class PasswordCredential final : public OriginBoundCredential
{
  Nullable<FormDataOrURLSearchParams> mAdditionalData;

public:
  NS_DECL_ISUPPORTS_INHERITED

  PasswordCredential();
  PasswordCredential(nsIGlobalObject* aGlobal, const PasswordCredentialData& data);
  PasswordCredential(nsIGlobalObject* aGlobal, 
    const nsString& aUsername, 
    const nsString& aPassword);

  NS_DECLARE_STATIC_IID_ACCESSOR(PASSWORDCREDENTIAL_IID)

protected:
  ~PasswordCredential();
  nsString mPassword;
  nsString mPasswordName;
  nsString mIdName;
public:
#if 0
    virtual bool WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto, JS::MutableHandle<JSObject*> aReflector) override;
#else
  virtual JSObject* WrapObject(JSContext* aCx, JS::Handle<JSObject*> aGivenProto) override;
#endif

  static already_AddRefed<PasswordCredential> Constructor(const GlobalObject& global, const PasswordCredentialData& data, ErrorResult& aRv);

  void GetPassword(nsString& aRetVal) const { aRetVal = mPassword; }

  void GetIdName(nsString& aRetVal) const { aRetVal = mIdName; };

  void SetIdName(const nsAString& aIdName) { mIdName = aIdName; };

  void GetPasswordName(nsString& aRetVal) const { aRetVal = mPassword; };

  void SetPasswordName(const nsAString& aPasswordName) { mPasswordName = aPasswordName; };

  void GetAdditionalData(Nullable<OwningFormDataOrURLSearchParams>& aRetVal) const {
    // FIXME
    aRetVal.SetNull();
  }

  void SetAdditionalData(const Nullable<FormDataOrURLSearchParams>& arg);

  // Return a raw pointer here to avoid refcounting, but make sure it's safe (the object should be kept alive by the callee).
  already_AddRefed<Promise> Send(const nsAString& url);
};

NS_DEFINE_STATIC_IID_ACCESSOR(PasswordCredential, PASSWORDCREDENTIAL_IID)

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_PasswordCredential_h
