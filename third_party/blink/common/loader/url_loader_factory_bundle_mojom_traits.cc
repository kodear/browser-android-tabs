// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/public/common/loader/url_loader_factory_bundle_mojom_traits.h"

#include <memory>
#include <utility>

#include "url/mojom/origin_mojom_traits.h"

namespace mojo {

using Traits = StructTraits<blink::mojom::URLLoaderFactoryBundleDataView,
                            std::unique_ptr<blink::URLLoaderFactoryBundleInfo>>;

// static
network::mojom::URLLoaderFactoryPtrInfo Traits::default_factory(
    BundleInfoType& bundle) {
  return std::move(bundle->default_factory_info());
}

// static
network::mojom::URLLoaderFactoryPtrInfo Traits::appcache_factory(
    BundleInfoType& bundle) {
  return std::move(bundle->appcache_factory_info());
}

// static
blink::URLLoaderFactoryBundleInfo::SchemeMap Traits::scheme_specific_factories(
    BundleInfoType& bundle) {
  return std::move(bundle->scheme_specific_factory_infos());
}

// static
blink::URLLoaderFactoryBundleInfo::OriginMap
Traits::initiator_specific_factories(BundleInfoType& bundle) {
  return std::move(bundle->initiator_specific_factory_infos());
}

// static
bool Traits::bypass_redirect_checks(BundleInfoType& bundle) {
  return bundle->bypass_redirect_checks();
}

// static
bool Traits::Read(blink::mojom::URLLoaderFactoryBundleDataView data,
                  BundleInfoType* out_bundle) {
  *out_bundle = std::make_unique<blink::URLLoaderFactoryBundleInfo>();

  (*out_bundle)->default_factory_info() =
      data.TakeDefaultFactory<network::mojom::URLLoaderFactoryPtrInfo>();
  (*out_bundle)->appcache_factory_info() =
      data.TakeAppcacheFactory<network::mojom::URLLoaderFactoryPtrInfo>();
  if (!data.ReadSchemeSpecificFactories(
          &(*out_bundle)->scheme_specific_factory_infos()))
    return false;
  if (!data.ReadInitiatorSpecificFactories(
          &(*out_bundle)->initiator_specific_factory_infos()))
    return false;

  (*out_bundle)->set_bypass_redirect_checks(data.bypass_redirect_checks());

  return true;
}

}  // namespace mojo
