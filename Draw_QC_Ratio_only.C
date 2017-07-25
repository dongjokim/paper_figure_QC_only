 // Default Configuration
    int isc = 0; // vm2vn2 = 3,2
    int m=3; int n=2;

const int NSet = 12;// 1data + 3 ampt + 6 vish + 2 ekrt
int gFillStyle = 3002;
int gOMarker[NSet] = {24, 
					kFullCircle, kFullCircle, kFullCircle,
					kOpenCircle, kOpenCircle, kOpenSquare, kOpenSquare, kOpenDiamond, kOpenDiamond,
					24, 24};
int gColor[NSet] = { kBlack, 
					kOrange, kOrange+2, kOrange+4,
					kRed, kRed, kBlue, kBlue, kGreen+2, kGreen+2,
					kBlue, kBlack};
				
double x_min = 0;
double x_max = 52;
double y_min = -1 * 1e-5 ;
double y_max = 1 * 1e-5;
double y_min_ratio = -10;
double y_max_ratio = 10;

TString strSaveFile = "figs/SC";

TString strSCType[5] = { "3223", "4224", "5225", "5335", "4334" };
TString strSCShortName[5] = {"SC32", "SC42", "SC52", "SC53", "SC43"};

TString datainfo[NSet][3] = {
	"results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root", Form("gr_SC_with_QC_%s", strSCType[isc].Data()), "Data",

	"results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0250.root", Form("gr_SC_with_QC_%s", strSCType[isc].Data()), "AMPT Default", 
	"results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0250.root", Form("gr_SC_with_QC_%s", strSCType[isc].Data()), "AMPT ST On", 
	"results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0250.root", Form("gr_SC_with_QC_%s", strSCType[isc].Data()), "AMPT ST On/ RC Off", 

	"VISH_simdata/AMPT/resultSC.root", Form("%s_%d", strSCShortName[isc].Data(), 0), "VISH2+1 AMPT eta/s=0.08", 
	"VISH_simdata/AMPT/resultSC.root", Form("%s_%d", strSCShortName[isc].Data(), 1), "VISH2+1 AMPT eta/s=0.16", 
	"VISH_simdata/KLN/resultSC.root", Form("%s_%d", strSCShortName[isc].Data(), 0), "VISH2+1 KLN eta/s=0.08",
	"VISH_simdata/KLN/resultSC.root", Form("%s_%d", strSCShortName[isc].Data(), 1), "VISH2+1 KLN eta/s=0.2",
	"VISH_simdata/Glb/resultSC.root", Form("%s_%d", strSCShortName[isc].Data(), 0), "VISH2+1 Glb eta/s=0.08",
	"VISH_simdata/Glb/resultSC.root", Form("%s_%d", strSCShortName[isc].Data(), 1), "VISH2+1 Glb eta/s=0.2",

	"Harris_results/EKRT_eta_020_pt_NSC.root", Form("gr_harri_SC_%d_pt_1", isc), "EKRT param0 eta/s=0.20",
	"Harris_results/EKRT_eta_par1_pt_NSC.root", Form("gr_harri_SC_%d_pt_1", isc), "EKRT param1"
};

TFile *fin[NSet];
TGraphErrors *gr_SC[NSet];
TGraphErrors *gr_SC_ratio[NSet]; // ratio to 1st graph 
TF1 *fFitftn;

