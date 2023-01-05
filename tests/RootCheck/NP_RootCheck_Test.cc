/**
NP_RootCheck_Test.cc
======================

HMM: can avoid ROOT in standalone usage altogether by making pd_vector
from "jcv PMTSimParamSvc" accessible::

    309 private:              
    310   TFile *infile;      
    311   TTree *t1;          
    312 
    313   int m_PmtTotal;    
    314   std::vector<PmtSimData> pd_vector;
    315 

Then can just grab the data into an NP array::

   std::vector<PmtSimData>& pd_vector = ...svc.pd_vector ; 
   NP* pd = NP::Make<double>( pd_vector.size(), sizeof(PmtSimData)/sizeof(double) ) ;  


**/

#include "NP.hh"

#include "TFile.h"
#include "TList.h"
#include "TKey.h"
#include "TTree.h"

int main(int argc, char** argv)
{
    const char* path = U::Resolve("$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root") ; 
    std::cout << " path " << path << std::endl ; 

    TFile* f = TFile::Open(path); 
    assert(f) ; 

    int nk = f->GetNkeys(); 

    TList* kk = f->GetListOfKeys();  

    kk->Print(); 
   
    std::cout 
        << " f " << f 
        << " kk " << kk
        << " nk " << nk 
        << std::endl
        ; 
   
    for(int i=0 ; i < nk ; i++)
    {
        TKey* k = (TKey*)kk->At(i); 
        std::cout << " i " << i << " k " << k << " k.GetName " << k->GetName() << std::endl ; 
    }



    TTree* t1 = (TTree*)f->Get("data");

    int _pmtId;
    //char* _SN;
    double _pde;
    double _gain;
    double _sigmaGain;
    double _afterPulseProb;
    double _prePulseProb;
    double _darkRate;
    double _timeSpread;
    double _timeOffset;

    t1 ->SetBranchAddress("pmtID",&_pmtId);
    //t1 ->SetBranchAddress("SN", _SN);
    t1 ->SetBranchAddress("PDE",&_pde);
    t1 ->SetBranchAddress("Gain",&_gain);
    t1 ->SetBranchAddress("Resolution",&_sigmaGain);
    t1 ->SetBranchAddress("afterPulseProb",&_afterPulseProb);
    t1 ->SetBranchAddress("prePulseProb",&_prePulseProb);
    t1 ->SetBranchAddress("DCR",&_darkRate);
    t1 ->SetBranchAddress("TTS_SS",&_timeSpread);
    t1 ->SetBranchAddress("timeOffset",&_timeOffset);

    int m_PmtTotal = 10 ; 

    for(int i=0; i<m_PmtTotal; i++)
    {
        t1->GetEntry(i);

        std::cout 
            << " _pmtId " << _pmtId
            << " _pde " << _pde 
            << std::endl 
            ;
 
        t1->Show(i); 

    }    


    return 0 ; 
}
