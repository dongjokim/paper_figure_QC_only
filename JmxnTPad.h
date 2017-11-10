//------------------------------------------------------------------------
//
// JmxnTPad  class divides canvas into a latice of m x n sepate pads 
// pads share x and y axes and their titels and labels
//
// ANNO DOMINI 19Apr 2010 (while stining on a long phenix night shift)  
//
//                                                    FK 
//
// -----------------------------------------------------------------------
// How to Usage it:
//  #include "JmxnTPad.h"
//{  //set number of pads and lower and upper ranges
//  const int nx=1; const int ny=2;
//  double lrX[nx]={0.3};   double urX[nx]={100.};
//  double lrY[ny]={0, 0};  double urY[ny]={10, 10};
//  
//  JmxnTPad  *plot =new JmxnTPad(nx, ny, lrX, urX, lrY, urY);
//  plot->SetTitleX("#Delta#phi [rad/#pi]");
//
//  for(Int_t i=0;i<nx;i++){
//    for(Int_t j=0;j<ny;j++){
//      TString c="caption xy";
//      plot->SetCaption(i, j,c);  // puting caption to each pad
//    }
//  }
//
//  plot->Draw();  
//  
//  TPad* p = plot->GetPad(0,0); //include graph to the upper left pad 
//  p->cd();  
//  your_graph->Draw("psame");
//}
//__________________________________________________________________________

#include "TH1D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLatex.h"

#define kDUMMYSIZE 30         //some dummy number for initialization
#define kDefaultMinLogY 0.001 //default minimum of the log scale when y axis is set to start from zero 



class JmxnTPad { 

  public:
    JmxnTPad();
    JmxnTPad(const int nXpads, const int nYpads, double *lowerRangesX, double *upperRangesX, double *lowerRangesY, double *upperRangesY, bool logx = 0, bool logy = 0);

    ~JmxnTPad();

    void Draw();
    TPad* GetPad(int ix, int iy){ return (TPad*) toppad->cd(100*ix+iy+1);}//coordinates 0,0 = upper left  
    TVirtualPad * GetTopPad(){return toppad;}

    void SetTitleX(TString title,   bool centralize = 0, double size = 0.05, int font = 42, double offset = 1.0, bool drawUnderEachColumn=0);
    void SetTitleY(TString title,   bool centralize = 1, double size = 0.05, int font = 42, double offset = 1.5, bool drawForEachRow=0);
    void SetTitleTop(TString title, bool centralize = 1, double size = 0.05, int font = 42, double offset = 0.5);
  
    void SetOptionsAxisX(int ndiv = 505, double ticksLength = 0.04, bool logScale =0);
    void SetOptionsAxisY(int ndiv = 505, double ticksLength = 0.04, bool logScale =0);
    void SetLogX(bool lx=1 ){logX = lx;}
    void SetLogY(bool ly=1 ){logY = ly;}

    void SetCanvas(float aspekt=1, float size=800, float sdx=10, float sdy=10);
    void SetMargins(double marginLeft = 0.18, double marginBottom = 0.13, double marginRight =0.05, double marginTop=0.1);
    void SetOptionsPads(bool  gridX=0, bool gridY=0, bool ticksOnX=0, bool ticksOnY=0);

    void SetOptionsCaption(double captionTextSizePx = 20, double captionTextFont = 43, double captionX = 0.9, double captionY = 4./5); 
    void SetYCaption(double captionY = 4./5){ CaptionY = captionY;} 
    void SetCaption(int ix, int iy, TString caption=""){ if(0<=ix && ix<kDUMMYSIZE && 0<=iy && iy<kDUMMYSIZE) Caption[ix][iy]=caption;}

    void SetOptionsLabelAxisY(double offsetLabelY = 0.007, double textSizeLabelY = 0.7, double textFontLabelY = 42); 
    void SetSizeOfLabelPadsAxisY(double width = 0.05, double height = 0.017); 
    void SetOptionsLabelAxisX(double offsetLabelX = 0.01, double textSizeLabelX = 0.8, double textFontLabelX = 42);
    void SetSizeOfLabelPadsAxisX(double width = 0.021, double height = 0.05);   



