// chisqared test results as a function of oberables, fist index 0 SC, 1 NSC
enum { kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};
enum { kEKRT, kVISH, kAMPT, kNmodel};
enum {kAMPT13f3a, kAMPT13f3b, kAMPT13f3c, kNAMPT};
enum {kV_AMPT, kV_KLN, kV_Glb, kNVISH};
enum {kV_smallviso, kV_largevisco, kVNvisco};
int gCMarker[6] = {kFullCircle, kFullSquare, kFullDiamond, kFullStar, 34, 22};
int gOMarker[6] = {kOpenCircle, kOpenSquare, kOpenDiamond, kOpenStar, 28, 26};

int gColor[6] = {kBlack, kBlue, kRed, kGreen+2, kOrange-1,kYellow-6};
int gFillColor[3] = { kGreen-3, kCyan+2, kYellow-6};

TGraphErrors *gr_VISH_chisq[2][kNVISH][kVNvisco];
TGraphErrors *gr_EKRT_chisq[2][2];
TGraphErrors *gr_AMPT_chisq[2][kNAMPT];

TString strVISHconf[kNVISH][kVNvisco] = {
	"AMPT, #eta/s=0.08",
	"AMPT, #eta/s=0.16",
	"MC-KLN, #eta/s=0.08",
	"MC-KLN, #eta/s=0.2",
	"MC-Glauber, #eta/s=0.08",
	"MC-Glauber, #eta/s=0.2"	
};

int sc_number[5][2] = { 3,2,
	4,2,
	5,2,
	5,3,
	4,3};

TString strSCType[kNSC] = { 
	"(3,2)","(4,2)","(5,2)","(5,3)","(4,3)"}; 

TString strAMPTName[kNAMPT] ={
	"string melting w/o hadronic rescattering",
	"default",
	"string melting"
}

TString strModel[3] = { "EKRT","VISH","AMPT"};

