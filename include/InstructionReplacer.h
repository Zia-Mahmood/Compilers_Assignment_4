#ifndef LLVM_PASSES_INSTRUCTION_REPLACER_H
#define LLVM_PASSES_INSTRUCTION_REPLACER_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

struct InstructionReplacer : public llvm::PassInfoMixin<InstructionReplacer> {
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

    static bool isRequired() { return true; }
};

#endif