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
#include "NPFold.h"

#include "TFile.h"
#include "TList.h"
#include "TKey.h"
#include "TTree.h"

const char* FOLD = getenv("FOLD") ; 

template<typename T>
std::string DescField(TTree* t, const char* field, int edge)
{
    std::stringstream ss ; 
    
    Long64_t ni = t->GetEntries();
    ss << " field " << field 
       << " ni " << ni << std::endl 
       ; 

    T value ; 
    t->SetBranchAddress(field,&value );
       
    for(int i=0; i < ni; i++)
    {
        t->GetEntry(i);
        bool dump =  i < edge || i > ni - edge ; 
        if(dump) ss << value << std::endl ; 
    }

    std::string s = ss.str(); 
    return s ; 
}


std::string DescTree(TTree* t)
{
    std::stringstream ss ; 
    TObjArray* brs = t->GetListOfBranches(); 
    Long64_t nbr = brs->GetEntries();
    ss << " brs " << brs << std::endl ; 
    ss << " nbr " << nbr << std::endl ; 

    for(int idx=0 ; idx < nbr ; idx++)
    {
        TBranch* br = (TBranch*)brs->At(idx); 
        ss << " br.Name " << br->GetName() << std::endl ; 

        br->Print(); 
    }


    std::string s = ss.str(); 
    return s ; 
}



template<typename T>
NP* GetField(TTree* t, const char* field)
{
    T value ; 
    t->SetBranchAddress(field,&value );

    Long64_t ni = t->GetEntries();

    NP* a = NP::Make<T>(ni) ; 
    T* vv = a->values<T>(); 

    for(int i=0; i < ni; i++)
    {
        t->GetEntry(i);
        vv[i] = value ; 
    }
    return a ; 
}



std::string Desc(TFile* f )
{
    std::stringstream ss ; 

    int nk = f->GetNkeys(); 
    TList* kk = f->GetListOfKeys();  
    kk->Print(); 
    ss
        << " f " << f 
        << " kk " << kk
        << " nk " << nk 
        << std::endl
        ; 
   
    for(int i=0 ; i < nk ; i++)
    {
        TKey* k = (TKey*)kk->At(i); 
        ss << " i " << i << " k " << k << " k.GetName " << k->GetName() << std::endl ; 
    }
    TTree* t1 = (TTree*)f->Get("data");

    Long64_t ni = t1->GetEntries();
    ss << " ni " << ni << std::endl ; 


    ss << DescTree(t1) << std::endl ; 

    ss << DescField<int>(t1, "pmtID", 10); 

    std::string s = ss.str(); 
    return s ; 
}



void Convert_PMT_rootfile( const char* path_, const char* fields_ )
{
    const char* path = U::Resolve(path_); 
    std::string _fold = U::ChangeExt(path, ".root", "_root" ); 
    const char* fold = _fold.c_str(); 
    std::cout 
        << " path " << path << std::endl
        << " fold " << fold << std::endl
        ; 

    TFile* f = TFile::Open(path); 
    assert(f) ; 
    std::cout << Desc(f) ; 

    TTree* t1 = (TTree*)f->Get("data");
    std::cout << " t1 " << t1 << std::endl ; 

    std::vector<std::string> fields ; 
    NP::Split(fields, fields_, ',' ); 

    NPFold* nf = new NPFold ; 
    for(unsigned i=0 ; i < fields.size() ; i++)
    {
        const char* field = fields[i].c_str(); 
        bool is_int = field && strcmp(field, "pmtID")==0 ;  
        NP* a = is_int ? GetField<int>(t1,field) : GetField<double>(t1,field) ;  
        nf->add(field, a ); 
    }
    nf->save(fold); 
}

int main(int argc, char** argv)
{
    Convert_PMT_rootfile("$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root", "pmtID,PDE") ; 
    Convert_PMT_rootfile("$JUNOTOP/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT.root", "pmtID,QE" ) ; 

    return 0 ; 
}
