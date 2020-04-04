#include "FrsSciMapped2Tcal.h"
#include <iomanip>

// --- Default Constructor
FrsSciMapped2Tcal::FrsSciMapped2Tcal()
    : FairTask("FrsSciMapped2Tcal", 1)
    , fNumTcal(0)
    , fNevent(0)
    , fTcal(NULL)
    , fMapped(NULL)
    , fTcalPar(NULL)
    , fOnline(kFALSE)
{
}

// --- Standard Constructor
FrsSciMapped2Tcal::FrsSciMapped2Tcal(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNumTcal(0)
    , fNevent(0)
    , fTcal(NULL)
    , fMapped(NULL)
    , fTcalPar(NULL)
    , fOnline(kFALSE)
{
}

// --- Destructor
FrsSciMapped2Tcal::~FrsSciMapped2Tcal()
{
    LOG(INFO) << "FrsSciMapped2Tcal: Delete instance";
    if (fMapped)
    {
        delete fMapped;
    }
    if (fTcal)
    {
        delete fTcal;
    }
}

// --- Parameter container : reading SofSciTcalPar from FairRuntimeDb
void FrsSciMapped2Tcal::SetParContainers()
{
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb)
    {
        LOG(ERROR) << "FairRuntimeDb not opened!";
    }

    fTcalPar = (FrsSciTcalPar*)rtdb->getContainer("FrsSciTcalPar");
    if (!fTcalPar)
    {
        LOG(ERROR) << "FrsSciMapped2Tcal::SetParContainers() : Could not get access to FrsSciTcalPar-Container.";
        return;
    }
    else
    {
        LOG(INFO) << "FrsSciMapped2Tcal::SetParContainers() : FrsSciTcalPar-Container found with "
                  << fTcalPar->GetNumSignals() << " signals";
    }
}

InitStatus FrsSciMapped2Tcal::Init()
{

    LOG(INFO) << "FrsSciMapped2Tcal: Init";

    FairRootManager* rm = FairRootManager::Instance();
    if (!rm)
    {
        LOG(ERROR) << "FrsSciMapped2Tcal::Init() Couldn't instance the FairRootManager";
        return kFATAL;
    }

    // --- ----------------- --- //
    // --- INPUT MAPPED DATA --- //
    // --- ----------------- --- //
    fMapped = (TClonesArray*)rm->GetObject("VftxSciMappedData");
    if (!fMapped)
    {
        LOG(ERROR) << "FrsSciMapped2Tcal::Couldn't get handle on VftxSciMappedData container";
        return kFATAL;
    }
    else
        LOG(INFO) << "FrsSciMapped2Tcal::FrsSciMappedData items found";

    // --- ---------------- --- //
    // --- OUTPUT TCAL DATA --- //
    // --- ---------------- --- //
    fTcal = new TClonesArray("FrsSciTcalData", 10);
    if (!fOnline)
    {
        rm->Register("FrsSciTcalData", "FrsSci", fTcal, kTRUE);
    }
    else
    {
        rm->Register("FrsSciTcalData", "FrsSci", fTcal, kFALSE);
    }

    LOG(INFO) << "FrsSciMapped2Tcal::Init output FrsSciTcalData ";

    // --- -------------------------- --- //
    // --- CHECK THE TCALPAR VALIDITY --- //
    // --- -------------------------- --- //
    if (fTcalPar->GetNumSignals() == 0)
    {
        LOG(ERROR) << "FrsSciMapped2Tcal::There are no Tcal parameters for FrsSci";
        return kFATAL;
    }
    else
    {
        LOG(INFO) << "FrsSciMapped2Tcal::Init(): fNumSignals=" << fTcalPar->GetNumSignals();
        LOG(INFO) << " FrsSciMapped2Tcal::Init(): fNumDetectors=" << fTcalPar->GetNumDetectors();
        LOG(INFO) << "  FrsSciMapped2Tcal::Init(): fNumChannels=" << fTcalPar->GetNumChannels();
    }
    return kSUCCESS;
}

InitStatus FrsSciMapped2Tcal::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

void FrsSciMapped2Tcal::Exec(Option_t* option)
{
    // Reset entries in output arrays, local arrays
    Reset();
    UInt_t iDet;
    UInt_t iCh;
    UInt_t iTf;
    UInt_t iTc;
    Double_t tns;

    Int_t nHitsPerEvent_SofSci = fMapped->GetEntries();
    for (Int_t ihit = 0; ihit < nHitsPerEvent_SofSci; ihit++)
    {
        VftxSciMappedData* hit = (VftxSciMappedData*)fMapped->At(ihit);
        if (!hit)
            continue;
        iDet = hit->GetDetector();
        iCh = hit->GetPmt();
        iTf = hit->GetTimeFine();
        iTc = hit->GetTimeCoarse();
        if ((iDet < 1) || (iDet > fTcalPar->GetNumDetectors()))
        {
            LOG(INFO) << "FrsSciMapped2Tcal::Exec() : In SofSciMappedData, iDet = " << iDet
                      << "is out of range, item skipped ";
            continue;
        }
        if ((iCh < 1) || (iCh > fTcalPar->GetNumChannels()))
        {
            LOG(INFO) << "FrsSciMapped2Tcal::Exec() : In SofSciMappedData, iCh = " << iCh
                      << "is out of range, item skipped ";
            continue;
        }
        tns = CalculateTimeNs(iDet, iCh, iTf, iTc);
        AddCalData(iDet, iCh, tns);
    }
    ++fNevent;
}

// -----   Public method Reset   ------------------------------------------------
void FrsSciMapped2Tcal::Reset()
{
    LOG(DEBUG) << "Clearing TcalCalData Structure";
    if (fTcal)
        fTcal->Clear();
}

// -----   Public method Finish   -----------------------------------------------
void FrsSciMapped2Tcal::Finish() {}

// -----   Private method AddCalData  --------------------------------------------
FrsSciTcalData* FrsSciMapped2Tcal::AddCalData(Int_t iDet, Int_t iCh, Double_t tns)
{
    // It fills the R3BSofSciTcalData
    TClonesArray& clref = *fTcal;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) FrsSciTcalData(iDet, iCh, tns);
}

Double_t FrsSciMapped2Tcal::CalculateTimeNs(UShort_t iDet, UShort_t iCh, UInt_t iTf, UInt_t iTc)
{
    UInt_t rank = iTf + fTcalPar->GetNumTcalParsPerSignal() * ((iDet - 1) * fTcalPar->GetNumChannels() + (iCh - 1));
    Double_t iPar = (Double_t)fTcalPar->GetSignalTcalParams(rank);
    Double_t r = (Double_t)rand.Rndm() - 0.5;
    Double_t iTf_ns;
    Double_t iTc_ns = (Double_t)iTc * 5.;
    //  std::cout << "FrsSciMapped2Tcal::CalculateTimeNs : iDet=" << iDet << ", iCh=" << iCh << ", iTf=" << iTf << ",
    //  rank=" << rank  << std::endl;

    if (r < 0)
    {
        Double_t iParPrev = fTcalPar->GetSignalTcalParams(rank - 1);
        iTf_ns = iPar + r * (iPar - iParPrev);
    }
    else
    {
        Double_t iParNext = fTcalPar->GetSignalTcalParams(rank + 1);
        iTf_ns = iPar + r * (iParNext - iPar);
    }

    // std::cout << "Tf_ns=" << iTf_ns << ", iTc_ns=" << iTc_ns << " : TimeNs = " << 5.*iTc_ns - iTf_ns << std::endl;
    return (iTc_ns - iTf_ns);
}

ClassImp(FrsSciMapped2Tcal)
