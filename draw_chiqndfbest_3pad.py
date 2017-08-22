import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.ticker as plticker
import ROOT

marker = ["o","s","D","*"]; #https://matplotlib.org/api/markers_api.html
color = ["black","blue","red","green","orange","yellow"];

def TGraphErrorsToNumpy(gr):
	n = gr.GetN();
	x = np.empty(n);
	y = np.empty(n);
	xerr = np.empty(n);
	yerr = np.empty(n);

	a = ROOT.Double(0);
	b = ROOT.Double(0);
	for i in range(0,n):
		gr.GetPoint(i,a,b);
		x[i] = float(a);
		y[i] = float(b);
		xerr[i] = gr.GetErrorX(i);
		yerr[i] = gr.GetErrorY(i);

	return x,y,xerr,yerr;

p,ax = plt.subplots(1,3,sharex=False,sharey=True,figsize=(15,5)); #create a 1x2 canvas of aspect 2/1 with shared y-axis
p.subplots_adjust(wspace=0.0,hspace=0.0); #remove the spacing between the pads

f = ROOT.TFile("chisquaredndf_results.root");

ax[0].set_yscale("log");
ax[0].set_ylim([0.4e-1,4e2]); #Custom y-limits. Setting to ax[0] is enough, since the sharey=True above

#draw on the first pad
for i in range(0,2):
	tgraph = f.Get("gr_EKRT_SC_parm{iset:02d}".format(iset=i)); #read the TGraphErrors
	title = tgraph.GetTitle().replace(" ("," $(").replace("#eta","\eta")+"$"; #read the title and it to latex format
	x,y,xerr,yerr = TGraphErrorsToNumpy(tgraph);
	ax[0].errorbar(x,y,yerr,linestyle="-",fmt=marker[i],color=color[i],label="EKRT+Viscous Hydro, "+title);

	x,y,xerr,yerr = TGraphErrorsToNumpy(f.Get("gr_EKRT_NSC_parm{iset:02d}".format(iset=i)));
	ax[1].errorbar(x,y,yerr,linestyle="--",fmt=marker[i],color=color[i],mfc="none"); #mfc="none" -> open marker

tgraph = f.Get("gr_VISH_SC_{iset:02d}{ieta:02d}_chisq".format(iset=0,ieta=0));
title = tgraph.GetTitle().replace("#eta","$\eta")+"$";
x,y,xerr,yerr = TGraphErrorsToNumpy(tgraph);
ax[0].errorbar(x,y,yerr,linestyle="-",fmt=marker[2],color=color[2],label="VISH2+1, "+title);

x,y,xerr,yerr = TGraphErrorsToNumpy(f.Get("gr_VISH_NSC_{iset:02d}{ieta:02d}_chisq".format(iset=0,ieta=0)));
ax[1].errorbar(x,y,yerr,linestyle="--",fmt=marker[2],color=color[2],mfc="none");

tgraph = f.Get("gr_AMPT_SC_ {iset:d}_chisq".format(iset=1));
title = tgraph.GetTitle();
x,y,xerr,yerr = TGraphErrorsToNumpy(tgraph);
ax[0].errorbar(x,y,yerr,linestyle="-",fmt=marker[3],color=color[3],label="AMPT, "+title);

x,y,xerr,yerr = TGraphErrorsToNumpy(f.Get("gr_AMPT_NSC_ {iset:d}_chisq".format(iset=1)));
ax[1].errorbar(x,y,yerr,linestyle="--",fmt=marker[3],color=color[3],mfc="none");

#add text to first pad
#ax[0].text(0.6,0.1,"N = 4, Centrality 10 - 50%",
#	horizontalalignment='center',verticalalignment='center',transform=ax[0].transAxes,size=12);
ax[0].text(0.5,0.12,"ALICE 10-50% Pb-Pb $\sqrt{s_{\mathrm{NN}}}$ = 2.76 TeV",horizontalalignment='center',verticalalignment='center',transform=ax[0].transAxes,size=10);
ax[0].text(0.5,0.06,"$N_{\mathrm{dof}}$ = 4",horizontalalignment='center',verticalalignment='center',transform=ax[0].transAxes,size=10);
ax[0].set_xticklabels(["","(3,2)","(4,2)","(5,2)","(5,3)","(4,3)"],fontsize = 10.4,rotation=45);
ax[0].set_yticklabels(["","$10^{-2}$","$10^{-1}$","$1$","$10$","$10^2$","$10^3$"],fontweight='bold',fontsize = 13);
ax[0].legend(frameon=False,prop={'size':9},loc="center",
	handletextpad=0.1,bbox_to_anchor=(0.45,0.87)); #title="Legend"

#add text to 2nd pad
ax[1].set_xticklabels(["","(3,2)","(4,2)","(5,2)","(5,3)","(4,3)"],fontsize = 10.4,rotation=45);

f.Close();
f = ROOT.TFile("chisquaredndf_vn_results.root");

#draw on the second pad
for i in range(0,2):
	x,y,xerr,yerr = TGraphErrorsToNumpy(f.Get("gr_EKRT_vn_parm{iset:02d}_chisq".format(iset=i)));
	ax[2].errorbar(x,y,yerr,linestyle="-",fmt=marker[i],color=color[i]);#,label="a"+str(i));

x,y,xerr,yerr = TGraphErrorsToNumpy(f.Get("gr_VISH_vn_{iset:02d}{ieta:02d}_chisq".format(iset=0,ieta=0)));
ax[2].errorbar(x,y,yerr,linestyle="-",fmt=marker[2],color=color[2]);#,label="b");
ax[2].set_xticklabels(["","$v_2$","$v_3$","$v_4$"],fontsize = 14,fontweight='bold');

x,y,xerr,yerr = TGraphErrorsToNumpy(f.Get("gr_AMPT_vn_ {iset:d}_chisq".format(iset=1)));
ax[2].errorbar(x,y,yerr,linestyle="-",fmt=marker[3],color=color[3]);#,label="b");

f.Close();

#set common parameters for both pads
for i,a in enumerate(ax):
	a.tick_params(which="major",direction="in",length=8.0);
	a.tick_params(which="minor",direction="in",length=4.0);

	a.xaxis.set_major_locator(plticker.MultipleLocator(1.0)); #set the x tick interval to mimic root style
	#a.xaxis.set_minor_locator(plticker.MultipleLocator(0.1));

	#a.text(0.5,-0.1,["x1","x2"][i],horizontalalignment='center',verticalalignment='center',transform=a.transAxes,size=16);
	a.text(0.93,0.93,["(a)","(b)","(c)"][i],horizontalalignment='center',verticalalignment='center',transform=a.transAxes,size=12);
	a.text(0.6,0.7,["SC($m$,$n$)","NSC($m$,$n$)","$v_n$ (n=2,3 and 4)"][i],horizontalalignment='center',verticalalignment='center',transform=a.transAxes,size=13);

#Manually place the axis labels for shared axes. There might be a better way..
#p.text(0.46,0.02,"x-axis",size=16);
p.text(0.07,0.5,"$\chi^2/N_{\mathrm{dof}}$",rotation="vertical",size=17);

#plt.savefig("figs/chisq_bestfits_3pad_wo_ampt.eps",bbox_inches="tight");
plt.savefig("figs/Fig7_chisqndf_bestfits_3pad.eps",bbox_inches="tight");
plt.show();
