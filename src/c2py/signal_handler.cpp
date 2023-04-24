// Copyright (c) 2017 Commissariat à l'énergie atomique et aux énergies alternatives (CEA)
// Copyright (c) 2017 Centre national de la recherche scientifique (CNRS)
// Copyright (c) 2019-2020 Simons Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0.txt
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Authors: Olivier Parcollet, Nils Wentzell

#include "./signal_handler.hpp"
#include <cstring>
#include <vector>
#include <iostream>
namespace c2py::signal_handler {
  namespace {

    std::vector<int> signals_list; //NOLINT
    bool initialized = false;      //NOLINT

    void slot(int signal) {
      std::cerr << "TRIQS : Received signal " << signal << std::endl;
      signals_list.push_back(signal);
    }
  } // namespace

  void start() {
    if (initialized) return;
    static struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = slot;
    sigaction(SIGINT, &action, nullptr);
    sigaction(SIGTERM, &action, nullptr);
    sigaction(SIGXCPU, &action, nullptr);
    sigaction(SIGQUIT, &action, nullptr);
    sigaction(SIGUSR1, &action, nullptr);
    sigaction(SIGUSR2, &action, nullptr);
    sigaction(SIGSTOP, &action, nullptr);
    initialized = true;
  }

  void stop() {
    signals_list.clear();
    initialized = false;
  }

  bool received(bool pop_) {
    //if (!initialized) start();
    bool r = signals_list.size() != 0;
    if (r && pop_) pop();
    return r;
  }

  int last() { return signals_list.back(); }
  void pop() { return signals_list.pop_back(); }
} // namespace c2py::signal_handler
