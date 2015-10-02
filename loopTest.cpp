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

struct LoopList
{
	//char function_name[SIZE];
	string *function_name ;
	int loop_num ;
	int nesting ;
	BasicBlock::iterator first_inst , last_inst ;
	struct LoopList *next ;
	struct LoopList *prev ;
};

struct LoopList *loop_list_head = NULL ;

struct LoopList *insert_at_last(struct LoopList *position , string s1 , int l_num , int nesting , BasicBlock::iterator finst , BasicBlock::iterator linst)
{
	if (position == NULL)
	{
		position = (struct LoopList *)malloc(sizeof(struct LoopList)) ;
		position->loop_num = l_num ;
		//strcpy(position->function_name,s1.c_str());
		position->function_name = new string(s1) ;
		position->nesting = nesting ;
		position->first_inst = finst ;
		position->last_inst = linst ;
		position->next = NULL ;
		position->prev = NULL ;
		return position ;
	}
	struct LoopList *newnode = (struct LoopList *)malloc(sizeof(struct LoopList)) ;
	//strcpy(newnode->function_name , s1.c_str()) ;
	newnode->function_name = new string(s1) ;
	newnode->loop_num = l_num ;
	newnode->nesting = nesting ;
	newnode->first_inst = finst ;
	newnode->last_inst = linst ;
	newnode->next = NULL ;
	newnode->prev = position ;
	position->next = newnode ;
	return newnode ;
}
int loop_list_ctr = 0 ;
struct LoopList *temp ;
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
		int countSubLoops(Loop *L)
		{
			if (L == NULL)
				return 0 ;
			vector<Loop*> subLoops = L->getSubLoops() ;
			Loop::iterator j,f ;
			j = subLoops.begin() ;
			f = subLoops.end() ;
			for (; j != f ; j++)
			{
				return 1+countSubLoops(*j) ;
			}
			return 0 ;
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
				Loop::block_iterator bb;
				BasicBlock *first_block , *last_block ;
				BasicBlock::iterator first_inst , last_inst ;
				int ctr = 0 ;
				for (bb = L->block_begin() ; bb != L->block_end() ; ++bb)
				{
					if (ctr == 0)
					{
						ctr++ ;
						first_block = *bb ;
						first_inst = first_block->begin();
					}

				}
				--bb ;
				last_block = *bb ;
				last_inst = last_block->end() ;
				--last_inst ;
				int nesting = 0 ;
				nesting = countSubLoops(*i) + 1;
				if (loop_list_ctr == 0)
				{
					loop_list_ctr++ ;
					loop_list_head = insert_at_last(loop_list_head,fname,LoopCounter,nesting,first_inst,last_inst) ;
					temp = loop_list_head ;
					
				}
				else
				{
					temp = insert_at_last(temp,fname,LoopCounter,nesting,first_inst,last_inst) ;
				}
			}
			if (F.getName() == "main")
			{
				temp = loop_list_head ;
				while (temp != NULL)
				{
					errs()<<"Function : "<<*(temp->function_name)<<" Loop : "<<temp->loop_num<<" number of nesting = "<<temp->nesting<<" 1st instruction : "<<*(temp->first_inst)<<" :: last instruction : "<<*(temp->last_inst)<<" .\n" ;
					temp = temp->next ;
				}
			}
			return false ;
		}
	} ;
}
char Loop_Type::ID = 0 ;
static RegisterPass<Loop_Type> X("LoopTest" , "Loop Test Pass") ;