//=============== Main Code =========
void Draw_QC_Ratio_only(){
	cout << "start macro" << endl;
	LoadSCResults();
	fFitftn = new TF1("fFitftn", "pol0");

	TCanvas *c1 = new TCanvas("c1","c1", 600, 700);
	c1->Draw();
	TPad *upPad = new TPad("up","upper pad", 0, 0.3, 1, 1);        
	TPad *lowPad = new TPad("low","lower pad", 0, 0, 1, 0.3);      

	upPad->Draw();
	lowPad->Draw();

	TLine *line_0= new TLine( x_min, 0, x_max, 0);
	TLine *line_1= new TLine( x_min, 1, x_max, 1);
	upPad->cd();
	upPad->SetTopMargin(0.05);
	upPad->SetBottomMargin(0);
	TH2D *href = new TH2D("href", "", 100, x_min, x_max, 100,  y_min, y_max);
	href->GetYaxis()->SetTitle("SC(m,n) ");
	href->GetYaxis()->SetTitleSize(0.04);
	href->GetYaxis()->SetTitleOffset(1.144);
	href->GetYaxis()->SetLabelSize(0.035);
	//	TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
	href->SetStats(0);
	href->Draw();
	line_0->Draw("same l");

	lowPad->cd();
	lowPad->SetTopMargin(0);
	lowPad->SetBottomMargin(0.2);
	TH2D *href_ratio = new TH2D("href_ratio", "" , 100, x_min, x_max, 100, y_min_ratio, y_max_ratio);
	href_ratio->GetYaxis()->SetTitle("Ratio ");
	href_ratio->GetYaxis()->CenterTitle(1);
	href_ratio->GetXaxis()->SetTitle("Centrality percentile");
	href_ratio->GetYaxis()->SetTitleSize(0.09);
	href_ratio->GetXaxis()->SetTitleSize(0.08);
	href_ratio->GetYaxis()->SetTitleOffset(0.45);
	href_ratio->GetXaxis()->SetTitleOffset(0.95);
	href_ratio->GetYaxis()->SetLabelSize(0.075);
	href_ratio->GetXaxis()->SetLabelSize(0.08);
	href_ratio->SetStats(0);
	href_ratio->Draw();
	line_1->Draw("same l");
	//
	//Fill Graph
 
	upPad->cd();
	TLegend *leg = new  TLegend(0.2, 0.55, 0.55, 0.88, "", "brNDC");
	leg->SetFillStyle(0); 
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);

	for(int i=0; i<NSet; i++){
		gr_SC[i]->Draw("same pl");
		leg->AddEntry( gr_SC[i], datainfo[i][2].Data(), "pl");
	}
	leg->Draw();

	lowPad->cd();
	for(int i=1; i<NSet; i++){
			int ref= 0;
			gr_SC_ratio[i] = CalculateRatio( gr_SC[i] ,  gr_SC[ref] , i-2.5); // gr2 / gr1
			gr_SC_ratio[i]->SetMarkerColor( gColor[i] );
			gr_SC_ratio[i]->SetMarkerStyle( gOMarker[i] );
			gr_SC_ratio[i]->SetMarkerSize( 1.1 );
			gr_SC_ratio[i]->SetLineColor( gColor[i] );
			gr_SC_ratio[i]->Draw("same p");
		
			gr_SC_ratio[i]->Fit("fFitftn", "n");

	}	


	TLegend *leg_low = new  TLegend(0.35, 0.7, 0.65, 0.9, "", "brNDC");
	leg_low->SetFillStyle(0); 
	leg_low->SetBorderSize(0);
	leg_low->SetTextSize(0.08);
	leg_low->Draw();


//	c1->SaveAs( strSaveFile.Data() );


//DJ's ask only ratio in 1 canvas

    TCanvas *c1000 = new TCanvas("c1000", "", 1000, 600);
    c1000->Draw();
    TH2D *href = new TH2D("href1000", Form("SC(%d,%d)", m, n), 100, 0, 52, 100, -3, 3);
    href->SetStats(0);
    href->GetYaxis()->SetTitle("(Theory-Data)/Data");
    href->GetXaxis()->SetTitle("Centrality percentile");
    href->Draw();
    line_0->Draw("same");

	for(int i=1; i<4; i++){ //AMPT
		gr_SC_ratio[i]->SetLineWidth(2);
		gr_SC_ratio[i]->Draw("same pl");
	}
	for(int i=4; i<10; i++){
		gr_SC_ratio[i]->SetLineWidth(2.5);
		if(i%2==1)gr_SC_ratio[i]->SetLineStyle(7);
		gr_SC_ratio[i]->Draw("same pl");

	}
	for(int i=10; i<NSet; i++){
		gr_SC_ratio[i]->SetLineWidth(3);
		gr_SC_ratio[i]->Draw("same l");
	}
	leg->Draw();

	c1000->SaveAs(Form("SC%d%d_ratio_only.eps",m,n));



}



// Load SC results //
void LoadSCResults(){
		cout << "read data" << endl;
		for(int i=0; i<NSet; i++){
				fin[i] = new TFile( datainfo[i][0].Data(), "read" );
				gr_SC[i] = (TGraphErrors*)fin[i]->Get( datainfo[i][1].Data() );
				gr_SC[i]->SetMarkerStyle( gOMarker[i] );
				gr_SC[i]->SetMarkerColor( gColor[i] );
				gr_SC[i]->SetLineColor( gColor[i] );
		}
		cout << "read done" << endl;
}


// CalculateRatio 
TGraphErrors *CalculateRatio( TGraphErrors* gr1, TGraphErrors* gr2, double xshift){
		int NPoint = gr1->GetN();
		TGraphErrors *gr_ratio = new TGraphErrors( NPoint);
		TGraph ger( gr2->GetN(), gr2->GetX(), gr2->GetEY() ); // << Err estimation of gr2
		for(int i=0; i<NPoint; i++){
				double x = gr1->GetX()[i];
				double y1 = gr1->GetY()[i];
				double ey1 = gr1->GetEY()[i];  // << estimation of gr2's y value for x1
				double y2 = gr2->Eval(x);
				double ey2 = ger.Eval(x);
				//double ratio = TMath::Abs( y1 / y2 );
				double ratio = (y1-y2)/y2;
				gr_ratio->SetPoint( i, x+xshift, ratio);
				gr_ratio->SetPointError( i, 0, ratio * TMath::Sqrt( ey1*ey1/y1/y1 + ey2*ey2/y2/y2 ));

		}
		return gr_ratio;
}
















