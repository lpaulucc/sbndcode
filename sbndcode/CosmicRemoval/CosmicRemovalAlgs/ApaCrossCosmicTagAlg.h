#ifndef APACROSSCOSMICTAGALG_H_SEEN
#define APACROSSCOSMICTAGALG_H_SEEN


///////////////////////////////////////////////
// ApaCrossCosmicTagAlg.h
//
// Functions for fiducial volume cosmic tagger
// T Brooks (tbrooks@fnal.gov), November 2018
///////////////////////////////////////////////

#include "sbndcode/CosmicRemoval/CosmicRemovalUtils/CosmicRemovalUtils.h"

// framework
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "fhiclcpp/ParameterSet.h" 
#include "art/Framework/Principal/Handle.h" 
#include "canvas/Persistency/Common/Ptr.h" 
#include "canvas/Persistency/Common/PtrVector.h" 
#include "art/Framework/Services/Registry/ServiceHandle.h" 
#include "art/Framework/Services/Optional/TFileService.h" 
#include "art/Framework/Services/Optional/TFileDirectory.h" 
#include "messagefacility/MessageLogger/MessageLogger.h" 

// LArSoft
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"
#include "larcore/Geometry/Geometry.h"
#include "larcorealg/Geometry/GeometryCore.h"

// Utility libraries
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Table.h"
#include "fhiclcpp/types/Atom.h"

// c++
#include <vector>
#include <utility>


namespace sbnd{

  class ApaCrossCosmicTagAlg {
  public:

    struct Config {
      using Name = fhicl::Name;
      using Comment = fhicl::Comment;

      fhicl::Atom<double> ApaDistance {
        Name("ApaDistance"),
        Comment("")
      };

      fhicl::Atom<double> Fiducial {
        Name("Fiducial"),
        Comment("")
      };

      fhicl::Atom<double> BeamTimeLimit {
        Name("BeamTimeLimit"),
        Comment("")
      };

    };

    ApaCrossCosmicTagAlg(const Config& config);

    ApaCrossCosmicTagAlg(const fhicl::ParameterSet& pset) :
      ApaCrossCosmicTagAlg(fhicl::Table<Config>(pset, {})()) {}

    ApaCrossCosmicTagAlg();

    ~ApaCrossCosmicTagAlg();

    void reconfigure(const Config& config);

    double T0FromApaCross(recob::Track track, std::vector<double> t0List, int tpc);

    bool ApaCrossCosmicTag(recob::Track track, std::vector<art::Ptr<recob::Hit>> hits, std::vector<double> t0Tpc0, std::vector<double> t0Tpc1);

  private:

    double fApaDistance;
    double fFiducial;
    double fBeamTimeLimit;

    detinfo::DetectorProperties const* fDetectorProperties;
    geo::GeometryCore const* fGeometryService;

  };

}

#endif
