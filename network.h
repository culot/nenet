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

#include "neuron.h"
#include "synapse.h"

namespace nenet {

class Actvfunc;

class Network {
 public:
  struct attrs {
    int inputSize, outputSize, hiddenSize, hiddenDepth;
    const Actvfunc* actvFunc;
  };

  Network(const attrs& attributes)
    : attrs_(attributes) {buildNetwork();}

  const attrs& attributes() const {return attrs_;}
  int inNeuronsCount() const {return inNodes_.size();}
  int outNeuronsCount() const {return outNodes_.size();}
  int hiddenNeuronsDepth() const {return hiddenNodes_.size();}
  int hiddenNeuronsCount() const;
  int synapsesCount() const {return synapses_.size();}

  void setTrainingInputData(const std::vector<double>& input);
  std::vector<double> inputData() const;
  void setTrainingOutputData(const std::vector<double>& output);
  std::vector<double> outputData() const;
  void train();
  void dump() const;

  // For testing purposes only
  void setFixedWeights(double weight);

 private:
  attrs attrs_;
  std::vector<std::shared_ptr<Neuron>> inNodes_, outNodes_;
  std::vector<std::vector<std::shared_ptr<Neuron>>> hiddenNodes_;
  std::vector<std::shared_ptr<Synapse>> synapses_;
  std::vector<double> expectedOutput_;

  void buildNetwork();
  void buildNeurons();
  void connectNeurons();
  void forwardPropagate();
};

}

