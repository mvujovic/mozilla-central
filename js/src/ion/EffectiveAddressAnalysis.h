/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef ion_EffectiveAddressAnalysis_h
#define ion_EffectiveAddressAnalysis_h

#include "ion/MIR.h"
#include "ion/MIRGraph.h"

namespace js {
namespace ion {

class EffectiveAddressAnalysis
{
    MIRGraph &graph_;

  public:
    EffectiveAddressAnalysis(MIRGraph &graph)
      : graph_(graph)
    {}

    bool analyze();
};

} /* namespace ion */
} /* namespace js */

#endif /* ion_EffectiveAddressAnalysis_h */
