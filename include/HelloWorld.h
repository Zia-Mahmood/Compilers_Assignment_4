#ifndef LLVM_PASSES_HELLO_WORLD_H
#define LLVM_PASSES_HELLO_WORLD_H

#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

struct HelloWorld : public llvm::PassInfoMixin<HelloWorld> {
  llvm::PreservedAnalyses run(llvm::Module &M, llvm::ModuleAnalysisManager &);

  // Without isRequired returning true, this pass will be skipped for functions
  // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
  // all functions with optnone.
  static bool isRequired() { return true; }
};

#endif

