#ifndef LLVM_PASSES_OPCODE_COUNTER_H
#define LLVM_PASSES_OPCODE_COUNTER_H

#include "llvm/ADT/StringMap.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using ResultOpcodeCounter = llvm::StringMap<unsigned>;

class OpcodeCounter : public llvm::AnalysisInfoMixin<OpcodeCounter> {
  static llvm::AnalysisKey Key;
  friend struct llvm::AnalysisInfoMixin<OpcodeCounter>;

public:
  using Result = ResultOpcodeCounter;
  Result run(llvm::Function &F, llvm::FunctionAnalysisManager &);
  OpcodeCounter::Result generateOpcodeMap(llvm::Function &F);

  static bool isRequired() { return true; }

};

class OpcodeCounterPrinter : public llvm::PassInfoMixin<OpcodeCounterPrinter> {
public:
  explicit OpcodeCounterPrinter(llvm::raw_ostream &OutS) : OS(OutS) {}
  llvm::PreservedAnalyses run(llvm::Function &Func,
                              llvm::FunctionAnalysisManager &FAM);

  static bool isRequired() { return true; }

private:
  llvm::raw_ostream &OS;
};

#endif
