#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>

void compareResponse(char* WJetTTbarMC, char* Wgun, char* histname, bool logy, bool logx, bool overlay,bool normalized){
  gStyle->SetOptStat(111111111);
  gStyle->SetOptTitle(0);
    
  int col1 = kRed;
  int col2 = kBlue;
  int i=0;
    
  char hname[500], htit[500];
  char WJetTTbar[500],WGun[500];
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TFile *_file1 = TFile::Open(Wgun);
    
  //  _file0->cd();
  //TDirectory *demo1    = (TDirectory*)_file0->FindObjectAny("demo");
  //_file1->cd();
  //TDirectory *demo2    = (TDirectory*)_file1->FindObjectAny("demo");
    
    
  //sprintf(hname, "%s", histname); //string "hname" is set to the content of histname 
    
  //  sprintf(htit, "WJetTTbarMC vs Wgun");
  bool Pt0=strncmp(histname,"hGenPt_0",8)==0;
  bool Pt1=strncmp(histname,"hGenPt_1",8)==0;
  bool Pt2=strncmp(histname,"hGenPt_2",8)==0;
  bool Pt3=strncmp(histname,"hGenPt_3",8)==0;
  bool PtEta0=strncmp(histname,"hGenPtEta_0",11)==0;
  bool PtEta1=strncmp(histname,"hGenPtEta_1",11)==0;
  bool PtEta2=strncmp(histname,"hGenPtEta_2",11)==0;
  bool PtEta3=strncmp(histname,"hGenPtEta_3",11)==0;
    
if(Pt0){    
    sprintf(hname, "Reweight_0");
    sprintf(WJetTTbar,"WJetTTbar_0");
    sprintf(WGun,"WGun_0");
  }
  else if(Pt1){    
    sprintf(hname, "Reweight_1");
    sprintf(WJetTTbar,"WJetTTbar_1");
    sprintf(WGun,"WGun_1");
  } 
  else if(Pt2){    
    sprintf(hname, "Reweight_2");
    sprintf(WJetTTbar,"WJetTTbar_2");
    sprintf(WGun,"WGun_2");
  }
  else if(Pt3){    
    sprintf(hname, "Reweight_3");
    sprintf(WJetTTbar,"WJetTTbar_3");
    sprintf(WGun,"WGun_3");
  }
  else if(PtEta0){    
    sprintf(hname, "ReweightPtEta_0");
    sprintf(WJetTTbar,"WJetTTbarPtEta_0");
    sprintf(WGun,"WGunPtEta_0");
  }
  else if(PtEta1){    
    sprintf(hname, "ReweightPtEta_1");
    sprintf(WJetTTbar,"WJetTTbarPtEta_1");
    sprintf(WGun,"WGunPtEta_1");
  }
  else if(PtEta2){    
    sprintf(hname, "ReweightPtEta_2");
    sprintf(WJetTTbar,"WJetTTbarPtEta_2");
    sprintf(WGun,"WGunPtEta_2");
  }
  else if(PtEta3){    
    sprintf(hname, "ReweightPtEta_3");
    sprintf(WJetTTbar,"WJetTTbarPtEta_3");
    sprintf(WGun,"WGunPtEta_3");
  }
  else{   
    sprintf(hname, "Reweight");   
    sprintf(WJetTTbar,"WJetTTbar");
    sprintf(WGun,"WGun");
  }
  
    
  int Nbins,Nbinsx,Nbinsy;    
  TH1F *h1,*h2,*hDiff;
  TH2F *H1,*H2,*HDiff;
  if(Pt0 || Pt1 || Pt2 || Pt3){
    h1 = (TH1F*)_file0->FindObjectAny(histname);
    h2 = (TH1F*)_file1->FindObjectAny(histname);
    hDiff = (TH1F*) h1->Clone("hDiff");
    h1->SetName(WJetTTbar);
    h2->SetName(WGun);
  }
  if(PtEta0 || PtEta1 || PtEta2 || PtEta3){
    H1 = (TH2F*)_file0->FindObjectAny(histname);
    H2 = (TH2F*)_file1->FindObjectAny(histname);
    HDiff = (TH2F*) H1->Clone("HDiff");
    H1->SetName(WJetTTbar);
    H2->SetName(WGun);
  }
  std::cout<<" **Read histograms**"<<endl; 
  //h2->GetXaxis()->SetTitle("pT(visible)/pT(genTau)");
  if(Pt0 || Pt1 || Pt2){ 
    hDiff->Divide(h1,h2,1,1);
    hDiff->SetName(hname);
    Nbins=h2->GetXaxis()->GetNbins();
    for(int i=1;i<=Nbins;i++){
      //std::cout<<" i "<<i <<" h1_i "<<h1->GetBinContent(i)<<" h2_i "<<h2->GetBinContent(i)<<" h1_e "<<h1->GetBinError(i)<<" h2_e "<<h2->GetBinError(i)<<" hDiff_i "<<hDiff->GetBinContent(i)<<" hDiff_e "<<hDiff->GetBinError(i)<<endl;
    }
  }
  else if(PtEta0 || PtEta1 || PtEta2){ 
    HDiff->Divide(H1,H2,1,1);
    HDiff->SetName(hname);
    Nbinsx=H2->GetXaxis()->GetNbins();
    Nbinsy=H2->GetYaxis()->GetNbins();
    for(int i=1;i<=Nbinsx;i++){
      for(int j=1;j<=Nbinsy;j++){
	//std::cout<<" i "<<i <<" j "<<j<<" h1_ij "<<H1->GetBinContent(i,j)<<" h2_ij "<<H2->GetBinContent(i,j)<<" h1_e "<<H1->GetBinError(i,j)<<" h2_e "<<H2->GetBinError(i,j)<<" hDiff_ij "<<HDiff->GetBinContent(i,j)<<" hDiff_e "<<HDiff->GetBinError(i,j)<<endl;
      }
    }
  }
  else if(Pt3){
    std::cout<< "histname is hGenPt_3"<<endl; 
    //TH1F *hDiff = (TH1F*) h1->Clone("hDiff"); 
    TH1F *h2New = new TH1F("Restricth2NBins","Restricth2NBins",70,100,170);
    Nbins=h2New->GetXaxis()->GetNbins();
    for(int i=1;i<=Nbins;i++){
      h2New->SetBinContent(i,h2->GetBinContent(i));
      h2New->SetBinError(i,h2->GetBinError(i));
      //std::cout<<" i "<<i <<" h2_i "<<h2->GetBinContent(i)<<" h2New_i "<<h2New->GetBinContent(i)<<" h2_e "<<h2->GetBinError(i)<<" h2New_e "<<h2New->GetBinError(i)<<endl;
    }
    TH1F *h1New = new TH1F("Restricth1NBins","Restricth1NBins",70,100,170);
    Nbins=h1New->GetXaxis()->GetNbins();
    for(int i=1;i<=Nbins;i++){
      h1New->SetBinContent(i,h1->GetBinContent(i));
      h1New->SetBinError(i,h1->GetBinError(i));
      //std::cout<<" i "<<i <<" h1_i "<<h1->GetBinContent(i)<<" h1New_i "<<h1New->GetBinContent(i)<<" h1_e "<<h1->GetBinError(i)<<" h1New_e "<<h1New->GetBinError(i)<<endl;
    }
    hDiff = (TH1F*) h1New->Clone("hDiff");
    hDiff->Divide(h1New,h2New,1,1);
    hDiff->SetName(hname);
    for(int i=1;i<=Nbins;i++){
      //std::cout<<" i "<<i <<" h1_i "<<h1->GetBinContent(i)<<" h2_i "<<h2->GetBinContent(i)<<" h1_e "<<h1->GetBinError(i)<<" h2_e "<<h2->GetBinError(i)<<" hDiff_i "<<hDiff->GetBinContent(i)<<" hDiff_e "<<hDiff->GetBinError(i)<<endl;
    }
  }
  else if(PtEta3){
    //TH1F *hDiff = (TH1F*) h1->Clone("hDiff"); 
    std::cout<< "histname is hGenPtEta_3"<<endl; 

    TH2F *h2New = new TH2F("Restricth2NBins","Restricth2NBins",70,100,170,24,0,2.4);
    Nbinsx=h2New->GetXaxis()->GetNbins();
    Nbinsy=h2New->GetYaxis()->GetNbins();
    for(int i=1;i<=Nbinsx;i++){
      for(int j=1;j<=Nbinsy;j++){
	h2New->SetBinContent(i,j,H2->GetBinContent(i,j));
	h2New->SetBinError(i,j,H2->GetBinError(i,j));
	//	std::cout<<" i "<<i <<" j "<<j<<" h2_ij "<<H2->GetBinContent(i,j)<<" h2New_ij "<<h2New->GetBinContent(i,j)<<" h2_e "<<H2->GetBinError(i,j)<<" h2New_e "<<h2New->GetBinError(i,j)<<endl;
      }
    }
    TH2F *h1New = new TH2F("Restricth1NBins","Restricth1NBins",70,100,170,24,0,2.4);
    Nbinsx=h1New->GetXaxis()->GetNbins();
    Nbinsy=h1New->GetYaxis()->GetNbins();
    for(int i=1;i<=Nbinsx;i++){
      for(int j=1;j<=Nbinsy;j++){
	h1New->SetBinContent(i,j,H1->GetBinContent(i,j));
	h1New->SetBinError(i,j,H1->GetBinError(i,j));
	//std::cout<<" i "<<i <<" j "<<j<<" h1_ij "<<H1->GetBinContent(i,j)<<" h1New_ij "<<h1New->GetBinContent(i,j)<<" h1_e "<<H1->GetBinError(i,j)<<" h1New_e "<<h1New->GetBinError(i,j)<<endl;
      }
    }
    HDiff = (TH2F*) h1New->Clone("HDiff");
    HDiff->Divide(h1New,h2New,1,1);
    HDiff->SetName(hname);
    for(int i=1;i<=Nbinsx;i++){
      for(int j=1;j<=Nbinsy;j++){
	//std::cout<<" i "<<i <<" j "<<j<<" h1_ij "<<H1->GetBinContent(i,j)<<" h2_ij "<<H2->GetBinContent(i,j)<<" h1_e "<<H1->GetBinError(i,j)<<" h2_e "<<H2->GetBinError(i,j)<<" hDiff_ij "<<HDiff->GetBinContent(i,j)<<" hDiff_e "<<HDiff->GetBinError(i,j)<<endl;
      }
    }
  }
  TFile* xf = new TFile("hist_WgunTemplateReweight.root","UPDATE");
  if(Pt0 || Pt1 || Pt2 || Pt3){
  h1->Write();
  h2->Write();
  hDiff->Write();
  }
  if(PtEta0 || PtEta1 || PtEta2 || PtEta3){
  H1->Write();
  H2->Write();
  HDiff->Write();
  }
  xf->Close();
  
  
}   
void WgunTemplateReweighting() {
  
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPt_0",0,0,1,1);
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPt_1",0,0,1,1);
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPt_2",0,0,1,1);
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPt_3",0,0,1,1);
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPtEta_0",0,0,1,1);
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPtEta_1",0,0,1,1);
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPtEta_2",0,0,1,1);
  compareResponse("ARElog102_HadTau_TauResponseTemplates_stacked.root","hist_taugun_aditee_LPC_Dec27.root", "hGenPtEta_3",0,0,1,1);
//  
}
