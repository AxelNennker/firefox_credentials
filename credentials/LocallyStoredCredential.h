/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_LocallyStoredCredential_h
#define mozilla_dom_LocallyStoredCredential_h

#include "mozilla/Attributes.h"
#include "mozilla/ErrorResult.h"
#include "nsCycleCollectionParticipant.h"

#include "mozilla/dom/Credential.h"

struct JSContext;

namespace mozilla {
namespace dom {

class LocallyStoredCredential : public Credential
{
public:
  NS_DECL_ISUPPORTS_INHERITED

public:
  LocallyStoredCredential();
  LocallyStoredCredential(nsIGlobalObject* aGlobal, const LocallyStoredCredentialData& data);

protected:
  ~LocallyStoredCredential();
  nsString mName;
  nsString mIconURL;

public:
  void GetName(nsString& aRetVal) const { aRetVal = mName; }

  void GetIconURL(nsString& aRetVal) const { aRetVal = mIconURL; }
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_LocallyStoredCredential_h
