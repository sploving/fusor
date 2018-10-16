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
#include <iostream>

using namespace std;
using namespace llvm;

#define True true
#define False false // For Python lovers!
#define IN_SET(ELEM, SET) (SET.find(ELEM) != SET.end())  // STL sucks!!!
#define IN_MAP(KEY, MAP) (MAP.find(KEY) != MAP.end())    // STL sucks!!!
#define ISINSTANCE(OBJ_P, CLASS) (dyn_cast<CLASS>(OBJ_P))  // C++ sucks!!!

//cl::opt<uint8_t> POOL_SIZE("array_size", cl::desc("Obfuscation fusor's size"), cl::init(64));

namespace {
    struct EncodingPass : public FunctionPass {
        static char ID;

        EncodingPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
	  Module& M = *(F.getParent());
          LLVMContext& context = M.getContext(); 
          const DataLayout& DL = M.getDataLayout();
	  //const ArrayRef<unsigned> strs = DL.getNonIntegralAddressSpaces();
	  //const string strdata = strs.front();
	  const string strdata = DL.getPrivateGlobalPrefix();
	  errs() << "data layout info:" << strdata << '\n';
          return True;
        }
    };
}

char EncodingPass::ID = 1;

static RegisterPass<EncodingPass> X("encoder", "String Encoding Pass", False, False);

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerEncodingPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
  PM.add(new EncodingPass());
}
static RegisterStandardPasses RegisterMyPass1(PassManagerBuilder::EP_EarlyAsPossible, registerEncodingPass);
