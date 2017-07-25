enum {kSC32, kSC42, kSC52, kSC53, kSC43, kNSC};
int gHarriEtaColor[5] = { kBlue, kBlack, kRed, kGreen+2, kOrange-3};


bool Draw_Data[kNSC] = { 1, 1, 1, 1, 1};
bool Draw_old_ekrt[kNSC] = { 0,0, 0, 0, 0 }; // old ekrt have only SC32, SC42
//bool Draw_new_ekrt[kNSC] = { 1,1,1,1,1 };
bool Draw_new_ekrt[kNSC] = { 1,1,1,1,1 };
//bool Draw_AMPT[kNSC] = {0,0,0,0,0};
bool Draw_AMPT[kNSC] = {1,1,1,1,1};
bool Draw_VISH21[kNSC][2] = {1,1,1,1,1 // eta/s =low 
							1,1,1,1,1 }; // eta/s = high



TGraphErrors *gr_C_factor[kNSC];
TGraphErrors *gr_C_factor_syst[kNSC];
TGraphErrors *gr_C_factor_EKRT_old[kNSC][5]; // 5 params
TGraphErrors *gr_C_factor_EKRT[kNSC][2]; // 2 params 
TGraphErrors *gr_C_factor_AMPT[kNSC][3]; // 3 ampt sets
TGraphErrors *gr_C_factor_VISH[kNSC][3][2]; // 3IC settings, 2 eta/s settings


int SC_combination[kNSC][2] ={
				3, 2,
				4, 2,
				5, 2,
				5, 3,
				4, 3
};
TString strSCName[kNSC] = {"3223","4224", "5225", "5335", "4334"};

double systErr[kNSC] = {  // this is not exactly correct since SC and NSC are correlatead
	2*TMath::Sqrt( (0.0143)*(0.0143) + (0.0198)*(0.0198) ), // v2 v3
	2*TMath::Sqrt( (0.0143)*(0.0143) + (0.026)*(0.026) ), // v2 v4
	2*TMath::Sqrt( (0.0143)*(0.0143) + (0.0268)*(0.0268) ),
	2*TMath::Sqrt( (0.0198)*(0.0198) + (0.0268)*(0.0268) ),
	2*TMath::Sqrt( (0.0198)*0.0198 + 0.026*0.026) 
};

