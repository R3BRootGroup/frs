#ifndef WASAMdc_H
#define WASAMdc_H

#include "R3BDetector.h"
#include "TLorentzVector.h"

class TClonesArray;
class WASAMdcPoint;
class FairVolume;

class WASAMdc : public R3BDetector
{
  public:
    /** Default constructor **/
    WASAMdc();

    /** Standard constructor.
     *@param geoFile name of the ROOT geometry file
     *@param trans   position
     *@param rot     rotation
     */
    WASAMdc(const TString& geoFile, const TGeoTranslation& trans, const TGeoRotation& rot = TGeoRotation());

    /** Standard constructor.
     *@param geoFile name of the ROOT geometry file
     *@param combi   position + rotation
     */
    WASAMdc(const TString& geoFile, const TGeoCombiTrans& combi = TGeoCombiTrans());

    /** Destructor **/
    ~WASAMdc();

    /** Virtual method ProcessHits
     **
     ** Defines the action to be taken when a step is inside the
     ** active volume. Creates a WASAMdcPoint and adds it to the
     ** collection.
     *@param vol  Pointer to the active volume
     **/
    virtual Bool_t ProcessHits(FairVolume* vol = 0);

    virtual Bool_t CheckIfSensitive(std::string name);

    /** Virtual method BeginEvent
     **
     ** If verbosity level is set, print hit collection at the
     ** end of the event and resets it afterwards.
     **/

    virtual void BeginEvent();

    /** Virtual method EndOfEvent
     **
     ** If verbosity level is set, print hit collection at the
     ** end of the event and resets it afterwards.
     **/

    virtual void EndOfEvent();

    /** Virtual method Register
     **
     ** Registers the hit collection in the ROOT manager.
     **/
    virtual void Register();

    /** Accessor to the hit collection **/
    virtual TClonesArray* GetCollection(Int_t iColl) const;

    /** Virtual method Print
     **
     ** Screen output of hit collection.
     **/
    virtual void Print(Option_t* option = "") const;

    /** Virtual method Reset
     **
     ** Clears the hit collection
     **/
    virtual void Reset();

    /** Virtual method CopyClones
     **
     ** Copies the hit collection with a given track index offset
     *@param cl1     Origin
     *@param cl2     Target
     *@param offset  Index offset
     **/
    virtual void CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset);

    virtual void Initialize();
    virtual void SetSpecialPhysicsCuts();

    //  void SaveGeoParams();

  private:
    /** Track information to be stored until the track leaves the
    active volume. **/
    Int_t fTrackID;                   //!  track index
    Int_t fVolumeID;                  //!  volume id
    Int_t fDetCopyID;                 //!  Det volume id  // added by Marc
    Int_t fsector;                    //!  volume id
    TLorentzVector fPosIn, fPosOut;   //!  position
    TLorentzVector fMomIn, fMomOut;   //!  momentum
    Double32_t fTime_in;              //!  time when entering active volume
    Double32_t fTime_out;             //!  time when exiting active volume
    Double32_t fTime;                 //!  time
    Double32_t fLength_in;            //!  length when entering active volume
    Double32_t fLength_out;           //!  length when exiting active volume
    Double32_t fLength;               //!  length
    Double32_t fELoss;                //!  energy loss
    Int_t fPosIndex;                  //!
    TClonesArray* fTraCollection;     //!  The hit collection
    Bool_t kGeoSaved;                 //!
    TList* flGeoPar;                  //!

    Int_t fLayer[17];

    /** Private method AddHit
     **
     ** Adds a TraPoint to the HitCollection
     **/
    WASAMdcPoint* AddHit(Int_t trackID,
                         Int_t detID,
                         Int_t detCopyID,
                         TVector3 posIn,
                         TVector3 pos_out,
                         TVector3 momIn,
                         TVector3 momOut,
                         Double_t time,
                         Double_t length,
                         Double_t eLoss);

    /** Private method ResetParameters
     **
     ** Resets the private members for the track parameters
     **/
    void ResetParameters();

    Int_t GetLayerType(Int_t volID);

    ClassDef(WASAMdc, 1);
};

inline Int_t WASAMdc::GetLayerType(Int_t volID)
{

    Int_t type = -1;

    for (Int_t i = 0; i < 17; i++) {
        if (volID == fLayer[i]) {
            type = i + 1;
            return (type);
        }
    }
    return type;
}

inline void WASAMdc::ResetParameters()
{
    fTrackID = fVolumeID = 0;
    fDetCopyID = 0;
    fPosIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fPosOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fMomIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fMomOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
    fTime = fLength = fELoss = 0;
    fPosIndex = 0;
};

#endif