  protected:
    double LocateCaption(double relpos, double lowRange, double upRange, bool setLog);
    void   AdjustTGaxis(TGaxis *gax,  TString title, double sizeTit, int fontTit, double offsetTit, bool centTit,  double sizeLab, int fontLab,int colLab, int lineCol);
   
     
    int nX; // number of pads in X direction (columns) 
    int nY; // number of pads in Y direction (rows)

   // A X I S 
    double *lower_range_X;  //lower limits of X axis
    double *upper_range_X;  //upper limits of X axis
    double *lower_range_Y;  //lower limits of Y axis
    double *upper_range_Y;  //upper limits of Y axis
    int    NDivX;           //Ndivisions for x axis
    int    NDivY;           //Ndivisions for y axis
    double TicksLengthX;    //length of ticks on X axis
    double TicksLengthY;    //length of ticks on Y axis
    bool   logX;            //set Log scale on Y axis
    bool   logY;            //set Log scale on Y axis

    // A X I S   L A B E L S   Y:
    double OffsetLabelY;       // label offset 
    double TextSizeLabelY;     // label text size 
    double TextFontLabelY;     // label text font 
    double xxLabelYDeltaWidth; //  X size of the TPad where we write label - change only if necessary 
    double yyLabelYDeltaHeigt; //  Y size of the TPad where we write label - change only if necessary

    // A X I S    L A B E L S   X:
    double OffsetLabelX;        // label offset 
    double TextSizeLabelX;      // label text size 
    double TextFontLabelX;      // label text font 
    double xxLabelXDeltaWidth;  //  X size of the TPad where we write label - change only if necessary
    double yyLabelXDeltaHeigt;  //  Y size of the TPad where we write label 


     // A X I S    T I T L E   X:
    TString TitleX;              // X title text
    bool    CentralizeTitleX;    // draw X title to the center
    bool    EachColumnHasTitleX; // draw X title UnderEachColumn
    double  OffsetTitleX;        // X title offset
    int     TextFontTitleX;      // X title text font
    double  TextSizeTitleX;      // X title text size 
    
    // A X I S    T I T L E  Y:
    TString TitleY;              // Y title text
    bool    CentralizeTitleY;    // draw Y title to the center
    bool    EachRowHasTitleY;    // draw Y title For Each Row
    double  OffsetTitleY;        // Y title offset
    int     TextFontTitleY;      // Y title text font
    double  TextSizeTitleY;      // Y title text size

    // M A I N    T I T L E
    TString Title;               // top title text
    bool    CentralizeTitle;     // draw title in the center
    double  OffsetTitle;         // title offset
    int     TextFontTitle;       // title text font
    double  TextSizeTitle;       // title text size

   //C A P T I O N S   I N   P A D S
    double   CaptionTextSizePx;  //caption text size
    double   CaptionTextFont;    //caption text font
    double   CaptionX;           //X relative position of the caption within the graph
    double   CaptionY;           //Y relative position of the caption within the graph  
    TString  Caption[kDUMMYSIZE][kDUMMYSIZE];

    //  M A I N     C A N V A S 
    float aspektCanvas;      //size and positioning of the main canvas 
    float sizeCanvas, sdxCanvas, sdyCanvas;

    double MarginLeft; //Margins around the latice of nx times ny pads 
    double MarginBottom; 
    double MarginRight;  
    double MarginTop;

    bool   GridX;//set grid on X 
    bool   GridY; //set grid on Y
    bool   TicksOnX;//draw X Ticks in each pad
    bool   TicksOnY;//draw Y Ticks in each pad


   
    TCanvas *C;
    TVirtualPad *toppad;

    TH1F *hDummy[kDUMMYSIZE][kDUMMYSIZE];

};

