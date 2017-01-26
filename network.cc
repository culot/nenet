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

#include <stdexcept>

#include "network.h"

namespace nenet {

  /* XXX Draw the network in Gfx class
void Network::dump() const {
  std::cout << std::endl << "********* DUMP ************" << std::endl;
  for (int i = 0; i < attrs_.inputSize; ++i) {
    auto neuron = inNodes_[i];
    neuron->dump();
  }
  for (int depth = 0; depth < attrs_.hiddenDepth; ++depth) {
    for (int i = 0; i < attrs_.hiddenSize; ++i) {
      auto neuron = hiddenNodes_[depth][i];
      neuron->dump();
    }
  }
  for (int i = 0; i < attrs_.outputSize; ++i) {
    auto neuron = outNodes_[i];
    neuron->dump();
  }
  std::cout << "********* DUMP ************" << std::endl;
}
  */

void Network::buildNetwork() {
  buildNeurons();
  connectNeurons();
}

void Network::buildNeurons() {
  for (int i = 0; i < attrs_.inputSize; ++i) {
    inNodes_.push_back(std::make_shared<Neuron>(Neuron::Type::in));
  }
  for (int i = 0; i < attrs_.outputSize; ++i) {
    outNodes_.push_back(std::make_shared<Neuron>(Neuron::Type::out));
  }
  hiddenNodes_.resize(attrs_.hiddenDepth);
  for (int depth = 0; depth < attrs_.hiddenDepth; ++depth) {
    for (int i = 0; i < attrs_.hiddenSize; ++i) {
      hiddenNodes_[depth].push_back(std::make_shared<Neuron>(Neuron::Type::hidden));
    }
  }
}

void Network::connectNeurons() {
  for (auto inNeuron : inNodes_) {
    for (auto hiddenNeuron : hiddenNodes_[0]) {
      auto synapse = std::make_shared<Synapse>(inNeuron, hiddenNeuron);
      synapses_.push_back(synapse);
      inNeuron->addOutboundConnection(synapse);
      hiddenNeuron->addInboundConnection(synapse);
    }
  }
  for (int depth = 1; depth < attrs_.hiddenDepth; ++depth) {
    for (auto& hiddenNeuron : hiddenNodes_[depth]) {
      for (auto& prevHiddenNeuron : hiddenNodes_[depth - 1]) {
        auto synapse = std::make_shared<Synapse>(prevHiddenNeuron, hiddenNeuron);
        synapses_.push_back(synapse);
        prevHiddenNeuron->addOutboundConnection(synapse);
        hiddenNeuron->addInboundConnection(synapse);
      }
    }
  }
  for (auto& outNeuron : outNodes_) {
    for (auto& hiddenNeuron : hiddenNodes_[attrs_.hiddenDepth - 1]) {
      auto synapse = std::make_shared<Synapse>(hiddenNeuron, outNeuron);
      synapses_.push_back(synapse);
      hiddenNeuron->addOutboundConnection(synapse);
      outNeuron->addInboundConnection(synapse);
    }
  }
}

int Network::hiddenNeuronsCount() const {
  if (hiddenNodes_.empty()) {
    return 0;
  }
  int hiddenSize = hiddenNodes_[0].size();
  int hiddenDepth = hiddenNodes_.size();

  return hiddenSize * hiddenDepth;
}

void Network::setTrainingInputData(const std::vector<double>& input) {
  if (input.size() != inNodes_.size()) {
    throw std::runtime_error("Training input size does not match network input size");
  }
  for (int i = 0; i < input.size(); ++i) {
    auto neuron = inNodes_[i];
    neuron->resetValue();
    neuron->addValue(input[i]);
  }
}

std::vector<double> Network::inputData() const {
  std::vector<double> inputData;
  for (const auto neuron : inNodes_) {
    inputData.push_back(neuron->value());
  }
  return inputData;
}

void Network::setTrainingOutputData(const std::vector<double>& output) {
  if (output.size() != outNodes_.size()) {
    throw std::runtime_error("Training output size does not match network output size");
  }
  expectedOutput_ = output;
}

std::vector<double> Network::outputData() const {
  std::vector<double> outputData;
  for (const auto neuron : outNodes_) {
    outputData.push_back(neuron->value());
  }
  return outputData;
}

void Network::train() {
  forwardPropagate();
}

void Network::forwardPropagate() {
  for (int layer = 0; layer < attrs_.hiddenDepth; ++layer) {
    for (auto neuron : hiddenNodes_[layer]) {
      neuron->computeSum();
      neuron->applyActivationFunction(*attrs_.actvFunc);
    }
  }
  for (auto neuron : outNodes_) {
    neuron->computeSum();
    neuron->applyActivationFunction(*attrs_.actvFunc);
  }
}

void Network::setFixedWeights(double weight) {
  for (auto synapse : synapses_) {
    synapse->setWeight(weight);
  }
}

}
