#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Analysis.h"
#include "ArithmeticSimplifier.h"
#include "llvm/IR/PatternMatch.h"
#include <llvm/Pass.h>

using namespace llvm;


PreservedAnalyses ArithmeticSimplifier::run(Function &F, FunctionAnalysisManager &FAM) {
  for (BasicBlock &BB : F) {
    for (Instruction &I : make_early_inc_range(BB)) {
      if (auto *BO = dyn_cast<BinaryOperator>(&I)) {
        Value *Simplified = nullptr;
        // Handle X * 1 → X
        if (BO->getOpcode() == Instruction::Mul &&
            PatternMatch::match(BO->getOperand(1), PatternMatch::m_One())) {
          Simplified = BO->getOperand(0);
        }
        // Handle X + 0 → X
        else if (BO->getOpcode() == Instruction::Add &&
                 PatternMatch::match(BO->getOperand(1), PatternMatch::m_Zero())) {
          Simplified = BO->getOperand(0);
        }

        if (Simplified) {
          BO->replaceAllUsesWith(Simplified);
          BO->eraseFromParent();
        }
      }
    }
  }
  return PreservedAnalyses::none();
}


llvm::PassPluginLibraryInfo getArithmeticSimplifierPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "ArithmeticSimplifier", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            // Register the HelloWorld pass with the PassBuilder.
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "arithmetic-simplifier") {
                    FPM.addPass(ArithmeticSimplifier());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getArithmeticSimplifierPluginInfo();
}
