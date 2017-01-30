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

#pragma once

#include <memory>
#include <vector>

namespace nenet {

class Actvfunc;
class Synapse;

class Neuron {
 public:
  enum Type {
    hidden,
    in,
    out
  };

  Neuron(Type type) : type_(type) {}
  Neuron(int id, Type type) : id_(id), type_(type) {}

  double value() const {return value_;}
  int id() const {return id_;}
  Type type() const {return type_;}
  Neuron& addValue(double value) {value_ += value; return *this;}
  void resetValue() {value_ = 0;}

  void computeSum();
  void applyActivationFunction(const Actvfunc& func);
  void addInboundConnection(std::shared_ptr<Synapse> synapse);
  void addOutboundConnection(std::shared_ptr<Synapse> synapse);

 private:
  int    id_ {0};
  Type   type_;
  std::vector<std::shared_ptr<Synapse>> inConn_;
  std::vector<std::shared_ptr<Synapse>> outConn_;
  double value_ {};
};

}