//--------------------------------------------------------------
JmxnTPad::JmxnTPad():
   nX(0), nY(0),
   lower_range_X(NULL), upper_range_X(NULL), lower_range_Y(NULL), upper_range_Y(NULL),
   NDivX(505), NDivY(505), TicksLengthX(0.05), TicksLengthY(0.03), logX(0), logY(0),
   TitleX(""), CentralizeTitleX(0), EachColumnHasTitleX(0), OffsetTitleX(1.), TextFontTitleX(42), TextSizeTitleX(0.05), 
   TitleY(""), CentralizeTitleY(0), EachRowHasTitleY(0),    OffsetTitleY(1.5), TextFontTitleY(42), TextSizeTitleY(0.05),
   Title(""),  CentralizeTitle(0) ,                         OffsetTitle(0.5) , TextFontTitle(42),  TextSizeTitle(0.05),
   CaptionTextSizePx(20), CaptionTextFont(43), CaptionX(0.9), CaptionY(4./5),
   OffsetLabelY(0.007), TextSizeLabelY(0.7), TextFontLabelY(42),  
   xxLabelYDeltaWidth(0.05), yyLabelYDeltaHeigt(0.017),
   OffsetLabelX(0.01), TextSizeLabelX(0.8), TextFontLabelX(42), 
   xxLabelXDeltaWidth(0.021), yyLabelXDeltaHeigt(0.05),
   aspektCanvas(1), sizeCanvas(800), sdxCanvas(10.), sdyCanvas(10.),
   MarginLeft(0.18), MarginBottom(0.13), MarginRight(0.05), MarginTop(0.1),
   GridX(0), GridY(0), TicksOnX(0), TicksOnY(0),
   C(NULL),
   toppad(NULL)
{
//default constructor
  for(int i=0;i<kDUMMYSIZE;i++){
    for(int j=0;j<kDUMMYSIZE;j++){ 
       hDummy[i][j]  = NULL;
       Caption[i][j] = "";
    }
  }
}
//--------------------------------------------------------------
JmxnTPad::JmxnTPad(const int nXpads, const int nYpads, double *lowerRangesX, double *upperRangesX, double *lowerRangesY, double *upperRangesY, bool logx, bool logy):
   nX(nXpads), nY(nYpads),
   lower_range_X(lowerRangesX), upper_range_X(upperRangesX), lower_range_Y(lowerRangesY), upper_range_Y(upperRangesY),
   logX(logx),logY(logy),
   NDivX(505), NDivY(505), TicksLengthX(0.05), TicksLengthY(0.03), 
   TitleX(""), CentralizeTitleX(0), EachColumnHasTitleX(0), OffsetTitleX(1.), TextFontTitleX(42), TextSizeTitleX(0.05), 
   TitleY(""), CentralizeTitleY(0), EachRowHasTitleY(0),    OffsetTitleY(1.5), TextFontTitleY(42), TextSizeTitleY(0.05),
   Title(""),  CentralizeTitle(0) ,                         OffsetTitle(0.5) , TextFontTitle(42),  TextSizeTitle(0.05),
   CaptionTextSizePx(20), CaptionTextFont(43), CaptionX(0.9), CaptionY(4./5),
   OffsetLabelY(0.007), TextSizeLabelY(0.7), TextFontLabelY(42),  
   xxLabelYDeltaWidth(0.05), yyLabelYDeltaHeigt(0.017),
   OffsetLabelX(0.01), TextSizeLabelX(0.8), TextFontLabelX(42), 
   xxLabelXDeltaWidth(0.021), yyLabelXDeltaHeigt(0.05),
   aspektCanvas(1), sizeCanvas(800), sdxCanvas(10.), sdyCanvas(10.),
   MarginLeft(0.18), MarginBottom(0.13), MarginRight(0.05), MarginTop(0.1),
   GridX(0), GridY(0), TicksOnX(0), TicksOnY(0),
   C(NULL),
   toppad(NULL)
{
  //parametric constructor
  for(int i=0;i<kDUMMYSIZE;i++){
    for(int j=0;j<kDUMMYSIZE;j++){
      hDummy[i][j]  = NULL;
      Caption[i][j] = "";
    }
  }
}

//--------------------------------------------------------------

JmxnTPad::~JmxnTPad(){
  //destructor
  if(C)      delete C;
  if(toppad) delete toppad;
  if(hDummy[0][0]){
  for(int i=0;i<kDUMMYSIZE;i++){
    for(int j=0;j<kDUMMYSIZE;j++){
		delete hDummy[i][j];
	}
	}
	}
}

