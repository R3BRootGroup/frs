// ---------------------------------------------------------------------------
// -----                                                                 -----
// -----                      R3BFrsS4Data                               -----
// -----            Created 29/07/2018 by J.L. Rodriguez                 -----
// -----                                                                 -----
// ---------------------------------------------------------------------------

#include "R3BFrsS4Data.h"

R3BFrsS4Data::R3BFrsS4Data()
    : fZ(0)
    , fAq(0)
    , fXS2(0)
    , fXS4(0)
    , fAS2(0)
    , fAS4(0)
{
}

//------------------------------

R3BFrsS4Data::R3BFrsS4Data(Double_t z, Double_t aq, Double_t xs2, Double_t as2, Double_t xs4, Double_t as4)
    : fZ(z)
    , fAq(aq)
    , fXS2(xs2)
    , fAS2(as2)
    , fXS4(xs4)
    , fAS4(as4)
{
}

ClassImp(R3BFrsS4Data)
