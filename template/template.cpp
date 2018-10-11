#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/CallSite.h"
#include "llvm/Support/CommandLine.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <set>

using namespace std;
using namespace llvm;

#define True true
#define False false // For Python lovers!
#define IN_SET(ELEM, SET) (SET.find(ELEM) != SET.end())  // STL sucks!!!
#define IN_MAP(KEY, MAP) (MAP.find(KEY) != MAP.end())    // STL sucks!!!
#define ISINSTANCE(OBJ_P, CLASS) (dyn_cast<CLASS>(OBJ_P))  // C++ sucks!!!

cl::opt<uint8_t> POOL_SIZE("array_size", cl::desc("Obfuscation fusor's size"), cl::init(64));


namespace {
    struct ArrayPass : public FunctionPass {
        static char ID;

        ArrayPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
          
          return True;
        }
    };
}

char ArrayPass::ID = 0;

static RegisterPass<ArrayPass> X("template", "Template Pass", False, False);

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerArrayPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
  PM.add(new ArrayPass());
}

static RegisterStandardPasses RegisterMyPass1(PassManagerBuilder::EP_EnabledOnOptLevel0, registerArrayPass);
static RegisterStandardPasses RegisterMyPass2(PassManagerBuilder::EP_OptimizerLast, registerArrayPass);
