# Info
// --------------------------------------------------------------------------
// This file is part of jeffnye-gh/branch_prediction, made public 2024, (c) Jeff Nye
// --------------------------------------------------------------------------
# Branch prediction 

There are two models one adapted from GEM5, one adapted from various version of TAGE, 
in particular RISCY\_V\_TAGE.  The GEM5 model uses constructs from the riscv-perf-model
repo. 

The original licenses still apply to the unmodified or derived portions. See the original 
repos for the current licenses:

https://github.com/KanPard005/RISCY\_V\_TAGE
https://gem5.googlesource.com/public/gem5
https://github.com/riscv-software-src/riscv-perf-model

Otherwise the code is released under the Apache 2.0 license. See also LICENSE.

# Adapting to Map/Sparta

The GEM5 source is not/should not be used in the public Olympia model. Consider the model in
gem5\_in\_olympia an example of how to adapt a GEM5 model's clock and parameter mechanisms to
the Olympia YAML configuration and Map/Sparta clock semantics. gem5\_in\_olympia is an example.

The model in tage\_l is a good target for conversion to a Sparta Unit. The model in tage_l has
been instrumented for RTL correlation purposes. There are extra subroutine calls that aid in
RTL comparison that are not necessary for pure software models. There are also many probe
statements which have matching statements in the RTL. 

The RTL is not included in this version of the repo.

# History

The history generation is not speculative. Updates immediately follow prediction requests.
The histories are alway up to date. This will not match real hardware.

# Usage

The gem_in_olympia is not directly usable. It is a source code example.

The tage_l will correctly execute.

```
cd tage_l
make
```

Transaction tables and final memory state reports are provided.
