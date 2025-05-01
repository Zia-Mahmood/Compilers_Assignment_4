#ifndef LLVM_PASSES_CFG_PRINTER_H
#define LLVM_PASSES_CFG_PRINTER_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

struct CFGPrinter : public llvm::PassInfoMixin<CFGPrinter> {
  llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);

  static bool isRequired() { return true; }
};

#endif // LLVM_PASSES_CFG_PRINTER_H