void Draw_Norm_Factor_vish(){
				LoadSCResults();
				Load_old_ekrt();
				Load_new_ekrt();
				Load_AMPT();
				Load_VISH();

				double x_min = 0;
				double x_max = 52;
				double y_min = 0.01e-9;
				double y_max = 13e-6;
				double y_min_ratio = -1;
				double y_max_ratio = 0.99;		
	
				if(1){
				int isc=0;
								TCanvas *c1 = new TCanvas("c1","c1", 600, 700);
								c1->Draw();
								TPad *upPad = new TPad("up","upper pad", 0, 0.3, 1, 1);
								TPad *lowPad = new TPad("low","lower pad", 0, 0, 1, 0.3);

								upPad->Draw();
								lowPad->Draw();

								TLine *line_0= new TLine( x_min, 0, x_max, 0);
								TLine *line_1= new TLine( x_min, 0, x_max, 0);
								upPad->cd();
								upPad->SetTopMargin(0.05);
								upPad->SetBottomMargin(0);
								TH2D *href = new TH2D("href", "", 100, x_min, x_max, 100,  y_min+0.1e-7, y_max);
								href->GetYaxis()->SetTitleSize(0.04);
								href->GetYaxis()->SetTitle("#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT");
								href->GetYaxis()->CenterTitle(1);
								href->GetYaxis()->SetTitleOffset(1.144);
								href->GetYaxis()->SetLabelSize(0.035);
								//  TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
								href->SetStats(0);
								href->Draw();
								line_0->Draw("same l");

								lowPad->cd();
								lowPad->SetTopMargin(0);
								lowPad->SetBottomMargin(0.2);
								TH2D *href_ratio = new TH2D("href_ratio", "" , 100, x_min, x_max, 100, y_min_ratio, y_max_ratio);
								href_ratio->GetYaxis()->SetTitle("(Theory-Data)/Data ");
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


								upPad->cd();
								TLegend *leg = new TLegend( 0.12, 0.55, 0.6, 0.90, "#LTv_{3}^{2}#GT#LTv_{2}^{2}#GT", "brNDC");
								leg->SetBorderSize(0);
								leg->SetFillStyle(0);

								leg->AddEntry(gr_C_factor[isc], "Data"  , "p");
//								leg->AddEntry(gr_C_factor_EKRT_old[isc][0], "EKRT+viscous Hydrodynamics parm0 (#eta/s=0.2)", "l");
//								leg->AddEntry(gr_C_factor_EKRT_old[isc][1], "EKRT+viscous Hydrodynamics parm1 (#eta/s(T))", "l");
//								leg->AddEntry(gr_C_factor_EKRT_old[isc][2], "EKRT+viscous Hydrodynamics parm2 (#eta/s(T))", "l");
//								leg->AddEntry(gr_C_factor_EKRT_old[isc][3], "EKRT+viscous Hydrodynamics parm3 (#eta/s(T))", "l");
//								leg->AddEntry(gr_C_factor_EKRT_old[isc][4], "EKRT+viscous Hydrodynamics parm4 (#eta/s(T))", "l");
//								leg->AddEntry(gr_C_factor_EKRT[isc][0], "EKRT(new) param0", "l");
//								leg->AddEntry(gr_C_factor_EKRT[isc][1], "EKRT(new) param1", "l");
//								leg->AddEntry(gr_C_factor_AMPT[isc][0], "AMPT, default", "pl");
//								leg->AddEntry(gr_C_factor_AMPT[isc][1], "AMPT, string melting", "pl");
//								leg->AddEntry(gr_C_factor_AMPT[isc][2], "AMPT, string melting w/o hadronic rescattering", "pl");
								TString strVISH[3][2]={
										"VISH2+1 (AMPT, #eta/s=0.08)",
										"VISH2+1 (AMPT, #eta/s=0.16)",
										"VISH2+1 (MC-KLN, #eta/s=0.08)",
										"VISH2+1 (MC-KLN, #eta/s=0.2)",
										"VISH2+1 (MC-Glauber, #eta/s=0.08)",
										"VISH2+1 (MC-Glauber, #eta/s=0.2)"};
								for(int ic=0; ic<3; ic++){
										for(int ieta=0; ieta<2; ieta++){
												leg->AddEntry(gr_C_factor_VISH[isc][ic][ieta], Form("%s",strVISH[ic][ieta].Data()), "pl");
																					}
								}							
								leg->Draw();	

								//
								upPad->cd();
								if(Draw_Data[isc]==1){
										gr_C_factor_syst[isc]->Draw("same 2");
										gr_C_factor[isc]->Draw("same p");
								};
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){

												gr_C_factor_EKRT_old[isc][ipar]->Draw("same pl");
										}
								};
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												gr_C_factor_EKRT[isc][ipar]->Draw("same pl");
										}
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												gr_C_factor_AMPT[isc][iampt]->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												gr_C_factor_VISH[isc][ic][ieta]->Draw("same pl");
											}
										}
								}

								lowPad->cd();
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){
												CalculateRatio(gr_C_factor_EKRT_old[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												//	CalculateRatio(gr_C_factor_EKRT[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												CalculateRatio(gr_C_factor_AMPT[isc][iampt], gr_C_factor[isc], 0)->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												CalculateRatio(gr_C_factor_VISH[isc][ic][ieta], gr_C_factor[isc], 0)->Draw("same pl");
											}
										}
								}


								// Calculate ratio

				}
				if(1){
				int isc=1;
				y_max = 5e-6;
								TCanvas *c2 = new TCanvas("c2","c2", 600, 700);
								c2->Draw();
								TPad *upPad2 = new TPad("up2","upper pad", 0, 0.3, 1, 1);
								TPad *lowPad2 = new TPad("low2","lower pad", 0, 0, 1, 0.3);

								upPad2->Draw();
								lowPad2->Draw();

								upPad2->cd();
								upPad2->SetTopMargin(0.05);
								upPad2->SetBottomMargin(0);
								TH2D *href2 = new TH2D("href2", "", 100, x_min, x_max, 100,  y_min+0.1e-7, y_max);
								href2->GetYaxis()->SetTitleSize(0.04);
								href2->GetYaxis()->SetTitle("#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT");
								href2->GetYaxis()->CenterTitle(1);
								href2->GetYaxis()->SetTitleOffset(1.144);
								href2->GetYaxis()->SetLabelSize(0.035);
								//  TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
								href2->SetStats(0);
								href2->Draw();
								line_0->Draw("same l");

								lowPad2->cd();
								lowPad2->SetTopMargin(0);
								lowPad2->SetBottomMargin(0.2);
								TH2D *href_ratio2 = new TH2D("href_ratio2", "" , 100, x_min, x_max, 100, y_min_ratio, y_max_ratio);
								href_ratio2->GetYaxis()->SetTitle("(Theory-Data)/Data ");
								href_ratio2->GetYaxis()->CenterTitle(1);
								href_ratio2->GetXaxis()->SetTitle("Centrality percentile");
								href_ratio2->GetYaxis()->SetTitleSize(0.09);
								href_ratio2->GetXaxis()->SetTitleSize(0.08);
								href_ratio2->GetYaxis()->SetTitleOffset(0.45);
								href_ratio2->GetXaxis()->SetTitleOffset(0.95);
								href_ratio2->GetYaxis()->SetLabelSize(0.075);
								href_ratio2->GetXaxis()->SetLabelSize(0.08);
								href_ratio2->SetStats(0);
								href_ratio2->Draw();
								line_1->Draw("same l");


								upPad2->cd();
								TLegend *leg2 = new TLegend( 0.12, 0.55, 0.6, 0.9, "#LTv_{4}^{2}#GT#LTv_{2}^{2}#GT", "brNDC");
								leg2->SetBorderSize(0);
								leg2->SetFillStyle(0);
								leg2->AddEntry(gr_C_factor[isc], "Data"  , "p");
//								leg2->AddEntry(gr_C_factor_EKRT_old[isc][0], "EKRT+viscous Hydrodynamics parm0 (#eta/s=0.2)", "l");
//								leg2->AddEntry(gr_C_factor_EKRT_old[isc][1], "EKRT+viscous Hydrodynamics parm1 (#eta/s(T))", "l");
//								leg2->AddEntry(gr_C_factor_EKRT_old[isc][2], "EKRT+viscous Hydrodynamics parm2 (#eta/s(T))", "l");
//								leg2->AddEntry(gr_C_factor_EKRT_old[isc][3], "EKRT+viscous Hydrodynamics parm3 (#eta/s(T))", "l");
//								leg2->AddEntry(gr_C_factor_EKRT_old[isc][4], "EKRT+viscous Hydrodynamics parm4 (#eta/s(T))", "l");
								//								leg->AddEntry(gr_C_factor_EKRT[isc][0], "EKRT(new) param0", "l");
								//								leg->AddEntry(gr_C_factor_EKRT[isc][1], "EKRT(new) param1", "l");
//								leg2->AddEntry(gr_C_factor_AMPT[isc][0], "AMPT, default", "pl");
//								leg2->AddEntry(gr_C_factor_AMPT[isc][1], "AMPT, string melting", "pl");
//								leg2->AddEntry(gr_C_factor_AMPT[isc][2], "AMPT, string melting w/o hadronic rescattering", "pl");
								for(int ic=0; ic<3; ic++){
										for(int ieta=0; ieta<2; ieta++){
												leg2->AddEntry(gr_C_factor_VISH[isc][ic][ieta], Form("%s",strVISH[ic][ieta].Data()), "pl");
																					}
								}							

							
								leg2->Draw();	

								//
								upPad2->cd();
								if(Draw_Data[isc]==1){
										gr_C_factor_syst[isc]->Draw("same 2");
										gr_C_factor[isc]->Draw("same p");
								};
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){

												gr_C_factor_EKRT_old[isc][ipar]->Draw("same pl");
										}
								};
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												gr_C_factor_EKRT[isc][ipar]->Draw("same pl");
										}
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												gr_C_factor_AMPT[isc][iampt]->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												gr_C_factor_VISH[isc][ic][ieta]->Draw("same pl");
											}
										}
								}


								lowPad2->cd();
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){
												CalculateRatio(gr_C_factor_EKRT_old[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												//	CalculateRatio(gr_C_factor_EKRT[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												CalculateRatio(gr_C_factor_AMPT[isc][iampt], gr_C_factor[isc], 0)->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												CalculateRatio(gr_C_factor_VISH[isc][ic][ieta], gr_C_factor[isc], 0)->Draw("same pl");
											}
										}
								}

								// Calculate ratio

				}
				if(1){
				int isc=2;
				y_max = 0.8e-6;
								TCanvas *c3 = new TCanvas("c3","c3", 600, 700);
								c3->Draw();
								TPad *upPad3 = new TPad("up3","upper pad", 0, 0.3, 1, 1);
								TPad *lowPad3 = new TPad("low3","lower pad", 0, 0, 1, 0.3);

								upPad3->Draw();
								lowPad3->Draw();

								upPad3->cd();
								upPad3->SetTopMargin(0.05);
								upPad3->SetBottomMargin(0);
								TH2D *href3 = new TH2D("href3", "", 100, x_min, x_max, 100,  y_min, y_max);
								href3->GetYaxis()->SetTitleSize(0.04);
								href3->GetYaxis()->SetTitle("#LTv_{5}^{2}#GT#LTv_{2}^{2}#GT");
								href3->GetYaxis()->CenterTitle(1);

								href3->GetYaxis()->SetTitleOffset(1.144);
								href3->GetYaxis()->SetLabelSize(0.035);
								//  TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
								href3->SetStats(0);
								href3->Draw();
								line_0->Draw("same l");

								lowPad3->cd();
								lowPad3->SetTopMargin(0);
								lowPad3->SetBottomMargin(0.2);
								TH2D *href_ratio3 = new TH2D("href_ratio3", "" , 100, x_min, x_max, 100, y_min_ratio, y_max_ratio);
								href_ratio3->GetYaxis()->SetTitle("(Theory-Data)/Data ");
								href_ratio3->GetYaxis()->CenterTitle(1);
								href_ratio3->GetXaxis()->SetTitle("Centrality percentile");
								href_ratio3->GetYaxis()->SetTitleSize(0.09);
								href_ratio3->GetXaxis()->SetTitleSize(0.08);
								href_ratio3->GetYaxis()->SetTitleOffset(0.45);
								href_ratio3->GetXaxis()->SetTitleOffset(0.95);
								href_ratio3->GetYaxis()->SetLabelSize(0.075);
								href_ratio3->GetXaxis()->SetLabelSize(0.08);
								href_ratio3->SetStats(0);
								href_ratio3->Draw();
								line_1->Draw("same l");


								upPad3->cd();
								TLegend *leg3 = new TLegend( 0.12, 0.55, 0.6, 0.9, "#LTv_{5}^{2}#GT#LTv_{2}^{2}#GT", "brNDC");
								leg3->SetBorderSize(0);
								leg3->SetFillStyle(0);

								leg3->AddEntry(gr_C_factor[isc], "Data"  , "p");
//								leg3->AddEntry(gr_C_factor_EKRT[isc][0], "EKRT+viscous Hydrodynamics parm0 (#eta/s=0.2)", "l");
//								leg3->AddEntry(gr_C_factor_EKRT[isc][1], "EKRT+viscous Hydrodynamics parm1 (#eta/s(T))", "l");
//								leg3->AddEntry(gr_C_factor_EKRT[isc][1], "EKRT(new) param1", "l");
//								leg3->AddEntry(gr_C_factor_AMPT[isc][0], "AMPT, default", "pl");
//								leg3->AddEntry(gr_C_factor_AMPT[isc][1], "AMPT, string melting", "pl");
//								leg3->AddEntry(gr_C_factor_AMPT[isc][2], "AMPT, string melting w/o hadronic rescattering", "pl");
								for(int ic=0; ic<3; ic++){
										for(int ieta=0; ieta<2; ieta++){
												leg3->AddEntry(gr_C_factor_VISH[isc][ic][ieta], Form("%s",strVISH[ic][ieta].Data()), "pl");
																					}
								}							



								leg3->Draw();	

								//
								upPad3->cd();
								if(Draw_Data[isc]==1){
										gr_C_factor_syst[isc]->Draw("same 2");
										gr_C_factor[isc]->Draw("same p");
								};
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){

												gr_C_factor_EKRT_old[isc][ipar]->Draw("same pl");
										}
								};
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												gr_C_factor_EKRT[isc][ipar]->Draw("same pl");
										}
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												gr_C_factor_AMPT[isc][iampt]->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												gr_C_factor_VISH[isc][ic][ieta]->Draw("same pl");
											}
										}
								}


								lowPad3->cd();
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){
												CalculateRatio(gr_C_factor_EKRT_old[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												//	CalculateRatio(gr_C_factor_EKRT[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												CalculateRatio(gr_C_factor_AMPT[isc][iampt], gr_C_factor[isc], 0)->Draw("same pl");
										}
								}

								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												CalculateRatio(gr_C_factor_VISH[isc][ic][ieta], gr_C_factor[isc], 0)->Draw("same pl");
											}
										}
								}


								// Calculate ratio

				}

				if(1){
				int isc=3;
				y_max = 0.8e-7;
								TCanvas *c4 = new TCanvas("c4","c4", 600, 700);
								c4->Draw();
								TPad *upPad4 = new TPad("up4","upper pad", 0, 0.3, 1, 1);
								TPad *lowPad4 = new TPad("low4","lower pad", 0, 0, 1, 0.3);

								upPad4->Draw();
								lowPad4->Draw();

								cout << "T" << endl;
								upPad4->cd();
								upPad4->SetTopMargin(0.05);
								upPad4->SetBottomMargin(0);
								TH2D *href4 = new TH2D("href4", "", 100, x_min, x_max, 100,  y_min, y_max);
								href4->GetYaxis()->SetTitleSize(0.04);
								href4->GetYaxis()->SetTitle("#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT");
								href4->GetYaxis()->CenterTitle(1);

								href4->GetYaxis()->SetTitleOffset(1.144);
								href4->GetYaxis()->SetLabelSize(0.035);
								//  TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
								href4->SetStats(0);
								href4->Draw();
								line_0->Draw("same l");

								lowPad4->cd();
								lowPad4->SetTopMargin(0);
								lowPad4->SetBottomMargin(0.2);
								TH2D *href_ratio4 = new TH2D("href_ratio4", "" , 100, x_min, x_max, 100, y_min_ratio, y_max_ratio);
								href_ratio4->GetYaxis()->SetTitle("(Theory-Data)/Data ");
								href_ratio4->GetYaxis()->CenterTitle(1);
								href_ratio4->GetXaxis()->SetTitle("Centrality percentile");
								href_ratio4->GetYaxis()->SetTitleSize(0.09);
								href_ratio4->GetXaxis()->SetTitleSize(0.08);
								href_ratio4->GetYaxis()->SetTitleOffset(0.45);
								href_ratio4->GetXaxis()->SetTitleOffset(0.95);
								href_ratio4->GetYaxis()->SetLabelSize(0.075);
								href_ratio4->GetXaxis()->SetLabelSize(0.08);
								href_ratio4->SetStats(0);
								href_ratio4->Draw();
								line_1->Draw("same l");


								upPad4->cd();
								TLegend *leg4 = new TLegend( 0.12, 0.55, 0.6, 0.9, "#LTv_{5}^{2}#GT#LTv_{3}^{2}#GT", "brNDC");
								leg4->SetBorderSize(0);
								leg4->SetFillStyle(0);

								leg4->AddEntry(gr_C_factor[isc], "Data"  , "p");
//								leg4->AddEntry(gr_C_factor_EKRT[isc][0], "EKRT+viscous Hydrodynamics parm0 (#eta/s=0.2)", "l");
//								leg4->AddEntry(gr_C_factor_EKRT[isc][1], "EKRT+viscous Hydrodynamics parm1 (#eta/s(T))", "l");
//								leg4->AddEntry(gr_C_factor_AMPT[isc][0], "AMPT, default", "pl");
//								leg4->AddEntry(gr_C_factor_AMPT[isc][1], "AMPT, string melting", "pl");
//								leg4->AddEntry(gr_C_factor_AMPT[isc][2], "AMPT, string melting w/o hadronic rescattering", "pl");
								for(int ic=0; ic<3; ic++){
										for(int ieta=0; ieta<2; ieta++){
												leg4->AddEntry(gr_C_factor_VISH[isc][ic][ieta], Form("%s",strVISH[ic][ieta].Data()), "pl");
																					}
								}							



								leg4->Draw();	

								//
								upPad4->cd();
								if(Draw_Data[isc]==1){
										gr_C_factor_syst[isc]->Draw("same 2");
										gr_C_factor[isc]->Draw("same p");
								};
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){

												gr_C_factor_EKRT_old[isc][ipar]->Draw("same pl");
										}
								};
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												gr_C_factor_EKRT[isc][ipar]->Draw("same pl");
										}
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												gr_C_factor_AMPT[isc][iampt]->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												gr_C_factor_VISH[isc][ic][ieta]->Draw("same pl");
											}
										}
								}

								lowPad4->cd();
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){
												CalculateRatio(gr_C_factor_EKRT_old[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												//	CalculateRatio(gr_C_factor_EKRT[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												CalculateRatio(gr_C_factor_AMPT[isc][iampt], gr_C_factor[isc], 0)->Draw("same pl");
										}
								}

								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												CalculateRatio(gr_C_factor_VISH[isc][ic][ieta], gr_C_factor[isc], 0)->Draw("same pl");
											}
										}
								}


								// Calculate ratio

				}

	if(1){
				int isc=4;
				y_max = 0.5e-6;
								TCanvas *c5 = new TCanvas("c5","c5", 600, 700);
								c5->Draw();
								TPad *upPad5 = new TPad("up5","upper pad", 0, 0.3, 1, 1);
								TPad *lowPad5 = new TPad("low5","lower pad", 0, 0, 1, 0.3);

								upPad5->Draw();
								lowPad5->Draw();

								upPad5->cd();
								upPad5->SetTopMargin(0.05);
								upPad5->SetBottomMargin(0);
								TH2D *href5 = new TH2D("href5", "", 100, x_min, x_max, 100,  y_min, y_max);
								href5->GetYaxis()->SetTitleSize(0.04);
								href5->GetYaxis()->SetTitle("#LTv_{4}^{2}#GT#LTv_{3}^{2}#GT");
								href5->GetYaxis()->CenterTitle(1);

								href5->GetYaxis()->SetTitleOffset(1.144);
								href5->GetYaxis()->SetLabelSize(0.035);
								//  TGaxis::SetExponentOffset(0.01644, -0.0844, "y");
								href5->SetStats(0);
								href5->Draw();
								line_0->Draw("same l");

								lowPad5->cd();
								lowPad5->SetTopMargin(0);
								lowPad5->SetBottomMargin(0.2);
								TH2D *href_ratio5 = new TH2D("href_ratio5", "" , 100, x_min, x_max, 100, y_min_ratio, y_max_ratio);
								href_ratio5->GetYaxis()->SetTitle("(Theory-Data)/Data ");
								href_ratio5->GetYaxis()->CenterTitle(1);
								href_ratio5->GetXaxis()->SetTitle("Centrality percentile");
								href_ratio5->GetYaxis()->SetTitleSize(0.09);
								href_ratio5->GetXaxis()->SetTitleSize(0.08);
								href_ratio5->GetYaxis()->SetTitleOffset(0.45);
								href_ratio5->GetXaxis()->SetTitleOffset(0.95);
								href_ratio5->GetYaxis()->SetLabelSize(0.075);
								href_ratio5->GetXaxis()->SetLabelSize(0.08);
								href_ratio5->SetStats(0);
								href_ratio5->Draw();
								line_1->Draw("same l");


								upPad5->cd();
								TLegend *leg5 = new TLegend( 0.12, 0.55, 0.6, 0.9, "#LTv_{4}^{2}#GT#LTv_{3}^{2}#GT", "brNDC");
								leg5->SetBorderSize(0);
								leg5->SetFillStyle(0);

								leg5->AddEntry(gr_C_factor[isc], "Data"  , "p");
//								leg5->AddEntry(gr_C_factor_EKRT[isc][0], "EKRT+viscous Hydrodynamics parm0 (#eta/s=0.2)", "l");
//								leg5->AddEntry(gr_C_factor_EKRT[isc][1], "EKRT+viscous Hydrodynamics parm1 (#eta/s(T))", "l");
//								leg5->AddEntry(gr_C_factor_AMPT[isc][0], "AMPT, default", "pl");
//								leg5->AddEntry(gr_C_factor_AMPT[isc][1], "AMPT, string melting", "pl");
//								leg5->AddEntry(gr_C_factor_AMPT[isc][2], "AMPT, string melting w/o hadronic rescattering", "pl");

								for(int ic=0; ic<3; ic++){
										for(int ieta=0; ieta<2; ieta++){
												leg5->AddEntry(gr_C_factor_VISH[isc][ic][ieta], Form("%s",strVISH[ic][ieta].Data()), "pl");
																					}
								}							

								leg5->Draw();	

								//
								upPad5->cd();
								if(Draw_Data[isc]==1){
										gr_C_factor_syst[isc]->Draw("same 2");
										gr_C_factor[isc]->Draw("same p");
								};
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){

												gr_C_factor_EKRT_old[isc][ipar]->Draw("same pl");
										}
								};
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												gr_C_factor_EKRT[isc][ipar]->Draw("same pl");
										}
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												gr_C_factor_AMPT[isc][iampt]->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												gr_C_factor_VISH[isc][ic][ieta]->Draw("same pl");
											}
										}
								}


								lowPad5->cd();
								if(Draw_old_ekrt[isc]==1){
										for(int ipar=0; ipar<5; ipar++){
												CalculateRatio(gr_C_factor_EKRT_old[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_new_ekrt[isc]==1){
										for(int ipar=0; ipar<2; ipar++){
												//	CalculateRatio(gr_C_factor_EKRT[isc][ipar], gr_C_factor[isc], 0)->Draw("same pl");
										}	
								}
								if(Draw_AMPT[isc]==1){
										for(int iampt=0; iampt<3; iampt++){
												CalculateRatio(gr_C_factor_AMPT[isc][iampt], gr_C_factor[isc], 0)->Draw("same pl");
										}
								}
								if(Draw_VISH21[isc][0]==1){
										for(int ic=0; ic<3; ic++){
											for(int ieta=0; ieta<2; ieta++){
												CalculateRatio(gr_C_factor_VISH[isc][ic][ieta], gr_C_factor[isc], 0)->Draw("same pl");
											}
										}
								}

								// Calculate ratio

				}



/// DJ's ask only ratio in 1 canvas
	TCanvas *c1000 = new TCanvas("c1000", "", 1000, 600);
	c1000->Draw();
	isc = 4; // vm2vn2 = 3,2
	int m=4; int n=3;
	TH2D *href = new TH2D("href1000", Form("#LTv_{%d}^{2}#GT#LTv_{%d}^{2}#GT", m, n), 100, 0, 52, 100, -1.2, 1.2);
	href->SetStats(0); 
	href->GetYaxis()->SetTitle("(Theory-Data)/Data");
	href->GetXaxis()->SetTitle("Centrality percentile");
	href->Draw();	
	line_0->Draw("same");	

	

	for(int i=0; i<3; i++){
		gr_C_factor_AMPT[isc][i]->SetLineColor(kOrange+2*i);
		gr_C_factor_AMPT[isc][i]->SetMarkerColor(kOrange+2*i);
		gr_C_factor_AMPT[isc][i]->SetLineWidth(3);
		CalculateRatio( gr_C_factor_AMPT[isc][i], gr_C_factor[isc], 0)->Draw("same pl");
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<2; j++){
			CalculateRatio( gr_C_factor_VISH[isc][i][j], gr_C_factor[isc], 0)->Draw("same pl");
		}
	}
	for(int i=0; i<2; i++){
		CalculateRatio( gr_C_factor_EKRT[isc][i], gr_C_factor[isc], 0)->Draw("same l");
	}
	

	TLegend *leg100 = new TLegend( 0.6, 0.6, 0.9, 0.90, "", "brNDC");
	leg100->SetBorderSize(0);
	leg100->SetFillStyle(0);

	leg100->AddEntry(gr_C_factor_EKRT[isc][0], "EKRT+viscous Hydrodynamics parm0 (#eta/s=0.2)", "l");
	leg100->AddEntry(gr_C_factor_EKRT[isc][1], "EKRT+viscous Hydrodynamics parm1 (#eta/s(T))", "l");
	leg100->AddEntry(gr_C_factor_AMPT[isc][0], "AMPT, default", "pl");
	leg100->AddEntry(gr_C_factor_AMPT[isc][1], "AMPT, string melting", "pl");
	leg100->AddEntry(gr_C_factor_AMPT[isc][2], "AMPT, string melting w/o hadronic rescattering", "pl");
	for(int i=0; i<3; i++){
		for(int j=0; j<2; j++){
	leg100->AddEntry(gr_C_factor_VISH[isc][i][j], Form("%s",strVISH[i][j].Data()), "pl");
		}
	}
	leg100->Draw();


	c1000->SaveAs(Form("figs/vm2vn2_SC%d%d_rationly.eps", m,n) );
//



}

