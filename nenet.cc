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

#include <unistd.h>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include "softsign.h"
#include "network.h"

using namespace nenet;

void version(void) {
  std::cout << "nenet " << VERSION << std::endl;
  exit(0);
}

void usage(void) {
  std::cerr << "usage: nenet [-v]" << std::endl;
  exit(1);
}

int main(int argc, char** argv) {
  int opt;
  while ((opt = getopt(argc, argv, "v")) != -1) {
    switch (opt) {
    case 'v':
      version();
      break;
    default:
      usage();
    }
  }

  Softsign softsign;
  Network::attrs netAttrs;
  netAttrs.actvFunc = &softsign;
  netAttrs.inputSize = 2;
  netAttrs.outputSize = 1;
  netAttrs.hiddenSize = 3;
  netAttrs.hiddenDepth = 1;
  Network net(netAttrs);
  
  return 0;
}