//--------------------------------------------------------------
void JmxnTPad::SetTitleX(TString title, bool centralize, double size, int font, double offset, bool drawUnderEachColumn){
  //set X axis title options
    TitleX              = title;            
    CentralizeTitleX    = centralize;   
    EachColumnHasTitleX = drawUnderEachColumn; 
    OffsetTitleX        = offset;       
    TextFontTitleX      = font;     
    TextSizeTitleX      = size;   
}

//--------------------------------------------------------------
void JmxnTPad::SetTitleY(TString title, bool centralize, double size, int font, double offset, bool drawForEachRow){
  //set Y axis title options
    TitleY            = title;
    CentralizeTitleY  = centralize;
    EachRowHasTitleY  = drawForEachRow;
    OffsetTitleY      = offset;
    TextFontTitleY    = font;
    TextSizeTitleY    = size;
}

//--------------------------------------------------------------
void JmxnTPad::SetTitleTop(TString title, bool centralize, double size, int font, double offset){
  //set top title options
  Title            = title;
  CentralizeTitle  = centralize;
  OffsetTitle      = offset;
  TextFontTitle    = font;
  TextSizeTitle    = size;
}
//--------------------------------------------------------------
void JmxnTPad::SetOptionsCaption(double captionTextSizePx, double captionTextFont, double captionX, double captionY){
  //set caption options
  CaptionTextSizePx = captionTextSizePx;
  CaptionTextFont   = captionTextFont;
  CaptionX          = captionX; 
  CaptionY          = captionY;
} 
//--------------------------------------------------------------
void JmxnTPad::SetOptionsAxisX(int ndiv, double ticksLength, bool logScale){
  //set X axis options
  NDivX        = ndiv;  
  TicksLengthX = ticksLength; 
  logX         = logScale;   
}

//--------------------------------------------------------------
void JmxnTPad::SetOptionsAxisY(int ndiv, double ticksLength, bool logScale){
  //set Y axis options
  NDivY        = ndiv;  
  TicksLengthY = ticksLength; 
  logY         = logScale;   
}
//--------------------------------------------------------------
void JmxnTPad::SetCanvas(float aspekt, float size, float sdx, float sdy){
  //set size and positioning of the main canvas 
   aspektCanvas = aspekt; 
   sizeCanvas   = size;
   sdxCanvas    = sdx; 
   sdyCanvas    = sdy;
}
//--------------------------------------------------------------
void JmxnTPad::SetMargins(double marginLeft, double marginBottom, double marginRight, double marginTop){
  //set margins around the lattice of pads
  MarginLeft   = marginLeft; //Margins around the latice of nx times ny pads 
  MarginBottom = marginBottom; 
  MarginRight  = marginRight;
  MarginTop    = marginTop;
}
//--------------------------------------------------------------
void JmxnTPad::SetOptionsPads(bool  gridX, bool gridY, bool ticksOnX, bool ticksOnY){
  //set ticks and grids in pads
  GridX    = gridX;
  GridY    = gridY; 
  TicksOnX = ticksOnX;
  TicksOnY = ticksOnY;
}
//--------------------------------------------------------------
void JmxnTPad::SetOptionsLabelAxisY(double offsetLabelY, double textSizeLabelY, double textFontLabelY){
  //set style of label on Y axis
  OffsetLabelY   = offsetLabelY;
  TextSizeLabelY = textSizeLabelY; 
  TextFontLabelY = textFontLabelY;
} 
//--------------------------------------------------------------
void JmxnTPad::SetSizeOfLabelPadsAxisY(double width, double height){
  //in necessary you may use this function to change sizes of TPads which contain Y axis labels
  xxLabelYDeltaWidth = width; 
  yyLabelYDeltaHeigt = height; 
}

