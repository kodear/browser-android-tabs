// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/public/test/content_cert_verifier_browser_test.h"

#include "content/shell/browser/shell_url_request_context_getter.h"

namespace content {

CertVerifierBrowserTest::CertVerifierBrowserTest() = default;

CertVerifierBrowserTest::~CertVerifierBrowserTest() = default;

void CertVerifierBrowserTest::SetUpCommandLine(
    base::CommandLine* command_line) {
  if (mock_cert_verifier_disabled_)
    return;

  mock_cert_verifier_.SetUpCommandLine(command_line);
}

void CertVerifierBrowserTest::SetUpInProcessBrowserTestFixture() {
  if (mock_cert_verifier_disabled_)
    return;

  ShellURLRequestContextGetter::SetCertVerifierForTesting(
      mock_cert_verifier_.mock_cert_verifier_internal());

  mock_cert_verifier_.SetUpInProcessBrowserTestFixture();
}

void CertVerifierBrowserTest::TearDownInProcessBrowserTestFixture() {
  if (mock_cert_verifier_disabled_)
    return;

  ShellURLRequestContextGetter::SetCertVerifierForTesting(nullptr);
  mock_cert_verifier_.TearDownInProcessBrowserTestFixture();
}

}  // namespace content
