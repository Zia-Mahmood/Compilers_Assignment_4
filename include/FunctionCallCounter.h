#ifndef LLVM_PASSES_FUNCTION_CALL_COUNTER_H
#define LLVM_PASSES_FUNCTION_CALL_COUNTER_H

#include "llvm/ADT/StringMap.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm
{

    using ResultFunctionCallCounter = StringMap<unsigned>;

    struct FunctionCallCounter : public AnalysisInfoMixin<FunctionCallCounter>
    {
        static AnalysisKey Key;
        using Result = ResultFunctionCallCounter;
        Result run(Module &M, ModuleAnalysisManager &);
    };

    struct FunctionCallCounterPrinter : public PassInfoMixin<FunctionCallCounterPrinter>
    {
        explicit FunctionCallCounterPrinter(raw_ostream &OutS) : OS(OutS) {}
        PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);
        static bool isRequired() { return true; }

    private:
        raw_ostream &OS;
    };

}

#endif