#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Analysis.h"
#include "FunctionCallCounter.h"
#include "llvm/IR/PatternMatch.h"
#include <llvm/Pass.h>

using namespace llvm;

PreservedAnalyses FunctionCallCounter::run(Module &M, ModuleAnalysisManager &) {

    return PreservedAnalyses::all();
}

llvm::PassPluginLibraryInfo getFunctionCallCounterPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "FunctionCallCounter", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                // Register the HelloWorld pass with the PassBuilder.
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &MPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "function-call-counter")
                        {
                            MPM.addPass(FunctionCallCounter());
                            return true;
                        }
                        return false;
                    });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return getFunctionCallCounterPluginInfo();
}