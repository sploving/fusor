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
#include "llvm/IR/Type.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/Support/CommandLine.h"
#include "../fusor/func_searcher.hpp"
#include "../fusor/utils.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <set>
#include <iostream>

using namespace std;
using namespace llvm;

//cl::opt<uint8_t> POOL_SIZE("array_size", cl::desc("Obfuscation fusor's size"), cl::init(64));

namespace {
    static bool hasEncoded = false;
    //struct EncodingPass : public ModulePass { //FIXME: runOnMudule crashes, but this should be better.
    struct EncodingPass : public FunctionPass {
        static char ID;

        //EncodingPass() : ModulePass(ID) {} //FIXME
        EncodingPass() : FunctionPass(ID) {}

        //bool runOnModule(Module &M) { //FIXME
        bool runOnFunction(Function &F) override {
	  Module& M = *(F.getParent());
          LLVMContext& context = M.getContext(); 
	  if (hasEncoded == false){
	      EncodeGlobals(M);
	      hasEncoded = true;
	  }
          return true;
        }
        void EncodeGlobals(Module& M){
	  vector<Constant*> elemptrs;
	  vector<GlobalVariable*> gvs;
	  Value* idx[2] = {ConstantInt::get(i32,0), ConstantInt::get(i32,0)};
	  int size = 0;
	  for(auto &iter : M.getGlobalList()){
	    if(iter.hasInitializer()){		
	      if(ConstantDataArray* data = dyn_cast<ConstantDataArray> (iter.getInitializer())){
		if(data->isString()){
		  Constant* ptr = ConstantExpr::getInBoundsGetElementPtr(data->getType(), &iter, ArrayRef<Value *>(idx,2));
		  elemptrs.emplace_back(ptr);
		  gvs.emplace_back(&iter);
	    	  errs() << data->getAsString() << "\n";
		  size ++;
		}
	      }
	    }
	  }
	  errs() << "# of Global Strings: " << size << "\n";
	  ArrayType* atype = ArrayType::get(i8p, size);
	  Constant* elements = ConstantArray::get(atype, ArrayRef<Constant*> (elemptrs));
	  auto* array = new GlobalVariable(M, (Type *) atype, false, GlobalValue::ExternalLinkage, elements, "fusor_strs");

	  for(auto &gv : gvs){
	    int offset = 0;
	    Value* idx_dyn[2] = {ConstantInt::get(i32,0), ConstantInt::get(i32,offset)};
	    bool hasInserted = false;
	    for(auto user : gv->users()){
	      errs() << "User:" << *user << "\n";
	      if(!hasInserted){
	          Value* tmp = dyn_cast<Value>(user);
	          Instruction* insertBefore = dyn_cast<Instruction>(tmp->user_back());
	          LoadInst* inst; 
		  if(insertBefore){
	            errs() << "User:" << *insertBefore << "\n";
	            inst = new LoadInst(ConstantExpr::getInBoundsGetElementPtr(atype, array, ArrayRef<Value*>(idx_dyn)),"fusor_load",insertBefore); 
	            hasInserted = true;
		  } 
		  user = dyn_cast<User>(inst);
	      }
	    }
	    offset++;
	  }
	}
        Type *i8 = Type::getInt8Ty(getGlobalContext());
        Type *i8p = Type::getInt8PtrTy(getGlobalContext());
        Type *i32 = Type::getInt32Ty(getGlobalContext());
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
