<?php

$send = (empty($HTTP_GET_VARS["send"]) ?
$HTTP_POST_VARS["send"] : $HTTP_GET_VARS["send"]);


// Adatok
$sz1 = (empty($HTTP_GET_VARS["sz1"]) ?
$HTTP_POST_VARS["sz1"] : $HTTP_GET_VARS["sz1"]);
$sz2 = (empty($HTTP_GET_VARS["sz2"]) ?
$HTTP_POST_VARS["sz2"] : $HTTP_GET_VARS["sz2"]);
$sz4 = (empty($HTTP_GET_VARS["sz4"]) ?
$HTTP_POST_VARS["sz4"] : $HTTP_GET_VARS["sz4"]);
$sz5 = (empty($HTTP_GET_VARS["sz5"]) ?
$HTTP_POST_VARS["sz5"] : $HTTP_GET_VARS["sz5"]);
$sz6 = (empty($HTTP_GET_VARS["sz6"]) ?
$HTTP_POST_VARS["sz6"] : $HTTP_GET_VARS["sz6"]);
$sz7 = (empty($HTTP_GET_VARS["sz7"]) ?
$HTTP_POST_VARS["sz7"] : $HTTP_GET_VARS["sz7"]);
$sz8 = (empty($HTTP_GET_VARS["sz8"]) ?
$HTTP_POST_VARS["sz8"] : $HTTP_GET_VARS["sz8"]);
$sz9 = (empty($HTTP_GET_VARS["sz9"]) ?
$HTTP_POST_VARS["sz9"] : $HTTP_GET_VARS["sz9"]);
$sz10 = (empty($HTTP_GET_VARS["sz10"]) ?
$HTTP_POST_VARS["sz10"] : $HTTP_GET_VARS["sz10"]);
$sz12 = (empty($HTTP_GET_VARS["sz12"]) ?
$HTTP_POST_VARS["sz12"] : $HTTP_GET_VARS["sz12"]);
$sz13 = (empty($HTTP_GET_VARS["sz13"]) ?
$HTTP_POST_VARS["sz13"] : $HTTP_GET_VARS["sz13"]);
$sz14 = (empty($HTTP_GET_VARS["sz14"]) ?
$HTTP_POST_VARS["sz14"] : $HTTP_GET_VARS["sz14"]);
$sz15 = (empty($HTTP_GET_VARS["sz15"]) ?
$HTTP_POST_VARS["sz15"] : $HTTP_GET_VARS["sz15"]);
$sz16 = (empty($HTTP_GET_VARS["sz16"]) ?
$HTTP_POST_VARS["sz16"] : $HTTP_GET_VARS["sz16"]);

$sz18 = (empty($HTTP_GET_VARS["sz18"]) ?
$HTTP_POST_VARS["sz18"] : $HTTP_GET_VARS["sz18"]);
$sz19 = (empty($HTTP_GET_VARS["sz19"]) ?
$HTTP_POST_VARS["sz19"] : $HTTP_GET_VARS["sz19"]);
$sz20 = (empty($HTTP_GET_VARS["sz20"]) ?
$HTTP_POST_VARS["sz20"] : $HTTP_GET_VARS["sz20"]);
$sz21 = (empty($HTTP_GET_VARS["sz21"]) ?
$HTTP_POST_VARS["sz21"] : $HTTP_GET_VARS["sz21"]);
$sz22 = (empty($HTTP_GET_VARS["sz22"]) ?
$HTTP_POST_VARS["sz22"] : $HTTP_GET_VARS["sz22"]);


if ($send <> "") {

if ($sz1 && $sz2 ) {
	$send = "ok";

	$emailto = "natural-horsemanship@mgy.hu";
	$emailcc = "kaczorzsolt@tbbdesign.hu";
	include("email02.inc.php");
	$feedback = "<font color=#FF0000 >Köszönjük kérdésed!</font>";

} else {
	$send = "";
	$feedback = "<font color=#FF0000 >Kérjük, minden mezõt töltsön ki. Köszönjük!</font>";
}
				}







 

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>::: mgy :::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="css/all.css" rel="stylesheet" type="text/css">

</script>
<style type="text/css">
..cim {
	font-family : verdana, helvetica, arial;
	font-size : 12px;
	color : #ffffff;
	text-decoration : none;
	font-weight: bold;
}
td {
	font-family : verdana, helvetica, arial;
	font-size : 10px;
	color : #ffffff;
	text-decoration : none;
}
input, select, textarea {
	font-family : Times New Roman, Times, serif;
	font-size : 13px;
	color : #222222;
	text-decoration : none;
	border-style: dot; 
	border-width=1px; 
	background-color: #ffffff; 
	border-color: #E6E6E6;
}
</style>
</head>

<body bgcolor="#F0F0F0" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
<div align="center">
  <table width="195" height="115" border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td width="195" height="115" valign="top"><table width="195" height="115" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="195" valign="top"><table width="472" border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="472" height="22" align="center" valign="top" class="szoveg3"><?=$feedback;?>
&nbsp;</td>
              </tr>
              <form name="ff" method="post" action="kerdes.php" >
                <input type="hidden" name="send" value="ok">
                <tr>
                  <td height="62" valign="top"><div align="center">
                    <table width="398" border="0" cellspacing="0" cellpadding="0">
                      <tr valign="middle">
                        <td width="110" height="27"><table width="108" height="19" border="0" cellpadding="0" cellspacing="0">
                            <tr>
                              <td width="108"><div align="left" class="szoveg4"><img src="email.jpg" width="110" height="20"></div>
                              </td>
                            </tr>
                          </table>
                        </td>
                        <td width="288" height="27" class="szoveg3"><INPUT name=sz1 class="inputtype4" value="<?=$sz1;?>" size=25 >
                        </td>
                      </tr>
                      <tr valign="middle">
                        <td height="28" valign="top"><table width="108" height="19" border="0" cellpadding="0" cellspacing="0">
                            <tr>
                              <td width="108"><div align="left" class="szoveg4"><img src="kerdes.jpg" width="110" height="20"></div>
                              </td>
                            </tr>
                          </table>
                        </td>
                        <td height="28" class="szoveg3"><textarea name="sz2" cols="55" rows="5" class="inputtype4"><?=$sz2;?>
                        </textarea>
                        </td>
                      </tr>
                    </table>
                  </div></td>
                </tr>
                <tr>
                  <td height="33" valign="middle"><div align="center">
                      <table width="173" border="0" cellspacing="0" cellpadding="0">
                        <tr>
                          <td width="71" height="26">&nbsp;</td>
                          <td width="102"><input name="image" type=image value=Submit src=ok.jpg alt='' width="35" height="18">
</td>
                        </tr>
                      </table>
                  </div>
                  </td>
                </tr>
              </form>
            </table></td>
          </tr>
        </table>
      </td>
    </tr>
  </table>
</div>
</body>
</html>
