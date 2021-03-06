/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/CredentialContainerBinding.h"
#include "mozilla/dom/SiteBoundCredential.h"
#include "mozilla/dom/Credential.h"

namespace mozilla {
namespace dom {

NS_IMPL_ADDREF_INHERITED(SiteBoundCredential, Credential)
NS_IMPL_RELEASE_INHERITED(SiteBoundCredential, Credential)

NS_INTERFACE_MAP_BEGIN(SiteBoundCredential)
NS_INTERFACE_MAP_END_INHERITING(Credential)


SiteBoundCredential::SiteBoundCredential()
{
    // Add |MOZ_COUNT_CTOR(SiteBoundCredential);| for a non-refcounted object.
}

SiteBoundCredential::~SiteBoundCredential()
{
    // Add |MOZ_COUNT_DTOR(SiteBoundCredential);| for a non-refcounted object.
}

SiteBoundCredential::SiteBoundCredential(nsIGlobalObject* aGlobal, const nsString& aId)
  : Credential(aGlobal, aId)
{
  mName.AssignLiteral("");
  mIconURL.AssignLiteral("");
}

SiteBoundCredential::SiteBoundCredential(nsIGlobalObject* aGlobal, const SiteBoundCredentialData& data)
  : Credential(aGlobal, data)
{
  if (data.mName.WasPassed()) {
    mName = data.mName.Value();
  } else {
    // FIXME throw if not passed???
    mName.AssignLiteral("");
  }
  if (data.mIconURL.WasPassed()) {
    mIconURL = data.mIconURL.Value();
  } else {
    // FIXME throw if not passed???
    mIconURL.AssignLiteral("");
  }
}

} // namespace dom
} // namespace mozilla
