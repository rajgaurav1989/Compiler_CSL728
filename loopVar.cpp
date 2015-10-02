#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include "llvm/IR/IntrinsicInst.h"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define SIZE 50 
using namespace llvm ;
using namespace std ;
namespace
{
	struct Loop_Type : public FunctionPass
	{
		static char ID ;
		Loop_Type() : FunctionPass(ID) {}
		void getAnalysisUsage(AnalysisUsage &AU) const
		{
			AU.addRequired<LoopInfo>();
			AU.setPreservesAll() ;
		}
		virtual bool runOnFunction(Function &F)
		{
			LoopInfo &LI = getAnalysis<LoopInfo>() ;
			string fname = F.getName() ;
			int LoopCounter = 0 ;
			for (LoopInfo::iterator i = LI.begin() , e = LI.end() ; i != e ; ++i)
			{
				Loop *L = *i ;
				LoopCounter++ ;
				errs()<<"Loop : "<<LoopCounter<<" has induction variable : "<<L->getCanonicalInductionVariable()->getName()<<" \n" ;
			}
			return false ;
		}
	};
}
char Loop_Type::ID = 0 ;
static RegisterPass<Loop_Type> X("LoopTest" , "Loop Test Pass") ;