//--------------------------------------------------------------
 void JmxnTPad::SetOptionsLabelAxisX(double offsetLabelX, double textSizeLabelX, double textFontLabelX){
  //set style of label on X axis
  OffsetLabelX   = offsetLabelX;
  TextSizeLabelX = textSizeLabelX;
  TextFontLabelX = textFontLabelX; 
}
//--------------------------------------------------------------
void JmxnTPad::SetSizeOfLabelPadsAxisX(double width, double height){
  //in necessary you may use this function to change sizes of TPads which contain X axis labels
  xxLabelXDeltaWidth = width;
  yyLabelXDeltaHeigt = height;
}
//--------------------------------------------------------------
double JmxnTPad::LocateCaption(double relpos, double lowRange, double upRange, bool setLog){
  //calculates postion of a caption within a pad in case that lin or log scales are set
  if(!setLog){ //axis in linear scale:
    return relpos*upRange;//linear scale
  }else{       //axis in log scale:
    return TMath::Power(upRange/lowRange, relpos)*lowRange;
  }
}

//--------------------------------------------------------------
void JmxnTPad::AdjustTGaxis(TGaxis *gax,  TString title, double sizeTit, int fontTit, double offsetTit, bool centTit,  double sizeLab, int fontLab,int colLab, int lineCol){
  //adjust gaxis
  gax->SetTitleSize(sizeTit);
  gax->SetTitleFont(fontTit);
  gax->SetTitle(title);
  gax->SetTitleOffset(offsetTit);
  if(centTit) gax->CenterTitle();

  gax->SetLabelSize(sizeLab);
  gax->SetLabelFont(fontLab);
  gax->SetLabelColor(colLab);

  gax->SetLineColor(lineCol);
}
//--------------------------------------------------------------
void JmxnTPad::Draw() {
  //draw  canvas
  //inside draw nX x nY latice of pads
  //around draw overleying pads with labels (TGaxis)
  //and axis titles (using TGaxis)
  if(nX*nY == 0){
    printf("WARNING: initialize you canvas");
    return;
  }  
    
  char name[100], hname[100]; 
  if(C)            delete C;
  if(toppad)       delete toppad;
  if(hDummy[0][0]){
  for(int i=0;i<kDUMMYSIZE;i++){
    for(int j=0;j<kDUMMYSIZE;j++){
		delete hDummy[i][j];
	}
	}
	}

  int o =  (int)  gRandom->Uniform(100,10000);
  sprintf(name,"c_%d",o);

  C = new TCanvas(name, name, sdxCanvas, sdyCanvas, sizeCanvas*aspektCanvas, sizeCanvas);//the main canvas
  C->SetFillStyle(4000); C->SetFillColor(10);
  gStyle->SetOptStat(0);       gStyle->SetOptTitle(0);
  gStyle->SetPadTopMargin(0.); gStyle->SetPadBottomMargin(0.);//our pads will have no margin
  gStyle->SetPadLeftMargin(0.);gStyle->SetPadRightMargin(0.);

  //Create Dummy histograms for formating purposes (set upper and lower limits of histograms, ticks)
  for(int ix=0; ix<nX;ix++){
    for(int iy=0; iy<nY;iy++){
      //if log scales required check the lower limit
      if(logY && lower_range_Y[iy]<=0){ 
        printf("WARNING:  log Y scale does not permit non pozitive values, minimum in [%d,%d] pad set defult to %f",ix,iy,kDefaultMinLogY);
        lower_range_Y[iy] = kDefaultMinLogY; // log scale does not permit non pozitive values!
      }
      if(logX && lower_range_X[ix]<=0){
        printf("WARNING:  log X scale does not permit non pozitive values, minimum in [%d,%d] pad set defult to %f",ix,iy,kDefaultMinLogY);
        lower_range_X[ix] = kDefaultMinLogY; // log scale does not permit non pozitive values!
      }
    
      sprintf(name,"hDummyHist%d_%d",ix+o,iy+o);
      hDummy[ix][iy] = new TH1F(name,"", 3564, lower_range_X[ix] , upper_range_X[ix]); 
      hDummy[ix][iy]->SetMinimum(lower_range_Y[iy]);
      hDummy[ix][iy]->SetMaximum(upper_range_Y[iy]);
      hset( *hDummy[ix][iy], "","", 0.9,  0.5, 0.06,0.06, 0.01,0.001,0.05,0.05, NDivX,NDivY);
      hDummy[ix][iy]->GetXaxis()->SetTickLength(TicksLengthX);//set ticks
      hDummy[ix][iy]->GetYaxis()->SetTickLength(TicksLengthY);
    }
  } 

  
  toppad = gPad; //pointer to the top TPad which will contain labels + histograms
  toppad->Clear();
    
  //calculate positions of latice points in the grid of histograms
  double *yCorner = new double[nY+1]; //begining and end coordinates of the pads ... Y
  double *xCorner = new double[nX+1]; //begining and end coordinates of the pads ... X
  double dy = (1-MarginTop-MarginBottom)/(double) nY; //size of one pad ... Y
  double dx = (1-MarginLeft-MarginRight)/(double) nX; //size of one pad ... X

  xCorner[0] = MarginLeft; //start from the most left pad
  yCorner[0] = 1-MarginTop; //start from the MarginTop pad <---------- !!!

  for(int ix=1; ix<nX+1; ix++) xCorner[ix]=xCorner[ix-1]+dx; //calculate X positions of latice points (bottom-->top)
  for(int iy=1; iy<nY+1; iy++) yCorner[iy]=yCorner[iy-1]-dy; //calculate Y positions of latice points (top-->bottom)
  
  //-----------------------    
  TBox *b = new TBox();//draw box around histograms
  b->SetFillStyle(0);
  b->SetFillColor(0);

  TLatex *capt = new TLatex(); //caption written to the pad
  capt->SetTextFont(CaptionTextFont);
  capt->SetTextSize(CaptionTextSizePx);
  capt->SetTextAlign(32);

  TPad   *pp      = NULL; //pointer to the current TPad
  TGaxis *gLabels = NULL; //pointer to label pads
  
  //create latice of TPads with TBox frame around
  for(int ix=0; ix<nX;ix++){ //loop over all histograms
    for(int iy=0; iy<nY;iy++){ 
      sprintf(name,"%s_%d_%d",gPad->GetName(),ix,iy); //some dummy name
      pp = new TPad(name,name,xCorner[ix],yCorner[iy],xCorner[ix+1],yCorner[iy+1],0); //create pad
      pp->SetNumber(100*ix+iy+1);   //assign a number to it. Possible to access it via :  toppad->cd(ih);  
      pp->SetGridx(GridX);
      pp->SetGridy(GridY);
      pp->SetTickx(TicksOnX);
      pp->SetTickx(TicksOnY);
      if(logX) pp->SetLogx();
      if(logY) pp->SetLogy();
      pp->Draw();

      b->DrawBox(xCorner[ix],yCorner[iy],xCorner[ix+1],yCorner[iy+1]);//draw box arround the pad

      pp->cd();//go to the pad
    
      hDummy[ix][iy]->Draw();	// Draw the dummy    
			
      //Print captions to pads to places with the fixed relative coodrinates w.r.t. current tpad
      capt->DrawLatex( LocateCaption(CaptionX,lower_range_X[ix], upper_range_X[ix],logX),
                       LocateCaption(CaptionY,lower_range_Y[iy], upper_range_Y[iy],logY),Caption[ix][iy]);
      toppad->cd(0);//return back to the top pad
    }// iy loop    
  }//ix loop

  //--------------------------------------------------
  //Draw  Y axis labels in separate pads
  for(int iy=0; iy<nY; iy++){
    sprintf(name,"%s_%d_labelY",gPad->GetName(),iy);
    pp = new TPad(name,name,MarginLeft-xxLabelYDeltaWidth-OffsetLabelY,yCorner[nY-iy]-yyLabelYDeltaHeigt,MarginLeft-OffsetLabelY,yCorner[nY-iy-1]+yyLabelYDeltaHeigt,0);
    pp->SetNumber(10000+iy); // pp->SetFillColor(iy+12);  //Uncomment to visualize TPads with Y axis labels
    pp->Draw();  pp->cd();

    if(!logY){ sprintf(name,"B");} //linear scale 
    else{     sprintf(name,"BG");} //logarithmic scale
       
    gLabels = new TGaxis( 1., yyLabelYDeltaHeigt/(2*yyLabelYDeltaHeigt+dy), 1., (yyLabelYDeltaHeigt+dy)/(2*yyLabelYDeltaHeigt+dy),
                                lower_range_Y[nY-1-iy], upper_range_Y[nY-1-iy], NDivY,name);  //make a copy of Y TAxis

    AdjustTGaxis(gLabels,"",0,0,0,0,TextSizeLabelY,TextFontLabelY,1,0);
    gLabels->Draw();
    toppad->cd(0); //return back to the top pad
  }
 
  //--------------------------------------------------
  //Draw pads with X axis labels
  for(int ix=0; ix<nX; ix++){
    sprintf(name,"%s_%d_labelX",gPad->GetName(),ix);
    pp = new TPad(name,name,xCorner[ix]-xxLabelXDeltaWidth,yCorner[nY]-yyLabelXDeltaHeigt-OffsetLabelX,xCorner[ix+1]+xxLabelXDeltaWidth,yCorner[nY]-OffsetLabelX,0);
    pp->SetNumber(20000+ix);// pp->SetFillColor(ix+12); //uncoment to visualize the TPad with X axis label
    pp->Draw(); pp->cd(); 
 
    if(!logX){ sprintf(name,"B"); } //linear scale 
    else{     sprintf(name,"BG");} //logarithmic scale
    

    gLabels = new TGaxis(xxLabelXDeltaWidth/(2*xxLabelXDeltaWidth+dx), 1., (xxLabelXDeltaWidth+dx)/(2*xxLabelXDeltaWidth+dx),1., 
                        lower_range_X[ix], upper_range_X[ix], NDivX,name);
    AdjustTGaxis(gLabels,"",0,0,0,0,TextSizeLabelX,TextFontLabelX,1,0);//0
    gLabels->Draw();
    toppad->cd(0); //return back to the top pad
  }


  //-------------- Print tile ---------------
  toppad->cd(0);
  gLabels = new TGaxis(MarginLeft,1. - MarginTop, 1.-MarginRight,1.- MarginTop,0,1,1,"B");
  AdjustTGaxis(gLabels,Title,TextSizeTitle,TextFontTitle,-OffsetTitle,CentralizeTitle,0,0,0,0);
  gLabels->Draw();

  //-------------- Print tiles of X axes  ---------------
  if(EachColumnHasTitleX){ 
    for(int ix=0; ix<nX; ix++){
      toppad->cd(0);
      gLabels = new TGaxis(xCorner[ix], MarginBottom, xCorner[ix+1], MarginBottom, 0,1,1,"B");
                        
      AdjustTGaxis(gLabels,TitleX,TextSizeTitleX,TextFontTitleX,OffsetTitleX,CentralizeTitleX,0,0,0,1);
      gLabels->Draw();
    }
  }else{ //one single title on X
    toppad->cd(0);
    gLabels = new TGaxis(MarginLeft,MarginBottom, 1.-MarginRight,MarginBottom,0,1,1,"B");                      
    AdjustTGaxis(gLabels,TitleX,TextSizeTitleX,TextFontTitleX,OffsetTitleX,CentralizeTitleX,0,0,0,1);//0,0,0,0);
    gLabels->Draw();
  }
  //-------------- Print tiles Y axes  ---------------
  if(EachRowHasTitleY){ 
    for(int iy=0; iy<nY; iy++){
      toppad->cd(0);
      gLabels = new TGaxis(MarginLeft, yCorner[nY-iy],MarginLeft, yCorner[nY-iy-1], 0,1,1,"B");
                        
      AdjustTGaxis(gLabels,TitleY,TextSizeTitleY,TextFontTitleY,OffsetTitleY,CentralizeTitleY,0,0,0,1);
      gLabels->Draw();
    }
  }else{ //one single title on Y
    toppad->cd(0);
    gLabels = new TGaxis(MarginLeft, MarginBottom,  MarginLeft, 1.- MarginTop, 0,1,1,"B");                      

    AdjustTGaxis(gLabels,TitleY,TextSizeTitleY,TextFontTitleY,OffsetTitleY,CentralizeTitleY,0,0,0,1);
    gLabels->Draw();
  }
 
}

