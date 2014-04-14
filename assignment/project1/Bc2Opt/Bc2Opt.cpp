//===- Bc2Opt.cpp - First Project: bytecodes to dot ---------------===//
//
// This file implements a LLVM pass which converts bytecodes to dot.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "bc2opt"

#include <iostream>
#include <fstream>

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
using namespace std;
using namespace llvm;

namespace {
struct Bc2Opt: public FunctionPass {

    static const std::string AA;
    static const std::string BB;
    static const char TAB;

    static char ID;
    std::map<std::string, int> opCounter;
    ofstream outputFile;
    int instNo;

    Bc2Opt() :
            FunctionPass(ID), instNo(0) {
        outputFile.open("file.dot");
    }

    virtual ~Bc2Opt() {
        outputFile.close();
    }

    virtual bool runOnFunction(Function &F) {
        outputFile << "digraph \"CFG for '" << F.getName().str() << "' function\" {" << endl;
        for (Function::iterator bb = F.begin(), e = F.end(); bb != e; ++bb) {
            runOnBasicBlock(bb);
        }
        outputFile << "}" << endl;

        opCounter.clear();

        return false;
    }

private:
    bool runOnBasicBlock(const Function::iterator &bb) {
        if (opCounter.find(bb->getName().str()) == opCounter.end()) {
            opCounter[bb->getName().str()] = instNo++;
        }
        outputFile << TAB << AA << opCounter[bb->getName().str()] << " [shape=record, label=\"{" << BB << opCounter[bb->getName().str()] << ": " << "\\l\\l ";

        std::vector<int> targetVector;
        for (BasicBlock::iterator i = bb->begin(), e = bb->end(); i != e; ++i) {
            //outputFile << endl;
            runOnInstruction(targetVector, i);
        }
        outputFile << "}\"];" << endl;
        for (std::vector<int>::iterator rit = targetVector.begin(); rit != targetVector.end(); ++rit) {
            outputFile << TAB << AA << opCounter[bb->getName().str()] << "->" << AA << *rit <<";"<< endl;
        }
        targetVector.clear();

        return false;
    }

    bool runOnInstruction(std::vector<int> &targetVector, const BasicBlock::iterator i) {
        if (!strcmp(i->getOpcodeName(), "br")) {
            outputFile << i->getOpcodeName() << " ";
            int total = 0;
            for (User::op_iterator O = i->op_begin(), E = i->op_end(); O != E; ++O)
                total++;
            int count = 0;
            for (User::op_iterator O = i->op_begin(), E = i->op_end(); O != E; ++O) {
                count++;
                if (total == 1 || count > 1) {
                    string bbDest = O->get()->getName().str();
                    if (opCounter.find(bbDest) == opCounter.end()) {
                        opCounter[bbDest] = instNo++;
                    }
                    outputFile << " " << BB << opCounter[bbDest];
                    targetVector.push_back(opCounter[bbDest]);
                } else {
                    outputFile << "%"<<instNo<<" ";
                }

            }
        } else
            if(PHINode *phi = dyn_cast<PHINode>(i)) {
                outputFile << "%"<<instNo++<< " = "<< phi->getOpcodeName()<< " ";
                for(unsigned u = 0; u < phi->getNumIncomingValues(); u++) {
                    outputFile <<phi->getIncomingBlock(u)<<" ,"<< phi->getIncomingValue(u)<< " ";
                }
            }
            else {
                outputFile << "%"<<instNo++<< " = "<< i->getOpcodeName() << " ";
                for (User::op_iterator O = i->op_begin(), E = i->op_end(); O != E; ++O) {
                    //outputFile << O->get()->getValueName() << " ";
                    if (O->getUser()->getName().str().length()>0){
                        outputFile << " %"<<O->get()->getName().str();
                        outputFile << "teste henrique";
                    }
                }
            }

        outputFile << "\\l";

        return false;
    }

};
}

char Bc2Opt::ID = 0;
const std::string Bc2Opt::AA = "AA";
const std::string Bc2Opt::BB = "BB";
const char Bc2Opt::TAB = '\t';

static RegisterPass<Bc2Opt> X("bc2opt", "Converts bitcode to opt according to First Project instructions");