//=====================================================================================================
//=====================================================================================================
//=====================================================================================================
void LoadSCResults(){
                cout << "start loding SC(m,n) C factor from Data" << endl;
                TFile *fin_data = new TFile("results_0720/results_LHC10h_JFFlucAODLHC10h_Default.root", "read" );

                    for(int isc=0; isc<kNSC; isc++){
                                if(Draw_Data[isc]==0) continue;
                                TGraphErrors *gr_vm2 = (TGraphErrors*)fin_data->Get(Form("gr_v%d", SC_combination[isc][0] ));
                                TGraphErrors *gr_vn2 = (TGraphErrors*)fin_data->Get(Form("gr_v%d", SC_combination[isc][1] ));

                                gr_C_factor[isc] = new TGraphErrors();
                                int Npoint = gr_vm2->GetN();
                                for(int ipoint=0; ipoint<Npoint; ipoint++){
                                                double x = gr_vm2->GetX()[ipoint];
                                                double vm2 = gr_vm2->GetY()[ipoint];
                                                double vn2 = gr_vn2->GetY()[ipoint];
                                                double eyvm2 = gr_vm2->GetEY()[ipoint];
                                                double eyvn2 = gr_vn2->GetEY()[ipoint];

                                                gr_C_factor[isc]->SetPoint( ipoint, x, vn2*vn2* vm2*vm2);
                                                gr_C_factor[isc]->SetPointError(ipoint ,  0, vn2*vn2*vm2*vm2* TMath::Sqrt( TMath::Power( eyvm2/ vm2, 2) + TMath::Power( eyvn2 / vn2, 2) ));
                                };
                                gr_C_factor[isc]->SetMarkerStyle(kFullCircle);
                                gr_C_factor[isc]->SetMarkerColor(kBlack);
                };
                    for(int isc=0; isc<kNSC; isc++){
                            if(Draw_Data[isc]==0) continue;
                            gr_C_factor_syst[isc] = (TGraphErrors*)gr_C_factor[isc]->Clone();
                            int Npoint = gr_C_factor[isc]->GetN();
                            for(int ipoint=0; ipoint<Npoint; ipoint++){
                                    double sErr = gr_C_factor[isc]->GetY()[ipoint] * systErr[isc];
                                    gr_C_factor_syst[isc]->SetPointError( ipoint, 0.8, sErr);
                            }
                            gr_C_factor_syst[isc]->SetFillColor(kGray);
                            gr_C_factor_syst[isc]->SetFillStyle(1000);
                    };

                    cout << "load data done.. " << endl;



}

