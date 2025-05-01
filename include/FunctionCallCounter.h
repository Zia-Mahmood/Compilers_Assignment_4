#ifndef LLVM_PASSES_FUNCTION_CALL_COUNTER_H
#define LLVM_PASSES_FUNCTION_CALL_COUNTER_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

struct FunctionCallCounter : public llvm::PassInfoMixin<FunctionCallCounter> {
    llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &);

    static bool isRequired() {return true; }
};

#endif