void draw_chiq(){
// open the resuts 
	TFile *fin = TFile::Open("chisquared_results.root");

	for(int iset=0;iset<2;iset++) {
		gr_EKRT_chisq[0][iset] = (TGraphErrors*)fin->Get(Form("gr_EKRT_SC_parm%02d",iset));
		gr_EKRT_chisq[1][iset] = (TGraphErrors*)fin->Get(Form("gr_EKRT_NSC_parm%02d",iset));
	}

	for(int iset=0; iset<kNVISH; iset++){
        for(int ieta=0; ieta<kVNvisco; ieta++){
			gr_VISH_chisq[0][iset][ieta] = (TGraphErrors*)fin->Get(Form("gr_VISH_SC_%02d%02d_chisq",iset,ieta));
			gr_VISH_chisq[1][iset][ieta] = (TGraphErrors*)fin->Get(Form("gr_VISH_NSC_%02d%02d_chisq",iset,ieta));
		}
	}
	for(int iset=0; iset<kNAMPT; iset++){
		gr_AMPT_chisq[0][iset] = (TGraphErrors*)fin->Get(Form("gr_AMPT_SC_%2d_chisq",iset));
		gr_AMPT_chisq[1][iset] = (TGraphErrors*)fin->Get(Form("gr_AMPT_NSC_%2d_chisq",iset));
	}

	double sc=1.0, sdx=400, sdy=400;
	double ly=5.1e-1, hy=1.1e6;
	int logy=1;

	int iCan = 1;
	TLatex latexPad;
	latexPad.SetTextSize(0.04);
	
	//Best fit
	mc(iCan++,sc,sdx); //===================================
    // scale sc and sdx could be omitted
	mpad->SetLogy(logy);
    mpad->SetLeftMargin(0.2);
    gStyle->SetOptStat(0); gStyle->SetOptTitle(0);

    hfr0 = new TH2F("hfr0", " ", kNSC, -0.5, kNSC-0.5, 10, ly, hy);
    hset( *hfr0, "", "#chi^{2}",0.9,1.4, 0.05,0.07, 0.01,0.001, 0.09,0.06, 510,510);
    SetGraphBinLabel(hfr0, strSCType);
	hfr0->Draw();
    
    leg = new TLegend(0.25,0.70,0.5,0.93,NULL,"brNDC");
    leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.04);
    leg->AddEntry((TObject*)NULL,"EKRT+Viscous Hydrodynamics","");
    for(int iset=0;iset<2;iset++) {
    	gr_EKRT_chisq[0][iset]->SetMarkerStyle(gCMarker[iset]);
    	gr_EKRT_chisq[0][iset]->SetMarkerColor(gColor[iset]);
    	gr_EKRT_chisq[0][iset]->SetLineColor(gColor[iset]);
		gr_EKRT_chisq[0][iset]->Draw("lp");
		gr_EKRT_chisq[1][iset]->SetMarkerStyle(gOMarker[iset]);
		gr_EKRT_chisq[1][iset]->SetMarkerColor(gColor[iset]);
    	gr_EKRT_chisq[1][iset]->SetLineColor(gColor[iset]);
		gr_EKRT_chisq[1][iset]->SetLineStyle(2);
		gr_EKRT_chisq[1][iset]->Draw("lp");
		leg->AddEntry(gr_EKRT_chisq[0][iset],Form("%s",gr_EKRT_chisq[0][iset]->GetTitle()),"lp");
	}
    int count = 0;
    // AMPT eta/s =0.08
    int iset=0,ieta=0;
    gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gCMarker[2]);
    gr_VISH_chisq[0][iset][ieta]->SetMarkerColor(gColor[2]);
    gr_VISH_chisq[0][iset][ieta]->SetLineColor(gColor[2]);
	gr_VISH_chisq[0][iset][ieta]->Draw("lp");
	leg->AddEntry(gr_VISH_chisq[0][iset][ieta],Form("VISH2+1, %s",gr_VISH_chisq[0][iset][ieta]->GetTitle()),"lp");

	gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gOMarker[2]);
	gr_VISH_chisq[1][iset][ieta]->SetMarkerColor(gColor[2]);
	gr_VISH_chisq[1][iset][ieta]->SetLineColor(gColor[2]);
	gr_VISH_chisq[1][iset][ieta]->SetLineStyle(2);
	gr_VISH_chisq[1][iset][ieta]->Draw("lp");
	

	
	gr_AMPT_chisq[0][1]->SetMarkerStyle(gCMarker[3]);
	gr_AMPT_chisq[0][1]->SetMarkerColor(gColor[3]);
	gr_AMPT_chisq[0][1]->SetLineColor(gColor[3]);
	gr_AMPT_chisq[0][1]->Draw("lp");
	leg->AddEntry(gr_AMPT_chisq[0][1],Form("AMPT, %s",gr_AMPT_chisq[0][1]->GetTitle()),"lp");
	gr_AMPT_chisq[1][1]->SetMarkerStyle(gOMarker[3]);
	gr_AMPT_chisq[1][1]->SetMarkerColor(gColor[3]);
	gr_AMPT_chisq[1][1]->SetLineColor(gColor[3]);
	gr_AMPT_chisq[1][1]->SetLineStyle(2);
	gr_AMPT_chisq[1][1]->Draw("lp");
	leg->Draw();
	latexPad.DrawLatexNDC( 0.48, 0.48 , "SC(m,n)");
	latexPad.DrawLatexNDC( 0.48, 0.30 , "NSC(m,n)");

	gPad->GetCanvas()->Update();
	gPad->GetCanvas()->SaveAs("figs/chisq_bestfits.eps");
//EKRT
	mc(iCan++,sc,sdx); //===================================
    // scale sc and sdx could be omitted
	mpad->SetLogy(1);
    mpad->SetLeftMargin(0.2);
    gStyle->SetOptStat(0); gStyle->SetOptTitle(0);
	hfr0->Draw();
	leg = new TLegend(0.25,0.74,0.5,0.93,NULL,"brNDC");
    leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.04);
    leg->AddEntry((TObject*)NULL,"EKRT+Viscous Hydrodynamics","");
    for(int iset=0;iset<2;iset++) {
    	gr_EKRT_chisq[0][iset]->SetMarkerStyle(gCMarker[iset]);
		gr_EKRT_chisq[0][iset]->Draw("lp");
		gr_EKRT_chisq[1][iset]->SetMarkerStyle(gOMarker[iset]);
		gr_EKRT_chisq[1][iset]->Draw("lp");
		leg->AddEntry(gr_EKRT_chisq[0][iset],gr_EKRT_chisq[0][iset]->GetTitle(),"lp");
	}

	leg->Draw();
	latexPad.DrawLatexNDC( 0.48, 0.48 , "SC(m,n)");
	latexPad.DrawLatexNDC( 0.48, 0.30 , "NSC(m,n)");
	gPad->GetCanvas()->Update();
	gPad->GetCanvas()->SaveAs("figs/chisq_EKRT.eps");