//=====================================================================================================

void Load_old_ekrt(){
				bool do_old_param[5] = {1,1,1,1,1}; // do it over all parameters
				cout << "start loading SC(m,n) C factor from old EKRT calculations" << endl;
				TFile *fin_harri_old = new TFile("Harris_results/Harris_SC_datapoint.root", "read");
				
				for(int isc=0; isc<kNSC; isc++){
								if(Draw_old_ekrt[isc]==0) continue;
								for(int ipar=0; ipar<5; ipar++){
												//cout << Form("gr_harri_v%d2_v%d2_par%d", SC_combination[isc][1], SC_combination[isc][0], ipar) << endl;
												gr_C_factor_EKRT_old[isc][ipar] = (TGraphErrors*)fin_harri_old->Get(Form("gr_harri_v%d2_v%d2_par%d", SC_combination[isc][1], SC_combination[isc][0], ipar));
												gr_C_factor_EKRT_old[isc][ipar]->SetMarkerColor(gHarriEtaColor[ipar] );
												gr_C_factor_EKRT_old[isc][ipar]->SetLineColor(gHarriEtaColor[ipar] );
												gr_C_factor_EKRT_old[isc][ipar]->SetLineStyle( 2+ipar);
												gr_C_factor_EKRT_old[isc][ipar]->SetLineWidth(3);
								}
				};		
				cout << "load ekrt old done ... " << endl;
}

