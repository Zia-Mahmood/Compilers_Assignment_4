#ifndef LLVM_PASSES_CONSTANT_PROPAGATION_H
#define LLVM_PASSES_CONSTANT_PROPAGATION_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

struct ConstantPropagation : public llvm::PassInfoMixin<ConstantPropagation> {
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

    static bool isRequired() { return true; }
};

#endif