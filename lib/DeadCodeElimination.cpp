#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "DeadCodeElimination.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Utils/Local.h"
#include <vector>

using namespace llvm;

PreservedAnalyses DeadCodeElimination::run(Function &F, FunctionAnalysisManager &FAM)
{
    // Step 1: Collect all allocas that are loaded from
    SmallPtrSet<const AllocaInst *, 8> loadedAllocas;
    for (auto &BB : F)
    {
        for (auto &I : BB)
        {
            if (auto *LI = dyn_cast<LoadInst>(&I))
            {
                if (auto *AI = dyn_cast<AllocaInst>(LI->getPointerOperand()))
                {
                    loadedAllocas.insert(AI);
                }
            }
        }
    }

    // Step 2: Collect dead stores (stores to allocas that are not loaded)
    std::vector<StoreInst *> deadStores;
    for (auto &BB : F)
    {
        for (auto &I : BB)
        {
            if (auto *SI = dyn_cast<StoreInst>(&I))
            {
                if (auto *AI = dyn_cast<AllocaInst>(SI->getPointerOperand()))
                {
                    if (loadedAllocas.find(AI) == loadedAllocas.end())
                    {
                        deadStores.push_back(SI);
                    }
                }
            }
        }
    }

    // Step 3: Remove dead stores
    for (auto *SI : deadStores)
    {
        SI->eraseFromParent();
    }

    // Step 4: Remove trivially dead instructions (including allocas with no users)
    std::vector<Instruction *> toRemove;
    for (auto &BB : F)
    {
        for (auto &I : BB)
        {
            if (isInstructionTriviallyDead(&I))
            {
                toRemove.push_back(&I);
            }
        }
    }

    // Step 5: Remove the collected instructions
    for (auto *I : toRemove)
    {
        I->eraseFromParent();
    }

    return PreservedAnalyses::none();
}

llvm::PassPluginLibraryInfo getDeadCodeEliminationPluginInfo()
{
    return {LLVM_PLUGIN_API_VERSION, "DeadCodeElimination", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                // Register the HelloWorld pass with the PassBuilder.
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "dead-code-elimination")
                        {
                            FPM.addPass(DeadCodeElimination());
                            return true;
                        }
                        return false;
                    });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getDeadCodeEliminationPluginInfo();
}