//=====================================================================================================
void Load_new_ekrt(){
		const int npar=2;
		bool do_new_param[npar] = {1, 1}; // eta/s = parm0, parm1 , (param0 = 0.20 const)
		
		cout << "start loading SC(m,n) C factor from new EKRT calculations" << endl;
		TFile *fin_ekrt[npar]; 
		TString fin_ekrt_name[npar]= {
				"Harris_results/EKRT_eta_020_pt_NSC.root", 
				"Harris_results/EKRT_eta_par1_pt_NSC.root"
		};
		for(int ipar=0; ipar<npar; ipar++){
			if(do_new_param[ipar]==0) continue;
			fin_ekrt[ipar] = new TFile( fin_ekrt_name[ipar].Data(), "read"); // file loaded
			for(int isc=0; isc<kNSC; isc++){
				if(Draw_new_ekrt[isc]==0) continue;			
//					cout << Form(	"gr_vm2_vn2_%d_pt_%d", isc, 1) << endl;
					gr_C_factor_EKRT[isc][ipar] = (TGraphErrors*)fin_ekrt[ipar]->Get( Form( "gr_vm2_vn2_%d_pt_%d", isc, 1) );
					gr_C_factor_EKRT[isc][ipar]->SetLineStyle(1+ipar);
					gr_C_factor_EKRT[isc][ipar]->SetLineWidth(3);
					gr_C_factor_EKRT[isc][ipar]->SetLineColor(gHarriEtaColor[ipar]);
			};
		}
	
		cout << "load ekrt new done" << endl;
};

