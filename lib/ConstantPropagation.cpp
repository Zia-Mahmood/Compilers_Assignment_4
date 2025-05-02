#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "ConstantPropagation.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include <vector>

using namespace llvm;

PreservedAnalyses ConstantPropagation::run(Function &F, FunctionAnalysisManager &FAM)
{
    std::vector<Instruction *> toReplace;
    for (auto &BB : F)
    {
        for (auto &I : BB)
        {
            if (auto *BinOp = dyn_cast<BinaryOperator>(&I))
            {
                if (isa<ConstantInt>(BinOp->getOperand(0)) && isa<ConstantInt>(BinOp->getOperand(1)))
                {
                    toReplace.push_back(&I);
                }
            }
        }
    }
    for (auto *I : toReplace)
    {
        BinaryOperator *binOp = cast<BinaryOperator>(I);
        ConstantInt *constOp1 = cast<ConstantInt>(binOp->getOperand(0));
        ConstantInt *constOp2 = cast<ConstantInt>(binOp->getOperand(1));
        APInt val1 = constOp1->getValue();
        APInt val2 = constOp2->getValue();
        // Skip division by zero
        if ((binOp->getOpcode() == Instruction::UDiv || binOp->getOpcode() == Instruction::SDiv ||
             binOp->getOpcode() == Instruction::URem || binOp->getOpcode() == Instruction::SRem) &&
            val2.isZero())
        {
            continue;
        }
        APInt result;
        switch (binOp->getOpcode())
        {
        case Instruction::Add:
            result = val1 + val2;
            break;
        case Instruction::Sub:
            result = val1 - val2;
            break;
        case Instruction::Mul:
            result = val1 * val2;
            break;
        case Instruction::UDiv:
            result = val1.udiv(val2);
            break;
        case Instruction::SDiv:
            result = val1.sdiv(val2);
            break;
        case Instruction::URem:
            result = val1.urem(val2);
            break;
        case Instruction::SRem:
            result = val1.srem(val2);
            break;
        case Instruction::Shl:
            result = val1 << val2;
            break;
        case Instruction::LShr:
            result = val1.lshr(val2);
            break;
        case Instruction::AShr:
            result = val1.ashr(val2);
            break;
        case Instruction::And:
            result = val1 & val2;
            break;
        case Instruction::Or:
            result = val1 | val2;
            break;
        case Instruction::Xor:
            result = val1 ^ val2;
            break;
        default:
            continue; // Skip if not a handled binary operation
        }
        Type *ty = binOp->getType();
        Constant *constResult = ConstantInt::get(ty, result);
        binOp->replaceAllUsesWith(constResult);
        binOp->eraseFromParent();
    }
    return PreservedAnalyses::none();
}

llvm::PassPluginLibraryInfo getConstantPropagationPluginInfo()
{
    return {LLVM_PLUGIN_API_VERSION, "ConstantPropagation", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                // Register the HelloWorld pass with the PassBuilder.
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "constant-propagation")
                        {
                            FPM.addPass(ConstantPropagation());
                            return true;
                        }
                        return false;
                    });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getConstantPropagationPluginInfo();
}