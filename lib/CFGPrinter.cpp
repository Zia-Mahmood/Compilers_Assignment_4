#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Analysis.h"
#include "CFGPrinter.h"
#include "llvm/IR/PatternMatch.h"
#include <llvm/Pass.h>
#include <map>
#include <string>
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/GraphWriter.h"
#include <cstdlib>

// Comment the following line to exclude IR in DOT files
#define INCLUDE_IR

static std::string escapeDOT(const std::string &s)
{
    std::string result;
    for (char c : s)
    {
        if (c == '"')
        {
            result += "\\\"";
        }
        else
        {
            result += c;
        }
    }
    return result;
}

// comment till here

using namespace llvm;

PreservedAnalyses CFGPrinter::run(Function &F, FunctionAnalysisManager &FAM) {
    // Create the "dot_files" directory if it doesn't exist
    std::error_code EC;
    EC = sys::fs::create_directory("dot_files", true);
    if (EC)
    {
        errs() << "Error creating directory: " << EC.message() << "\n";
        return PreservedAnalyses::all();
    }

    // Set the filename to be inside "dot_files"
    std::string Filename = "dot_files/" + F.getName().str() + ".dot";
    llvm::raw_fd_ostream File(Filename, EC, llvm::sys::fs::OF_Text);
    if (EC)
    {
        errs() << "Error opening file: " << EC.message() << "\n";
        return PreservedAnalyses::all();
    }

    File << "digraph G {\n";
    File << "    subgraph cluster_" << F.getName() << " {\n";
    File << "        label = \"" << F.getName() << "\";\n";
    File << "        node [shape=box];\n";

    // Assign IDs to basic blocks
    std::map<const BasicBlock *, int> BBMap;
    int ID = 0;
    for (const BasicBlock &BB : F)
    {
        BBMap[&BB] = ID++;
    }

    // Generate nodes for basic blocks
    for (const auto &Pair : BBMap)
    {
        const BasicBlock *BB = Pair.first;
        int BBID = Pair.second;
        std::string Name = BB->hasName() ? BB->getName().str() : ("BB" + std::to_string(BBID));
        std::string Label = Name;
#ifdef INCLUDE_IR
        for (const Instruction &I : *BB)
        {
            std::string InstStr;
            raw_string_ostream RSO(InstStr);
            I.print(RSO);
            Label += "\\n" + escapeDOT(RSO.str());
        }
#endif
        File << "        node" << BBID << " [label=\"" << Label << "\"];\n";
    }

    // Add ENTRY and EXIT nodes
    File << "        ENTRY [label=\"ENTRY\", shape=ellipse];\n";
    File << "        EXIT [label=\"EXIT\", shape=ellipse];\n";
    File << "    }\n";

    // Generate edges
    const BasicBlock *EntryBB = &F.getEntryBlock();
    int EntryID = BBMap[EntryBB];
    File << "    ENTRY -> node" << EntryID << ";\n";

    int edgeCount = 0;
    for (const auto &Pair : BBMap)
    {
        const BasicBlock *BB = Pair.first;
        int BBID = Pair.second;
        const Instruction *Term = BB->getTerminator();
        if (auto *BI = dyn_cast<BranchInst>(Term))
        {
            if (BI->isConditional())
            {
                for (unsigned i = 0; i < 2; ++i)
                {
                    const BasicBlock *Succ = BI->getSuccessor(i);
                    int SuccID = BBMap[Succ];
                    std::string Label = (i == 0) ? "true" : "false";
                    File << "    node" << BBID << " -> node" << SuccID << " [label=\"" << Label << "\"];\n";
                    edgeCount++;
                }
            }
            else
            {
                const BasicBlock *Succ = BI->getSuccessor(0);
                int SuccID = BBMap[Succ];
                File << "    node" << BBID << " -> node" << SuccID << ";\n";
                edgeCount++;
            }
        }
        else if (isa<ReturnInst>(Term))
        {
            File << "    node" << BBID << " -> EXIT;\n";
            edgeCount++;
        }
    }

    File << "}\n";
    File.close();

    // Convert DOT to PNG
    std::string DotFile = "dot_files/" + F.getName().str() + ".dot";
    std::string PngFile = "dot_files/" + F.getName().str() + ".png";
    std::string Command = "dot -Tpng " + DotFile + " -o " + PngFile;
    int Result = system(Command.c_str());
    if (Result != 0)
    {
        errs() << "Failed to generate PNG for " << DotFile << "\n";
    }

    // Print summary to terminal
    errs() << "=================================================\n";
    errs() << "CFG for function '" << F.getName() << "':\n";
    errs() << "Saved to " << DotFile << "\n";
    errs() << "Basic blocks: " << BBMap.size() << "\n";
    errs() << "Edges: " << edgeCount + 1 << "\n"; // +1 for ENTRY edge
    errs() << "-------------------------------------------------\n\n";

    return PreservedAnalyses::all();
}

llvm::PassPluginLibraryInfo getCFGPrinterPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CFGPrinter", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            // Register the CFGPrinter pass with the PassBuilder.
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "cfg-printer") {
                    FPM.addPass(CFGPrinter());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize CFGPrinter when added to the pass pipeline on the
// command line, i.e. via '-passes=cfg-printer'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getCFGPrinterPluginInfo();
}