#ifndef LLVM_PASSES_DEAD_CODE_ELIMINATION_H
#define LLVM_PASSES_DEAD_CODE_ELIMINATION_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

struct DeadCodeElimination : public llvm::PassInfoMixin<DeadCodeElimination>
{
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

    static bool isRequired() { return true; }
};

#endif