//=====================================================================================================
void Load_AMPT(){
	cout << "start load ampt " << endl;
	const int kNAMPT=3;
	bool do_ampt[kNAMPT] = { 1, 1, 1};
	int ampt_color[3] = { kRed, kBlue, kGreen+2};
	TString strAMPTFile[kNAMPT] = {
            "results_0720/results_AMPT13f3b_JFFluc_KineOnly_Eta0408_Pt0250.root",
            "results_0720/results_AMPT13f3c_JFFluc_KineOnly_Eta0408_Pt0250.root",
            "results_0720/results_AMPT13f3a_JFFluc_KineOnly_Eta0408_Pt0250.root"}

	TFile *fin_ampt[kNAMPT];
	for(int iampt=0; iampt<kNAMPT; iampt++){
			if(do_ampt[iampt]==0) continue;
			fin_ampt[iampt] = new TFile( strAMPTFile[iampt].Data(), "read" );
			for( int isc=0; isc<kNSC; isc++){
					if(Draw_AMPT[isc]==0) continue;

				TGraphErrors *gr_sc =(TGraphErrors*)fin_ampt[iampt]->Get(Form("gr_SC_with_QC_%s", strSCName[isc].Data() ));
				TGraphErrors *gr_nsc =(TGraphErrors*)fin_ampt[iampt]->Get(Form("gr_SC_norm_with_QC_%s", strSCName[isc].Data() ));

					gr_C_factor_AMPT[isc][iampt] = Cal_C_factor(gr_nsc, gr_sc);

					gr_C_factor_AMPT[isc][iampt]->SetMarkerStyle(kFullCircle);
					gr_C_factor_AMPT[isc][iampt]->SetMarkerColor(ampt_color[iampt]);
					gr_C_factor_AMPT[isc][iampt]->SetLineColor(ampt_color[iampt]);
			};

			//TGraphErrors *gr_C_factor_AMPT[kNSC][3]; // 3 ampt sets
	};
	cout << "load ampt done.. " << endl;
};

