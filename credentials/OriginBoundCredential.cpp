/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/CredentialContainerBinding.h"
#include "mozilla/dom/OriginBoundCredential.h"
#include "mozilla/dom/Credential.h"

namespace mozilla {
namespace dom {

NS_IMPL_ADDREF_INHERITED(OriginBoundCredential, Credential)
NS_IMPL_RELEASE_INHERITED(OriginBoundCredential, Credential)

NS_INTERFACE_MAP_BEGIN(OriginBoundCredential)
NS_INTERFACE_MAP_END_INHERITING(Credential)


OriginBoundCredential::OriginBoundCredential()
{
    // Add |MOZ_COUNT_CTOR(OriginBoundCredential);| for a non-refcounted object.
}

OriginBoundCredential::~OriginBoundCredential()
{
    // Add |MOZ_COUNT_DTOR(OriginBoundCredential);| for a non-refcounted object.
}

OriginBoundCredential::OriginBoundCredential(nsIGlobalObject* aGlobal, const OriginBoundCredentialData& data)
  : Credential(aGlobal, data)
{
  if (data.mName.WasPassed()) {
    mName = data.mName.Value();
  } else {
    // FIXME throw if not passed???
  }
  if (data.mIconURL.WasPassed()) {
    mIconURL = data.mIconURL.Value();
  } else {
    // FIXME throw if not passed???
  }
}

} // namespace dom
} // namespace mozilla
