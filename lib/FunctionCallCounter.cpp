#include "FunctionCallCounter.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

AnalysisKey FunctionCallCounter::Key;

FunctionCallCounter::Result FunctionCallCounter::run(Module &M, ModuleAnalysisManager &AM)
{
    Result callCounts;
    // Initialize counts for all defined functions
    for (auto &F : M)
    {
        if (!F.isDeclaration())
        {
            callCounts[F.getName()] = 0;
        }
    }
    // Count calls to defined functions
    for (auto &F : M)
    {
        for (auto &BB : F)
        {
            for (auto &I : BB)
            {
                if (auto *Call = dyn_cast<CallInst>(&I))
                {
                    if (Function *CalledFunc = Call->getCalledFunction())
                    {
                        if (!CalledFunc->isDeclaration())
                        {
                            callCounts[CalledFunc->getName()]++;
                        }
                    }
                }
            }
        }
    }
    return callCounts;
}

PreservedAnalyses FunctionCallCounterPrinter::run(Module &M, ModuleAnalysisManager &AM)
{
    auto &callCounts = AM.getResult<FunctionCallCounter>(M);
    OS << "=================================================\n";
    OS << "Function Call Counts for module:\n";
    OS << "-------------------------------------------------\n";
    const char *str1 = "FUNCTION";
    const char *str2 = "#CALLS";
    OS << format("%-20s %-10s\n", str1, str2);
    OS << "-------------------------------------------------\n";
    for (const auto &pair : callCounts)
    {
        OS << format("%-20s %-10lu\n", pair.first().str().c_str(), pair.second);
    }
    OS << "-------------------------------------------------\n\n";
    return PreservedAnalyses::all();
}

llvm::PassPluginLibraryInfo getFunctionCallCounterPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "FunctionCallCounter", LLVM_VERSION_STRING,
        [](PassBuilder &PB)
        {
            PB.registerAnalysisRegistrationCallback(
                [](ModuleAnalysisManager &MAM)
                {
                    MAM.registerPass([&]
                                     { return FunctionCallCounter(); });
                });
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>)
                {
                    if (Name == "print<function-call-counter>")
                    {
                        MPM.addPass(FunctionCallCounterPrinter(errs()));
                        return true;
                    }
                    return false;
                });
        }};
}

// Registration
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo 
llvmGetPassPluginInfo()
{
    return getFunctionCallCounterPluginInfo();
}