//=====================================================================================================
//TGraphErrors *gr_C_factor_VISH[kNSC][3][2]; // 3IC settings, 2 eta/s settings
void Load_VISH(){
	cout << "start loading VISH2+1" << endl;
	TString strVISH[3][2] = {
				"VISH_simdata/AMPT/resultSCR.root", "VISH_simdata/AMPT/resultSC.root",
				"VISH_simdata/KLN/resultSCR.root", "VISH_simdata/KLN/resultSC.root",
				"VISH_simdata/Glb/resultSCR.root", "VISH_simdata/Glb/resultSC.root"};

	TFile *fin_VISH[3][2];
	int vc[3] = {kRed, kBlue, kGreen+2};
	for(int ic=0; ic<3; ic++){
		for(int i=0; i<2; i++){
			fin_VISH[ic][i] = new TFile( strVISH[ic][i].Data(), "read");
		}
	}

	TString strSCNameVISH[kNSC] = {"32", "42", "52", "53", "43"};
	int vm[3] = { kOpenCircle, kOpenSquare, kOpenDiamond };
	for(int isc=0; isc<kNSC; isc++){
	for(int ic=0; ic<3; ic++){
		for(int ieta=0; ieta<2; ieta++){

			TGraphErrors *gr_nsc=(TGraphErrors*)fin_VISH[ic][0]->Get(Form("SC%s_%d", strSCNameVISH[isc].Data(), ieta) );
			TGraphErrors *gr_sc=(TGraphErrors*)fin_VISH[ic][1]->Get(Form("SC%s_%d", strSCNameVISH[isc].Data(), ieta) );

			gr_C_factor_VISH[isc][ic][ieta] = Cal_C_factor(gr_nsc, gr_sc);
//			gr_C_factor_VISH[isc][ic][ieta]->Print();
			gr_C_factor_VISH[isc][ic][ieta]->SetLineColor(vc[ic] );	
			gr_C_factor_VISH[isc][ic][ieta]->SetMarkerColor(vc[ic] );	
			gr_C_factor_VISH[isc][ic][ieta]->SetMarkerSize( 1.2 );	
			gr_C_factor_VISH[isc][ic][ieta]->SetLineStyle(1+6*ieta);
			gr_C_factor_VISH[isc][ic][ieta]->SetMarkerStyle( vm[ic] );
			gr_C_factor_VISH[isc][ic][ieta]->SetLineWidth(2.5);
			
		}
	}
	};

}


