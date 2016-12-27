#include "TROOT.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TList.h"
#include "TLegendEntry.h"
#include "string.h"
#include <iostream>
#include "TTreeReader.h"
#include "TChain.h"
#include "TProfile.h"
#include <cmath>
#include "TProfile2D.h"
#include "TH2D.h"

void fill_taugun2_Reweight(int isample=0){

  TChain *chain = new TChain("TreeMaker2/PreSelection");

  if (isample==0){
    //chain->Add("/data3/store/user/hatake/hadtau/Rishi_taugan_tree_20150605/*.root");
    //chain->Add("/home/arane/work/Analysis_May11/CMSSW_8_0_20/src/Sep13_NewTemplate/TreeFiles/taugun_*_RA2AnalysisTree.root");
    chain->Add("/eos/uscms/store/user/arane/SingleW_TreeFiles/Wgun_*_RA2AnalysisTree.root");
    /*
    chain->Add("/home/arane/work/Analysis_May11/CMSSW_8_0_20/src/Sep13_NewTemplate/TreeFiles/taugun_5_RA2AnalysisTree.root");
    chain->Add("/home/arane/work/Analysis_May11/CMSSW_8_0_20/src/Sep13_NewTemplate/TreeFiles/taugun_6_RA2AnalysisTree.root");
    chain->Add("/home/arane/work/Analysis_May11/CMSSW_8_0_20/src/Sep13_NewTemplate/TreeFiles/taugun_7_RA2AnalysisTree.root");
    chain->Add("/home/arane/work/Analysis_May11/CMSSW_8_0_20/src/Sep13_NewTemplate/TreeFiles/taugun_8_RA2AnalysisTree.root");
    chain->Add("/home/arane/work/Analysis_May11/CMSSW_8_0_20/src/Sep13_NewTemplate/TreeFiles/taugun_9_RA2AnalysisTree.root");
    chain->Add("/home/arane/work/Analysis_May11/CMSSW_8_0_20/src/Sep13_NewTemplate/TreeFiles/taugun_10_RA2AnalysisTree.root");
    */
    }

  TTreeReader *tReader;
  tReader = new TTreeReader((TTree *)chain);
  
  TFile *f2;
  //  if (isample==0) f2 = TFile::Open("hist_taugun_aditee_Reweighted.root",      "RECREATE");
  TFile *fWeights = TFile::Open("hist_WgunTemplateReweight.root");
  //const char *ReweightHists[4]={"Reweight_0","Reweight_1","Reweight_2","Reweight_3"};
  //  TTreeReaderValue<Float_t> getMETPt(*tReader, "METPt");

  TTreeReaderValue<std::vector<int>>  getGenParentId(*tReader, "GenParticles_ParentId");
  TTreeReaderValue<std::vector<int>>  getGenPdgID(*tReader, "GenParticles_PdgId");
  TTreeReaderValue<std::vector<int>>  getGenParentStatus(*tReader, "GenParticles_Status");
  TTreeReaderValue<std::vector<TLorentzVector>>  getGenParts(*tReader, "GenParticles");
  TTreeReaderValue<std::vector<TLorentzVector>>  getGenTaus(*tReader, "GenTaus");
  TTreeReaderValue<std::vector<TLorentzVector>>  getGenTauNu(*tReader, "GenTaus_Nu");
  TTreeReaderValue<std::vector<bool>>  getGenTauHad(*tReader, "GenTaus_had");
  TTreeReaderValue<std::vector<TLorentzVector>>  getJets(*tReader, "Jets"); 
  TTreeReaderValue<std::vector<TLorentzVector>>  getSoftJets(*tReader, "SoftJets");

 
  int events = chain->GetEntries();
  //  std::cout << events << std::endl;

  TH1F *hTauResp_0  = new TH1F("hTauResp_0","hTauResp_0",50,0.,2.5);
  TH1F *hTauResp_1  = new TH1F("hTauResp_1","hTauResp_1",50,0.,2.5);
  TH1F *hTauResp_2  = new TH1F("hTauResp_2","hTauResp_2",50,0.,2.5);
  TH1F *hTauResp_3  = new TH1F("hTauResp_3","hTauResp_3",50,0.,2.5);

  TH1F *hTauRespGen_0  = new TH1F("hTauRespGen_0","hTauRespGen_0",50,0.,2.5);
  TH1F *hTauRespGen_1  = new TH1F("hTauRespGen_1","hTauRespGen_1",50,0.,2.5);
  TH1F *hTauRespGen_2  = new TH1F("hTauRespGen_2","hTauRespGen_2",50,0.,2.5);
  TH1F *hTauRespGen_3  = new TH1F("hTauRespGen_3","hTauRespGen_3",50,0.,2.5);
  hTauResp_0->Sumw2();
  hTauResp_1->Sumw2();
  hTauResp_2->Sumw2();
  hTauResp_3->Sumw2();
  hTauRespGen_0->Sumw2();
  hTauRespGen_1->Sumw2();
  hTauRespGen_2->Sumw2();
  hTauRespGen_3->Sumw2();
  TH2D * tau_GenJetPhi = new TH2D("tau_GenJetPhi","DPhi between gen and jet tau vs. their energy ratio",50,0.,2.5,100,-1.0,1.0);
  int nEvents=0;
  int n_20_30=0;
  int n_30_50=0;
  int n_50_100=0;
  int n_Above_100=0;    
  TH1F *hGenPt_0  = new TH1F("hGenPt_0","hGenPt_0",10,20.,30);
  TH1F *hGenPt_1  = new TH1F("hGenPt_1","hGenPt_1",20,30.,50);
  TH1F *hGenPt_2  = new TH1F("hGenPt_2","hGenPt_2",50,50.,100);
  TH1F *hGenPt_3  = new TH1F("hGenPt_3","hGenPt_3",70,100.,170);
  TH1F *hGenPt  = new TH1F("hGenPt","hGenPt",380,20.,400);
  hGenPt_0->Sumw2();
  hGenPt_1->Sumw2();
  hGenPt_2->Sumw2();
  hGenPt_3->Sumw2();
  hGenPt->Sumw2();    
  int noMatch=0;
  int noGenMatch=0;
  int NoMatch_Pt_4=0;
  int NoMatch_Pt_4_AbovedRcut=0;
  int NoMatch_Pt_4_AbovedRcut_VisGenJetBelow10=0;
  int Eta_Gt_2Pt1=0;
  int NoslimJet=0;
  int MatchFound=0;
  //for (int i = 0; i < events; i++) {
  while(tReader->Next()){
    //chain->GetEntry(i);
    nEvents++;
    if (nEvents%10000 == 0) {
      // A very simple progress indicator
      // Print the entry number every thousandth time
      cout <<" nEvt "<< nEvents << endl;
    }
    //    if(nEvents>100000)break;


    TLorentzVector tlv_gentau;
    TLorentzVector tlv_gentaunu;
    TLorentzVector tlv_gentauvisible;
    //TLorentzVector tlv_Gentauvisible;
    TLorentzVector tlv_slimjet;
    TLorentzVector tlv_jet;
    TLorentzVector tlv_genjet;

    int jmatch=-1;
    int jmatchGen=-1;
    double dRmin=100.;
    double dRmin_gen=100.;
    int HadTaus=0;
    double genPt=0.;
    double genEta=0.;
    double genPhi=0.;
    double dRmatch=0.4;
    double dR=0.;
    double dR_gen=0.;
    vector<TLorentzVector> slimJets;
    for(unsigned int idx = 0; idx < (*getJets).size(); idx++){
      slimJets.push_back((*getJets).at(idx));
    }
    for(unsigned int idx = 0; idx < (*getSoftJets).size(); idx++){
      slimJets.push_back((*getSoftJets).at(idx));
    }
    //std::cout<<" Jets_size "<<(*getJets).size()<<endl;
    //std::cout<<" SoftJets_size "<<(*getSoftJets).size()<<endl;
    //std::cout<<" slimJets_size "<<slimJets.size()<<endl;

    for(unsigned int idx = 0; idx < (*getGenParts).size(); idx++){
      if ((*getGenPdgID).at(idx)==15 && (*getGenTauHad).size()==1 ){
	HadTaus++;
      }
    }
    if(HadTaus!=(*getGenTaus).size())
      std::cout<<" nEvt "<<nEvents<<" Tau does not decay hadronically "<<endl;

    //std::cout<<" tau_nu size "<<(*getGenTauNu).size()<<endl;
    tlv_gentau.SetPtEtaPhiM((*getGenTaus).at(0).Pt(),
			    (*getGenTaus).at(0).Eta(),
			    (*getGenTaus).at(0).Phi(),
			    (*getGenTaus).at(0).M());
    tlv_gentaunu.SetPtEtaPhiM((*getGenTauNu).at(0).Pt(),
			      (*getGenTauNu).at(0).Eta(),
			      (*getGenTauNu).at(0).Phi(),
			      (*getGenTauNu).at(0).M());
    tlv_gentauvisible=tlv_gentau -tlv_gentaunu;
    double respGen   = tlv_gentauvisible.Pt()/tlv_gentau.Pt();
    //std::cout<<" pt_gen "<<tlv_gentauvisible.Pt()<<" eta_gen "<<tlv_gentauvisible.Eta()<<" phi_gen "<<tlv_gentauvisible.Phi()<<endl;
    //    tlv_Gentauvisible.SetPtEtaPhiM((*getGenTaus).at(0).Pt(),
    //			    (*getGenTaus).at(0).Eta(),
    //			    (*getGenTaus).at(0).Phi(),
    //			    (*getGenTaus).at(0).M());
    //tlv_Gentauvisible -= tlv_gentaunu;
    //std::cout<<" pt_gen "<<tlv_Gentauvisible.Pt()<<" eta_gen "<<tlv_Gentauvisible.Eta()<<" phi_gen "<<tlv_Gentauvisible.Phi()<<endl;
    genPt=tlv_gentau.Pt();
    genEta=tlv_gentau.Eta();
    genPhi=tlv_gentau.Phi();
    if(genPt>=20 && genPt<30)
      n_20_30++;
    else if(genPt>=30 && genPt<50)
      n_30_50++;
    else if(genPt>=50 && genPt<100)
      n_50_100++;
    else
      n_Above_100++;

    if(genPt<50)
      dRmatch=0.4;
    //std::cout<<" genPt "<<genPt<<endl;
    //std::cout<<" genEta "<<genEta<<endl;
    //if(slimJets.size()==0)
    // NoslimJet++;

    	// Loop over jets for matching
	for(unsigned short jdx = 0; jdx < slimJets.size(); jdx++){
	  tlv_slimjet.SetPtEtaPhiM(slimJets.at(jdx).Pt(),
				   slimJets.at(jdx).Eta(),
				   slimJets.at(jdx).Phi(),
				   slimJets.at(jdx).M());
	  dR        = tlv_gentauvisible.DeltaR(tlv_slimjet);
	  dR_gen    = tlv_gentau.DeltaR(tlv_slimjet);
	  //std::cout<<" dR "<<dR<<endl;
	  double resp      = tlv_slimjet.Pt()/tlv_gentau.Pt();
	  if (fabs(genEta)<2.1 && dR<dRmatch){
	    if (dR<dRmin){
	      jmatch=(int)jdx;
	      dRmin=dR;
	    }
	  }
	  if (fabs(genEta)<2.1 && dR_gen<0.4){
	    if (dR_gen<dRmin_gen){
	      jmatchGen=(int)jdx;
	      dRmin_gen=dR_gen;
	    }
	  }

	} // jet loop
	if(fabs(genEta)>2.1)
	  Eta_Gt_2Pt1++;
	//if(jmatch==-1 && fabs(genEta)<2.1 && dR<dRmatch)
	//std::cout<<" genEta "<<genEta<<" dR "<<dR<<endl;
	if(jmatch==-1 && fabs(genEta)<2.1){
	  NoMatch_Pt_4++;
	  if(slimJets.size()==0){
	    NoslimJet++;
	    int findYBin=int(fabs(genEta)/0.1)+1;
	    if (genPt>=20.&&genPt<30.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_0");
	      int findXBin=int(genPt-20.)+1;
	      hTauResp_0->Fill(0.,h->GetBinContent(findXBin,findYBin));
	      hGenPt_0->Fill(genPt,h->GetBinContent(findXBin,findYBin));
	      hTauRespGen_0->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	    else if (genPt>=30.&&genPt<50.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_1");
	      int findXBin=int(genPt-30.)+1;
	      hTauResp_1->Fill(0.,h->GetBinContent(findXBin,findYBin));
	      hGenPt_1->Fill(genPt,h->GetBinContent(findXBin,findYBin));	
	      hTauRespGen_1->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	    else if (genPt>=50.&&genPt<100.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_2");
	      int findXBin=int(genPt-50.)+1;
	      hTauResp_2->Fill(0.,h->GetBinContent(findXBin,findYBin));
	      hGenPt_2->Fill(genPt,h->GetBinContent(findXBin,findYBin));
	      hTauRespGen_2->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	    else if(genPt>=100.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_3");
	      int findXBin=int(genPt-100.)+1;
	      if(findXBin>70) findXBin=70;
	      hTauResp_3->Fill(0.,h->GetBinContent(findXBin,findYBin));
	      hGenPt_3->Fill(genPt,h->GetBinContent(findXBin,findYBin));
	      hTauRespGen_3->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	  }
	  else{	
	    if(dRmin>dRmatch)
	      NoMatch_Pt_4_AbovedRcut++;
	    else{
	      std::cout<<" slimJet_size "<<slimJets.size()<<" jmatch "<<jmatch<<" dR "<<dR<<" dRmin "<<dRmin<<" genPt "<<genPt<<" visible_Pt "<<tlv_gentauvisible.Pt()<<" ratio "<<tlv_gentauvisible.Pt()/genPt<<endl;
	      if(tlv_gentauvisible.Pt()<10)
		NoMatch_Pt_4_AbovedRcut_VisGenJetBelow10++;
	    }
	  }
	}
	if(jmatchGen==-1)
	  noGenMatch++;
	if (jmatch!=-1){
	  MatchFound++;
	  tlv_slimjet.SetPtEtaPhiM((slimJets).at(jmatch).Pt(),
				     (slimJets).at(jmatch).Eta(),
				     (slimJets).at(jmatch).Phi(),
				     (slimJets).at(jmatch).M());
	    double dR        = tlv_gentau.DeltaR(tlv_slimjet);
	    double resp      = tlv_slimjet.Pt()/tlv_gentau.Pt();
	    hGenPt->Fill(genPt);
	    double tauJetPhi=tlv_slimjet.Phi();
	    double tauJetPt=tlv_slimjet.Pt();
	    if(TVector2::Phi_mpi_pi( genPhi - tauJetPhi) < -1.0)
	      tau_GenJetPhi->Fill(tauJetPt / genPt ,-1.0);
	    else if(TVector2::Phi_mpi_pi( genPhi - tauJetPhi) > 1.0)
	      tau_GenJetPhi->Fill(tauJetPt / genPt ,1.0);
	    else
	      tau_GenJetPhi->Fill(tauJetPt / genPt ,TVector2::Phi_mpi_pi( genPhi - tauJetPhi));

	    //
	    // Tau template
	    int findYBin=int(fabs(genEta)/0.1)+1;
	    if (abs(genEta)<2.1 && genPt>=20.&&genPt<30.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_0");
	      int findXBin=int(genPt-20.)+1;
	      if (nEvents%10000 == 0)
		std::cout<<" pt "<<genPt<<" findXBin "<<findXBin<<" eta "<<genEta<<" findYBin "<<findYBin<<endl;
	      hTauResp_0->Fill(resp,h->GetBinContent(findXBin,findYBin));
	      hGenPt_0->Fill(genPt,h->GetBinContent(findXBin,findYBin));
	      hTauRespGen_0->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	    else if (abs(genEta)<2.1 && genPt>=30.&&genPt<50.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_1");
	      int findXBin=int(genPt-30.)+1;
	      if (nEvents%10000 == 0)
		std::cout<<" pt "<<genPt<<" findXBin "<<findXBin<<" eta "<<genEta<<" findYBin "<<findYBin<<endl;
	      hTauResp_1->Fill(resp,h->GetBinContent(findXBin,findYBin));
	      hGenPt_1->Fill(genPt,h->GetBinContent(findXBin,findYBin));
	      hTauRespGen_1->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	    else if (abs(genEta)<2.1 && genPt>=50.&&genPt<100.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_2");
	      int findXBin=int(genPt-50.)+1;
	      if (nEvents%10000 == 0)
		std::cout<<" pt "<<genPt<<" findXBin "<<findXBin<<" eta "<<genEta<<" findYBin "<<findYBin<<endl;
	      hTauResp_2->Fill(resp,h->GetBinContent(findXBin,findYBin));
	      hGenPt_2->Fill(genPt,h->GetBinContent(findXBin,findYBin));
	      hTauRespGen_2->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	    else if (abs(genEta)<2.1 && genPt>=100.){
	      TH2F * h=(TH2F *)fWeights->FindObjectAny("ReweightPtEta_3");
	      int findXBin=int(genPt-100.)+1;
	      if(findXBin>70) findXBin=70;
	      if (nEvents%10000 == 0)
		std::cout<<" pt "<<genPt<<" findXBin "<<findXBin<<" eta "<<genEta<<" findYBin "<<findYBin<<endl;
	      hTauResp_3->Fill(resp,h->GetBinContent(findXBin,findYBin));
	      hGenPt_3->Fill(genPt,h->GetBinContent(findXBin,findYBin));
	      hTauRespGen_3->Fill(respGen,h->GetBinContent(findXBin,findYBin));
	    }
	} //matches jmatch!=-1
	else
	  noMatch++;
  }//matches tReader

  std::cout<<"W_0 "<<hTauResp_0->GetSumOfWeights()<<" W_1 "<<hTauResp_1->GetSumOfWeights()<<" W_2 "<<hTauResp_2->GetSumOfWeights()<<" W_3 "<<hTauResp_3->GetSumOfWeights()<<endl;

  if (hTauResp_0->GetSumOfWeights()) hTauResp_0->Scale(20./hTauResp_0->GetSumOfWeights());
  if (hTauResp_1->GetSumOfWeights()) hTauResp_1->Scale(20./hTauResp_1->GetSumOfWeights());
  if (hTauResp_2->GetSumOfWeights()) hTauResp_2->Scale(20./hTauResp_2->GetSumOfWeights());
  if (hTauResp_3->GetSumOfWeights()) hTauResp_3->Scale(20./hTauResp_3->GetSumOfWeights());
  if (hTauRespGen_0->GetSumOfWeights()) hTauRespGen_0->Scale(20./hTauRespGen_0->GetSumOfWeights());
  if (hTauRespGen_1->GetSumOfWeights()) hTauRespGen_1->Scale(20./hTauRespGen_1->GetSumOfWeights());
  if (hTauRespGen_2->GetSumOfWeights()) hTauRespGen_2->Scale(20./hTauRespGen_2->GetSumOfWeights());
  if (hTauRespGen_3->GetSumOfWeights()) hTauRespGen_3->Scale(20./hTauRespGen_3->GetSumOfWeights());
  if (tau_GenJetPhi->GetSumOfWeights()) tau_GenJetPhi->Scale(273800./tau_GenJetPhi->GetSumOfWeights());
  if(hGenPt_0->GetSumOfWeights()) hGenPt_0->Scale(1./hGenPt_0->GetSumOfWeights());
  if(hGenPt_1->GetSumOfWeights()) hGenPt_1->Scale(1./hGenPt_1->GetSumOfWeights());
  if(hGenPt_2->GetSumOfWeights()) hGenPt_2->Scale(1./hGenPt_2->GetSumOfWeights());
  if(hGenPt_3->GetSumOfWeights()) hGenPt_3->Scale(1./hGenPt_3->GetSumOfWeights());
  if(hGenPt->GetSumOfWeights()) hGenPt->Scale(1./hGenPt->GetSumOfWeights());
  std::cout<<" 20-30 "<<n_20_30<<endl;
  std::cout<<" 30-50 "<<n_30_50<<endl;
  std::cout<<" 50-100 "<<n_50_100<<endl;
  std::cout<<" AboveHundred "<<n_Above_100<<endl;
  std::cout<<" noMatch "<<noMatch<<endl;
  std::cout<<" noGenMatch "<<noGenMatch<<endl;
  std::cout<<" Eta_Gt_2Pt1 "<<Eta_Gt_2Pt1<<endl;
  std::cout<<" hTauResp_0 "<<hTauResp_0->GetSumOfWeights()<<endl;
  std::cout<<" hTauResp_1 "<<hTauResp_1->GetSumOfWeights()<<endl;
  std::cout<<" hTauResp_2 "<<hTauResp_2->GetSumOfWeights()<<endl;
  std::cout<<" hTauResp_3 "<<hTauResp_3->GetSumOfWeights()<<endl;
  std::cout<<" NoMatch_Pt_4 "<<NoMatch_Pt_4<<endl;
  std::cout<<" NoMatch_Pt_4_AbovedRcut "<<NoMatch_Pt_4_AbovedRcut<<endl;
  std::cout<<" NoMatch_Pt_4_AbovedRcut_VisGenJetBelow10 "<<NoMatch_Pt_4_AbovedRcut_VisGenJetBelow10<<endl;
  std::cout<<" NoslimJet "<<NoslimJet<<endl;
  std::cout<<" MatchFound "<<MatchFound<<endl;
  //f2->Write();
  TFile* xf = new TFile("hist_taugun_aditee_Reweighted.root","RECREATE");
  hTauResp_0->Write();
  hTauResp_1->Write();
  hTauResp_2->Write();
  hTauResp_3->Write();
  hTauRespGen_0->Write();
  hTauRespGen_1->Write();
  hTauRespGen_2->Write();
  hTauRespGen_3->Write();
  hGenPt_0->Write();
  hGenPt_1->Write();
  hGenPt_2->Write();
  hGenPt_3->Write();
  hGenPt->Write();
  tau_GenJetPhi->Write();
  xf->Close();





}
