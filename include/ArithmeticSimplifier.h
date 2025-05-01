#ifndef LLVM_PASSES_ARITHMETIC_SIMPLIFIER_H
#define LLVM_PASSES_ARITHMETIC_SIMPLIFIER_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

struct ArithmeticSimplifier : public llvm::PassInfoMixin<ArithmeticSimplifier> {
  llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

  static bool isRequired() { return true; }
};

#endif