//=====================================================================================================
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
//                double ratio = TMath::Abs( y1 / y2 );
				double ratio = ( y1 - y2 ) / y2;
                gr_ratio->SetPoint( i, x+xshift, ratio);
                gr_ratio->SetPointError( i, 0, ratio * TMath::Sqrt( ey1*ey1/y1/y1 + ey2*ey2/y2/y2 ));

        }

		gr_ratio->SetLineColor(gr1->GetLineColor());
		gr_ratio->SetMarkerColor(gr1->GetMarkerColor() );
		gr_ratio->SetLineWidth(gr1->GetLineWidth() );
		gr_ratio->SetMarkerStyle(gr1->GetMarkerStyle() );
		gr_ratio->SetLineStyle(gr1->GetLineStyle() );

        return gr_ratio;
}

//=====================================================================================================
TGraphErrors *Cal_C_factor( TGraphErrors* gr_nsc, TGraphErrors* gr_sc){
	int NPoint = gr_nsc->GetN();
	TGraphErrors *gr_C = new TGraphErrors();
	for(int i=0; i<NPoint; i++){
		double x = gr_nsc->GetX()[i];
		double nsc = gr_nsc->GetY()[i];
		double sc = gr_sc->GetY()[i];
		double err_sc = gr_sc->GetEY()[i];
		double err_nsc = gr_nsc->GetEY()[i];
		double c = sc / nsc;
		double err_c = c * (( err_sc/sc * err_sc/sc + err_nsc /nsc *err_nsc / nsc  ) );
		gr_C->SetPoint( i, x, c);	
//		gr_C->SetPointError(i, 0, err_c);
	}
	return gr_C;
}
