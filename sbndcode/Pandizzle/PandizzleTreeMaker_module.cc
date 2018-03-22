////////////////////////////////////////////////////////////////////////
// Class:       PandizzleTreeMaker
// Plugin Type: analyzer (art v2_10_03)
// File:        PandizzleTreeMaker_module.cc
//
// Generated at Wed Mar 21 12:07:24 2018 by Dominic Brailsford using cetskelgen
// from cetlib version v3_02_00.
////////////////////////////////////////////////////////////////////////

#include "TTree.h"

#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "lardataobj/RecoBase/Hit.h"

//Custom
#include "Pandizzle.h"
#include "sbndcode/RecoUtils/RecoUtils.h"

class PandizzleTreeMaker;


class PandizzleTreeMaker : public art::EDAnalyzer {
public:
  explicit PandizzleTreeMaker(fhicl::ParameterSet const & p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  PandizzleTreeMaker(PandizzleTreeMaker const &) = delete;
  PandizzleTreeMaker(PandizzleTreeMaker &&) = delete;
  PandizzleTreeMaker & operator = (PandizzleTreeMaker const &) = delete;
  PandizzleTreeMaker & operator = (PandizzleTreeMaker &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;

private:

  art::Ptr<simb::MCParticle> GetMCParticleFromVector(int g4_id, const std::vector<art::Ptr<simb::MCParticle> > & particles);
  void Reset();

  sbnd::Pandizzle fPandizzle;

  TTree *fTree;
  int fNHits;
  double fLength;
  bool fIsTrackLike;
  bool fIsShowerLike;
  int fMCID;
  int fMCPDG;
  int fMCNDaughters;
  bool fMCStartInTPC;
  bool fMCStopInTPC;
  double fMCStartMomX;
  double fMCStartMomY;
  double fMCStartMomZ;
  double fMCStartMomT;
  double fMCStartPosX;
  double fMCStartPosY;
  double fMCStartPosZ;
  double fMCStartPosT;


  std::string fPFParticleModuleLabel;
  std::string fTrackModuleLabel;
  std::string fShowerModuleLabel;
  std::string fPIDModuleLabel;
  std::string fVertexModuleLabel;
  std::string fLArGeantModuleLabel;
};


PandizzleTreeMaker::PandizzleTreeMaker(fhicl::ParameterSet const & p)
  :
  EDAnalyzer(p),
  fPandizzle(p),
  fPFParticleModuleLabel       (p.get<std::string>("PFParticleModuleLabel")),
  fTrackModuleLabel        (p.get<std::string>("TrackModuleLabel")),
  fShowerModuleLabel        (p.get<std::string>("ShowerModuleLabel")),
  fPIDModuleLabel        (p.get<std::string>("PIDModuleLabel")),
  fVertexModuleLabel     (p.get<std::string>("VertexModuleLabel")),
  fLArGeantModuleLabel   (p.get<std::string>("LArGeantModuleLabel"))
{
  Reset();
  art::ServiceHandle<art::TFileService> tfs;
  fTree = tfs->make<TTree>("pt","pandizzle tree");
  fTree->Branch("length",&fLength);
  fTree->Branch("nhits",&fNHits);
  fTree->Branch("istracklike",&fIsTrackLike);
  fTree->Branch("isshowerlike",&fIsShowerLike);
  fTree->Branch("mc_id",&fMCID);
  fTree->Branch("mc_pdg",&fMCPDG);
  fTree->Branch("mc_ndaughters",&fMCNDaughters);
  fTree->Branch("mc_startintpc",&fMCStartInTPC);
  fTree->Branch("mc_stopintpc",&fMCStopInTPC);
  fTree->Branch("mc_startmomx",&fMCStartMomX);
  fTree->Branch("mc_startmomy",&fMCStartMomY);
  fTree->Branch("mc_startmomz",&fMCStartMomZ);
  fTree->Branch("mc_startmomt",&fMCStartMomT);
  fTree->Branch("mc_startposx",&fMCStartPosX);
  fTree->Branch("mc_startposy",&fMCStartPosY);
  fTree->Branch("mc_startposz",&fMCStartPosZ);
  fTree->Branch("mc_startpost",&fMCStartPosT);

}

void PandizzleTreeMaker::analyze(art::Event const & e)
{

  //MCParticle
  art::Handle<std::vector<simb::MCParticle> > mcParticleListHandle;
  std::vector<art::Ptr<simb::MCParticle> > mcParticleList;
  if (e.getByLabel(fLArGeantModuleLabel, mcParticleListHandle)) art::fill_ptr_vector(mcParticleList, mcParticleListHandle);


  //PFP
  art::Handle<std::vector<recob::PFParticle> > pfParticleListHandle;
  std::vector<art::Ptr<recob::PFParticle> > pfParticleList;
  if (e.getByLabel(fPFParticleModuleLabel, pfParticleListHandle)) art::fill_ptr_vector(pfParticleList, pfParticleListHandle);

  ////Track
  //art::Handle<std::vector<recob::Track> > trackListHandle;
  //std::vector<art::Ptr<recob::Track> > trackList;
  //if (e.getByLabel(fTrackModuleLabel, trackListHandle)) art::fill_ptr_vector(trackList, trackListHandle);

  ////Shower
  //art::Handle<std::vector<recob::Shower> > showerListHandle;
  //std::vector<art::Ptr<recob::Shower> > showerList;
  //if (e.getByLabel(fShowerModuleLabel, showerListHandle)) art::fill_ptr_vector(showerList, showerListHandle);


  //art::FindManyP<recob::Track> fmTrackFromPFP(pfParticleListHandle,e,fTrackModuleLabel);
  //art::FindManyP<recob::Shower> fmShowerFromPFP(pfParticleListHandle,e,fShowerModuleLabel);

  //art::FindManyP<recob::Vertex> fmVertexFromPFP(pfParticleListHandle,e,fPFParticleModuleLabel);

  //art::FindManyP<anab::MVAPIDResult> fmPIDFromTrack(trackListHandle,e,fTrackModuleLabel);
  //art::FindManyP<anab::MVAPIDResult> fmPIDFromShower(showerListHandle,e,fShowerModuleLabel);

  //art::FindManyP<recob::Hit> fmHitFromTrack(trackListHandle,e,fTrackModuleLabel);
  //art::FindManyP<recob::Hit> fmHitFromShower(showerListHandle,e,fShowerModuleLabel);



  std::cout<<"Event: " << e.event() <<"  NPFP: " << pfParticleList.size() << std::endl;
  for (unsigned int i_pfp = 0; i_pfp < pfParticleList.size(); i_pfp++){
    art::Ptr<recob::PFParticle> pfParticle = pfParticleList[i_pfp];
    fPandizzle.Assess(pfParticle,e);
    std::vector<art::Ptr<recob::Hit> > hits = fPandizzle.GetHits();
    fLength = fPandizzle.GetLength();
    fNHits = hits.size();
    fIsTrackLike = fPandizzle.IsTrackLike();
    fIsShowerLike = fPandizzle.IsShowerLike();

    //Get the MCParticle
    int g4id = RecoUtils::TrueParticleIDFromTotalRecoHits(hits);
    art::Ptr<simb::MCParticle> particle = GetMCParticleFromVector(g4id,mcParticleList);
    if (particle.isAvailable()){
      fMCID = particle->TrackId();
      fMCPDG = particle->PdgCode();
      fMCNDaughters = particle->NumberDaughters();
      fMCStartInTPC = RecoUtils::IsInsideTPC(particle->Position(0).Vect(),0);
      fMCStopInTPC = RecoUtils::IsInsideTPC(particle->Position(particle->NumberTrajectoryPoints()-1).Vect(),0);
      fMCStartMomX = particle->Momentum(0).X();
      fMCStartMomY = particle->Momentum(0).Y();
      fMCStartMomZ = particle->Momentum(0).Z();
      fMCStartMomT = particle->Momentum(0).T();
      fMCStartPosX = particle->Position(0).X();
      fMCStartPosY = particle->Position(0).Y();
      fMCStartPosZ = particle->Position(0).Z();
      fMCStartPosT = particle->Position(0).T();
    }

    fTree->Fill();
    //art::Ptr<recob::Track> track;
    //art::Ptr<recob::Shower> shower;
    //std::vector<art::Ptr<recob::Vertex> > vertices;
    //std::vector<art::Ptr<recob::Hit> > hits;
    //if (fmTrackFromPFP.at(pfParticle.key()).size() > 0){
    //  track = fmTrackFromPFP.at(pfParticle.key())[0];
    //  hits = fmHitFromTrack.at(track.key());
    //}
    //else if (fmShowerFromPFP.at(pfParticle.key()).size() > 0) {
    //  shower = fmShowerFromPFP.at(pfParticle.key())[0];
    //  hits = fmHitFromShower.at(shower.key());
    //}

    //vertices = fmVertexFromPFP.at(pfParticle.key());

    //int g4id = RecoUtils::TrueParticleIDFromTotalRecoHits(hits);
    //art::Ptr<simb::MCParticle> particle;
    //for (unsigned int i_mcp = 0; i_mcp < mcParticleList.size(); i_mcp++){
    //  if (mcParticleList[i_mcp]->TrackId()==g4id){
    //    particle=mcParticleList[i_mcp];
    //    break;
    //  }
    //}
    //int truepdg = -9999;
    //if (particle.isAvailable()) truepdg = particle->PdgCode();
    //std::cout<<"PDG: " << pfParticle->PdgCode() << " ID: " << pfParticle->Self() << "  Parent: " << pfParticle->Parent() << "  IsPrim: " << pfParticle->IsPrimary() << "  IsTrack: " << track.isAvailable() << " IsShower: " << shower.isAvailable() << "  NVertices: " << vertices.size() << " NHits: " << hits.size() << " TruePDG: " << truepdg << std::endl;


    //bnd::Pandizzle pandizzler(pfParticle,pfParticleList,fmTrackFromPFP, fmShowerFromPFP, fmPIDFromTrack, fmPIDFromShower);
  }
  fPandizzle.Reset();
  Reset();
}

void  PandizzleTreeMaker::Reset(){
  int kDefInt = -9999;
  double kDefDoub = (double)(kDefInt);

  fNHits = kDefInt;
  fLength = kDefDoub;
  fIsTrackLike = false;
  fIsShowerLike = false;

  fMCID = kDefInt;
  fMCPDG = kDefInt;
  fMCNDaughters = kDefInt;
  fMCStartInTPC = false;
  fMCStopInTPC = false;
  fMCStartMomX = kDefDoub;
  fMCStartMomY = kDefDoub;
  fMCStartMomZ = kDefDoub;
  fMCStartMomT = kDefDoub;
  fMCStartPosX = kDefDoub;
  fMCStartPosY = kDefDoub;
  fMCStartPosZ = kDefDoub;
  fMCStartPosT = kDefDoub;

  return;
}

art::Ptr<simb::MCParticle> PandizzleTreeMaker::GetMCParticleFromVector(int g4id, const std::vector<art::Ptr<simb::MCParticle> > & particles){
  art::Ptr<simb::MCParticle> particle;

  for (unsigned i_mcp = 0; i_mcp < particles.size(); i_mcp++){
    if (g4id == particles[i_mcp]->TrackId()){
      particle = particles[i_mcp];
      break;
    }
  }
  return particle;
}

DEFINE_ART_MODULE(PandizzleTreeMaker)