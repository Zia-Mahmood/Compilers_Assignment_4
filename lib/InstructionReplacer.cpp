#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "InstructionReplacer.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include <vector>

using namespace llvm;

PreservedAnalyses InstructionReplacer::run(Function &F, FunctionAnalysisManager &FAM)
{
    std::vector<Instruction *> toReplace;
    for (auto &BB : F)
    {
        for (auto &I : BB)
        {
            if (auto *BinOp = dyn_cast<BinaryOperator>(&I))
            {
                if (BinOp->getOpcode() == Instruction::Add && BinOp->getOperand(0) == BinOp->getOperand(1))
                {
                    toReplace.push_back(&I);
                }
            }
        }
    }
    for (auto *I : toReplace)
    {
        Type *ty = I->getType();
        Constant *zero = ConstantInt::get(ty, 0);
        Value *operand = I->getOperand(0);
        BinaryOperator *newSub = BinaryOperator::CreateSub(zero, operand, "", I->getIterator());
        I->replaceAllUsesWith(newSub);
        I->eraseFromParent();
    }
    return PreservedAnalyses::none();
}


llvm::PassPluginLibraryInfo getInstructionReplacerPluginInfo()
{
    return {LLVM_PLUGIN_API_VERSION, "InstructionReplacer", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                // Register the HelloWorld pass with the PassBuilder.
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "instruction-replacer")
                        {
                            FPM.addPass(InstructionReplacer());
                            return true;
                        }
                        return false;
                    });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getInstructionReplacerPluginInfo();
}