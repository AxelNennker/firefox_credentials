/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_PasswordCredential_h

#include "nsCOMPtr.h"
#include "nsIGlobalObject.h"
#include "mozilla/dom/Promise.h"

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

#include "mozilla/dom/LocallyStoredCredential.h"

struct JSContext;
class nsIGlobalObject;

namespace mozilla {
namespace dom {

class PasswordCredential final : public LocallyStoredCredential
{
public:
  NS_DECL_ISUPPORTS_INHERITED

  PasswordCredential();
  PasswordCredential(nsIGlobalObject* aGlobal, const PasswordCredentialData& data);

protected:
  ~PasswordCredential();
  nsString mPassword;
public:
  static already_AddRefed<PasswordCredential> Constructor(const GlobalObject& global, const PasswordCredentialData& data, ErrorResult& aRv);

  void GetPassword(nsString& aRetVal) const { aRetVal = mPassword; }

  // Return a raw pointer here to avoid refcounting, but make sure it's safe (the object should be kept alive by the callee).
  already_AddRefed<Promise> Send(const nsAString& url);
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_PasswordCredential_h
