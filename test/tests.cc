/*-
 * Copyright (c) 2017 Frederic Culot <culot@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cassert>
#include <iostream>

#include "softsign.h"
#include "network.h"

using namespace nenet;

void test_topology_minimal() {
  std::cout << "Testing network topology (minimal build) ... ";

  Softsign softsign;
  Network::attrs netAttrs;
  netAttrs.actvFunc = &softsign;
  netAttrs.inputSize = 1;
  netAttrs.outputSize = 1;
  netAttrs.hiddenSize = 1;
  netAttrs.hiddenDepth = 1;
  Network net(netAttrs);

  assert(net.hiddenNeuronsDepth() == 1);
  assert(net.hiddenNeuronsCount() == 1);
  assert(net.synapsesCount() == 2);

  std::cout << "OK" << std::endl;
}

void test_topology_small() {
  std::cout << "Testing network topology (small build) ... ";

  Softsign softsign;
  Network::attrs netAttrs;
  netAttrs.actvFunc = &softsign;
  netAttrs.inputSize = 2;
  netAttrs.outputSize = 1;
  netAttrs.hiddenSize = 3;
  netAttrs.hiddenDepth = 2;
  Network net(netAttrs);

  assert(net.hiddenNeuronsDepth() == 2);
  assert(net.hiddenNeuronsCount() == 6);
  assert(net.synapsesCount() == 18);

  std::cout << "OK" << std::endl;
}

void test_topology_large() {
  std::cout << "Testing network topology (large build) ... ";

  Softsign softsign;
  Network::attrs netAttrs;
  netAttrs.actvFunc = &softsign;
  netAttrs.inputSize = 1;
  netAttrs.outputSize = 1;
  netAttrs.hiddenSize = 128;
  netAttrs.hiddenDepth = 256;
  Network net(netAttrs);

  assert(net.hiddenNeuronsDepth() == 256);
  assert(net.hiddenNeuronsCount() == 32768);
  assert(net.synapsesCount() == 4178176);

  std::cout << "OK" << std::endl;
}

int main(int argc, char** argv) {
  test_topology_minimal();
  test_topology_small();
  test_topology_large();

  return 0;
}