// VISH2+1
	mc(iCan++,sc,sdx); //===================================
    // scale sc and sdx could be omitted
	mpad->SetLogy(1);
    mpad->SetLeftMargin(0.2);
    gStyle->SetOptStat(0); gStyle->SetOptTitle(0);
	hfr0->Draw();
	latexPad.DrawLatexNDC( 0.45, 0.90 , "VISH2+1");
    latexPad.DrawLatexNDC( 0.48, 0.48 , "SC(m,n)");
	latexPad.DrawLatexNDC( 0.48, 0.30 , "NSC(m,n)");

    leg = new TLegend(0.23,0.72,0.5,0.89,NULL,"brNDC");
    leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.03);
    legR = new TLegend(0.60,0.72,0.9,0.89,NULL,"brNDC");
    legR->SetFillStyle(0); legR->SetBorderSize(0); legR->SetTextSize(0.03);
    
    //leg->AddEntry((TObject*)NULL,"VISH2+1","");
    for(int iset=0; iset<kNVISH; iset++){
        for(int ieta=0; ieta<kVNvisco; ieta++){
        	gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gCMarker[iset]);
        	gr_VISH_chisq[0][iset][ieta]->SetMarkerColor(gColor[iset]);
        	gr_VISH_chisq[0][iset][ieta]->SetLineColor(gColor[iset]);
        	gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gCMarker[iset]);
        	gr_VISH_chisq[1][iset][ieta]->SetMarkerColor(gColor[iset]);
        	gr_VISH_chisq[1][iset][ieta]->SetLineColor(gColor[iset]);
        	if(ieta==1) {
        		gr_VISH_chisq[0][iset][ieta]->SetMarkerStyle(gOMarker[iset]);
        		gr_VISH_chisq[1][iset][ieta]->SetMarkerStyle(gOMarker[iset]);
        		gr_VISH_chisq[0][iset][ieta]->SetLineStyle(2); 
        		gr_VISH_chisq[1][iset][ieta]->SetLineStyle(2);
        		legR->AddEntry(gr_VISH_chisq[0][iset][ieta],gr_VISH_chisq[0][iset][ieta]->GetTitle(),"lp");
        	} else {
        		leg->AddEntry(gr_VISH_chisq[0][iset][ieta],gr_VISH_chisq[0][iset][ieta]->GetTitle(),"lp");
			}
			gr_VISH_chisq[0][iset][ieta]->Draw("lp");
			gr_VISH_chisq[1][iset][ieta]->Draw("lp");
		}
	}
	
	leg->Draw();legR->Draw();
	gPad->GetCanvas()->Update();
	gPad->GetCanvas()->SaveAs("figs/chisq_VISH.eps");

//AMPT
	mc(iCan++,sc,sdx); //===================================
    // scale sc and sdx could be omitted
	mpad->SetLogy(1);
    mpad->SetLeftMargin(0.2);
    gStyle->SetOptStat(0); gStyle->SetOptTitle(0);

    
	hfr0->Draw();
    latexPad.DrawLatexNDC( 0.48, 0.48 , "SC(m,n)");
	latexPad.DrawLatexNDC( 0.48, 0.30 , "NSC(m,n)");

    leg = new TLegend(0.25,0.70,0.5,0.93,NULL,"brNDC");
    leg->SetFillStyle(0); leg->SetBorderSize(0); leg->SetTextSize(0.04);
    leg->AddEntry((TObject*)NULL,"AMPT","");
	for(int iset=0; iset<kNAMPT; iset++){
		gr_AMPT_chisq[0][iset]->SetMarkerStyle(gCMarker[iset]);
		gr_AMPT_chisq[0][iset]->SetMarkerColor(gColor[iset]);
		gr_AMPT_chisq[0][iset]->SetLineColor(gColor[iset]);
		gr_AMPT_chisq[0][iset]->Draw("lp");
		gr_AMPT_chisq[1][iset]->SetMarkerStyle(gOMarker[iset]);
		gr_AMPT_chisq[1][iset]->SetMarkerColor(gColor[iset]);
		gr_AMPT_chisq[1][iset]->SetLineColor(gColor[iset]);
		gr_AMPT_chisq[1][iset]->SetLineStyle(2);
		gr_AMPT_chisq[1][iset]->Draw("lp");
		leg->AddEntry(gr_AMPT_chisq[0][iset],gr_AMPT_chisq[0][iset]->GetTitle(),"lp");
	}
	leg->Draw();
	gPad->GetCanvas()->Update();
	gPad->GetCanvas()->SaveAs("figs/chisq_AMPT.eps");
}

void SetGraphBinLabel(TH2F *hid, TString *strArr) {
	for(int i=1;i<= hid->GetNbinsX();i++) {
		cout << strArr[i-1] << endl;
		hid->GetXaxis()->SetBinLabel(i, strArr[i-1]);
	}
}
