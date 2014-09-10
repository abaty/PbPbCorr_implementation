#include "PbPb_track_correction.h"
#include <iostream>
#include "../../ntupler/trackTree.C"

void example()
{
  //intializeCorrections loads the histograms with the corrections in them
  //should be called before using the corrections
  initializeCorrections();

/*
  Pt should be above 0.5.
  Eta should have |eta|<2.4.
  Centrality given using bins of 0.5% (200 hiBins total) i.e. 6 correspondes to 2.5-3%.
  Rmin is defined as the distance to the nearest jet with pt>50 GeV/c and |eta|<2.
  It is calculated with sqrt(dphi^2+deta^2) between the track and the jet.
  The function calculates this for you, but you have to feed it arrays with the jetPt, jetEta, jetPhi, and number of jets (nref) for each event.

  getCorrection gives the total correction with Fake and Efficiency acounted for.
  required parameters are:

  track pt
  track eta
  track phi
  centrality bin
  an array of the pt of all jets in the event
  an array of the eta of all jets in the event
  an array of the phi of all jets in the event
  the number of jets in the event

*/

//opening File
 TString directory="/mnt/hadoop/cms/store/user/velicanu/";
 const char* infname = "/HydjetDrum_Pyquen_Dijet80_FOREST_Track8_Jet24_FixedPtHatJES_v0/0";

//declaring trees
 trackTree * ftrk;
 HiTree * fhi;
 t * fjet;
 ftrk = new trackTree(Form("%s/%s.root",directory.Data(),infname));
 fhi = new HiTree(Form("%s/%s.root",directory.Data(),infname));
 fjet = new t(Form("%s/%s.root",directory.Data(),infname));

//looping over events
for(int i=0; i<2; i++)
  {
    ftrk->GetEntry(i);
    fhi->GetEntry(i);
    fjet->GetEntry(i);

    double cent = fhi->hiBin;

    //track loop
    for( int j=0; j<100; j++)
    {  
      double pt = ftrk->trkPt[j];
      double eta = ftrk->trkEta[j];
      double phi = ftrk->trkPhi[j];

      //correction is grabbed here
      double corr = getCorrection(pt,eta,phi,cent,fjet->jtpt,fjet->jteta,fjet->jtphi,fjet->nref);
      std::cout << corr << std::endl;
    }
  }
}
