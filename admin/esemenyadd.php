<?php 
session_start();
ob_start();
?>
<?php
define("DEFAULT_LOCALE", "windows-1250");
@setlocale(LC_ALL, DEFAULT_LOCALE);	
?>
<?php
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT"); // Date in the past
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); // Always modified
header("Cache-Control: private, no-store, no-cache, must-revalidate"); // HTTP/1.1 
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache"); // HTTP/1.0
?>
<?php include ("ewconfig.php") ?>
<?php include ("db.php") ?>
<?php include ("esemenyinfo.php") ?>
<?php include ("advsecu.php") ?>
<?php include ("phpmkrfn.php") ?>
<?php include ("ewupload.php") ?>
<?php
	if (!IsLoggedIn()) {
		ob_end_clean();
		header("Location: login.php");
		exit();
	}
?>
<?php

// Initialize common variables
$x_kod = NULL;
$ox_kod = NULL;
$z_kod = NULL;
$ar_x_kod = NULL;
$ari_x_kod = NULL;
$x_kodList = NULL;
$x_kodChk = NULL;
$cbo_x_kod_js = NULL;
$x_datum = NULL;
$ox_datum = NULL;
$z_datum = NULL;
$ar_x_datum = NULL;
$ari_x_datum = NULL;
$x_datumList = NULL;
$x_datumChk = NULL;
$cbo_x_datum_js = NULL;
$x_hely = NULL;
$ox_hely = NULL;
$z_hely = NULL;
$ar_x_hely = NULL;
$ari_x_hely = NULL;
$x_helyList = NULL;
$x_helyChk = NULL;
$cbo_x_hely_js = NULL;
$x_idopont = NULL;
$ox_idopont = NULL;
$z_idopont = NULL;
$ar_x_idopont = NULL;
$ari_x_idopont = NULL;
$x_idopontList = NULL;
$x_idopontChk = NULL;
$cbo_x_idopont_js = NULL;
$x_lejart = NULL;
$ox_lejart = NULL;
$z_lejart = NULL;
$ar_x_lejart = NULL;
$ari_x_lejart = NULL;
$x_lejartList = NULL;
$x_lejartChk = NULL;
$cbo_x_lejart_js = NULL;
$x_kepek = NULL;
$ox_kepek = NULL;
$z_kepek = NULL;
$ar_x_kepek = NULL;
$ari_x_kepek = NULL;
$x_kepekList = NULL;
$x_kepekChk = NULL;
$cbo_x_kepek_js = NULL;
?>
<?php

// Load key from QueryString
$bCopy = true;
$x_kod = @$_GET["kod"];
if (($x_kod == "") || (is_null($x_kod))) $bCopy = false;

// Get action
$sAction = @$_POST["a_add"];
if (($sAction == "") || ((is_null($sAction)))) {
	if ($bCopy) {
		$sAction = "C"; // Copy record
	} else {
		$sAction = "I"; // Display blank record
	}
} else {

	// Get fields from form
	$x_kod = @$_POST["x_kod"];
	$x_datum = @$_POST["x_datum"];
	$x_hely = @$_POST["x_hely"];
	$x_idopont = @$_POST["x_idopont"];
	$x_lejart = @$_POST["x_lejart"];
	$x_kepek = @$_POST["x_kepek"];
}
$conn = phpmkr_db_connect(HOST, USER, PASS, DB, PORT);
switch ($sAction) {
	case "C": // Copy record
		if (!LoadData($conn)) { // Load record
			$_SESSION[ewSessionMessage] = "Nem találtam rekordokat";
			phpmkr_db_close($conn);
			ob_end_clean();
			header("Location: esemenylist.php");
			exit();
		}
		break;
	case "A": // Add
		if (AddData($conn)) { // Add new record
			$_SESSION[ewSessionMessage] = "Sikeres adatrögzítés";
			phpmkr_db_close($conn);
			ob_end_clean();
			header("Location: esemenylist.php");
			exit();
		}
		break;
}
?>
<?php include ("header.php") ?>
<script type="text/javascript">
<!--
EW_LookupFn = "ewlookup.php"; // ewlookup file name
EW_AddOptFn = "ewaddopt.php"; // ewaddopt.php file name
EW_MultiPagePage = "Oldal"; // multi-page Page Text
EW_MultiPageOf = "a(z)"; // multi-page Of Text

//-->
</script>
<script type="text/javascript" src="ewp.js"></script>
<script type="text/javascript">
<!--
EW_dateSep = "/"; // set date separator	

//-->
</script>
<script type="text/javascript">
<!--
function EW_checkMyForm(EW_this) {
if (EW_this.x_datum && !EW_hasValue(EW_this.x_datum, "TEXT" )) {
	if (!EW_onError(EW_this, EW_this.x_datum, "TEXT", "Kérlek tölts ki a kötelezõ mezõket - Dátum"))
		return false;
}
if (EW_this.x_datum && !EW_checkdate(EW_this.x_datum.value)) {
	if (!EW_onError(EW_this, EW_this.x_datum, "TEXT", "Hibás dáum formátum = yyyy/mm/dd - Dátum"))
		return false; 
}
if (EW_this.x_hely && !EW_hasValue(EW_this.x_hely, "TEXT" )) {
	if (!EW_onError(EW_this, EW_this.x_hely, "TEXT", "Kérlek tölts ki a kötelezõ mezõket - Hely"))
		return false;
}
if (EW_this.x_lejart && !EW_hasValue(EW_this.x_lejart, "SELECT" )) {
	if (!EW_onError(EW_this, EW_this.x_lejart, "SELECT", "Kérlek tölts ki a kötelezõ mezõket - Lejárt"))
		return false;
}
return true;
}

//-->
</script>
<script type="text/javascript">
<!--
	var EW_DHTMLEditors = [];

//-->
</script>
<link rel="stylesheet" type="text/css" media="all" href="calendar/calendar-win2k-1.css" title="win2k-1" />
<script type="text/javascript" src="calendar/calendar.js"></script>
<script type="text/javascript" src="calendar/lang/calendar-en.js"></script>
<script type="text/javascript" src="calendar/calendar-setup.js"></script>
<p><span class="phpmaker">Hozzáadás Tábla: esemeny<br><br><a href="esemenylist.php">Vissza a listára</a></span></p>
<form name="fesemenyadd" id="fesemenyadd" action="esemenyadd.php" method="post" onSubmit="return EW_checkMyForm(this);">
<p>
<input type="hidden" name="a_add" value="A">
<?php
if (@$_SESSION[ewSessionMessage] <> "") {
?>
<p><span class="ewmsg"><?php echo $_SESSION[ewSessionMessage] ?></span></p>
<?php
	$_SESSION[ewSessionMessage] = ""; // Clear message
}
?>
<table class="ewTable">
	<tr id="r_datum">
		<td class="ewTableHeader"><span>Dátum<span class='ewmsg'>&nbsp;*</span></span></td>
		<td class="ewTableAltRow"><span id="cb_x_datum">
<input type="text" name="x_datum" id="x_datum" value="<?php echo FormatDateTime(@$x_datum,5); ?>">
&nbsp;<img src="images/ew_calendar.gif" id="cx_datum" alt="Pick a Date" style="cursor:pointer;cursor:hand;">
<script type="text/javascript">
Calendar.setup(
{
inputField : "x_datum", // ID of the input field
ifFormat : "%Y/%m/%d", // the date format
button : "cx_datum" // ID of the button
}
);
</script>
</span></td>
	</tr>
	<tr id="r_hely">
		<td class="ewTableHeader"><span>Hely<span class='ewmsg'>&nbsp;*</span></span></td>
		<td class="ewTableAltRow"><span id="cb_x_hely">
<input type="text" name="x_hely" id="x_hely" size="60" maxlength="80" value="<?php echo htmlspecialchars(@$x_hely) ?>">
</span></td>
	</tr>
	<tr id="r_idopont">
		<td class="ewTableHeader"><span>Idopont</span></td>
		<td class="ewTableAltRow"><span id="cb_x_idopont">
<input type="text" name="x_idopont" id="x_idopont" size="20" maxlength="20" value="<?php echo htmlspecialchars(@$x_idopont) ?>">
</span></td>
	</tr>
	<tr id="r_lejart">
		<td class="ewTableHeader"><span>Lejárt<span class='ewmsg'>&nbsp;*</span></span></td>
		<td class="ewTableAltRow"><span id="cb_x_lejart">
<?php if (!(!is_null($x_lejart)) || ($x_lejart == "")) { $x_lejart = "n";} // Set default value ?>
<?php
$x_lejartList = "<select id='x_lejart' name='x_lejart'>";
$x_lejartList .= "<option value=''>Kérlek válassz</option>";
	$x_lejartList .= "<option value=\"i\"";
	if (@$x_lejart == "i") {
		$x_lejartList .= " selected";
	}
	$x_lejartList .= ">" . "igen" . "</option>";
	$x_lejartList .= "<option value=\"n\"";
	if (@$x_lejart == "n") {
		$x_lejartList .= " selected";
	}
	$x_lejartList .= ">" . "nem" . "</option>";
$x_lejartList .= "</select>";
echo $x_lejartList;
?>
</span></td>
	</tr>
	<tr id="r_kepek">
		<td class="ewTableHeader"><span>képek mappa</span></td>
		<td class="ewTableAltRow"><span id="cb_x_kepek">
<input type="text" name="x_kepek" id="x_kepek" size="20" maxlength="20" value="<?php echo htmlspecialchars(@$x_kepek) ?>">
</span></td>
	</tr>
</table>
<p>
<input type="submit" name="btnAction" id="btnAction" value="Rögzít">
</form>
<?php include ("footer.php") ?>
<?php
phpmkr_db_close($conn);
?>
<?php

//-------------------------------------------------------------------------------
// Function LoadData
// - Variables setup: field variables

function LoadData($conn)
{
	global $x_kod;
	$sFilter = ewSqlKeyWhere;
	if (!is_numeric($x_kod)) return false;
	$x_kod =  (get_magic_quotes_gpc()) ? stripslashes($x_kod) : $x_kod;
	$sFilter = str_replace("@kod", AdjustSql($x_kod), $sFilter); // Replace key value
	$sSql = ewBuildSql(ewSqlSelect, ewSqlWhere, ewSqlGroupBy, ewSqlHaving, ewSqlOrderBy, $sFilter, "");
	$rs = phpmkr_query($sSql,$conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSql);
	if (phpmkr_num_rows($rs) == 0) {
		$bLoadData = false;
	} else {
		$bLoadData = true;
		$row = phpmkr_fetch_array($rs);

		// Get the field contents
		$GLOBALS["x_kod"] = $row["kod"];
		$GLOBALS["x_datum"] = $row["datum"];
		$GLOBALS["x_hely"] = $row["hely"];
		$GLOBALS["x_idopont"] = $row["idopont"];
		$GLOBALS["x_lejart"] = $row["lejart"];
		$GLOBALS["x_kepek"] = $row["kepek"];
	}
	phpmkr_free_result($rs);
	return $bLoadData;
}
?>
<?php

//-------------------------------------------------------------------------------
// Function AddData
// - Add Data
// - Variables used: field variables

function AddData($conn)
{
	global $x_kod;
	$sFilter = ewSqlKeyWhere;

	// Check for duplicate key
	$bCheckKey = true;
	if ((@$x_kod == "") || (is_null(@$x_kod))) {
		$bCheckKey = false;
	} else {
		$sFilter = str_replace("@kod", AdjustSql($x_kod), $sFilter); // Replace key value
	}
	if ($bCheckKey) {
		$sSqlChk = ewBuildSql(ewSqlSelect, ewSqlWhere, ewSqlGroupBy, ewSqlHaving, ewSqlOrderBy, $sFilter, "");
		$rsChk = phpmkr_query($sSqlChk, $conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSqlChk);
		if (phpmkr_num_rows($rsChk) > 0) {
			$_SESSION[ewSessionMessage] = "Duplikált érték";
			phpmkr_free_result($rsChk);
			return false;
		}
		phpmkr_free_result($rsChk);
	}

	// Field datum
	$theValue = ($GLOBALS["x_datum"] != "") ? " '" . ConvertDateToMysqlFormat($GLOBALS["x_datum"]) . "'" : "Null";
	$fieldList["`datum`"] = $theValue;

	// Field hely
	$theValue = (!get_magic_quotes_gpc()) ? addslashes($GLOBALS["x_hely"]) : $GLOBALS["x_hely"]; 
	$theValue = ($theValue != "") ? " '" . $theValue . "'" : "NULL";
	$fieldList["`hely`"] = $theValue;

	// Field idopont
	$theValue = (!get_magic_quotes_gpc()) ? addslashes($GLOBALS["x_idopont"]) : $GLOBALS["x_idopont"]; 
	$theValue = ($theValue != "") ? " '" . $theValue . "'" : "NULL";
	$fieldList["`idopont`"] = $theValue;

	// Field lejart
	$theValue = (!get_magic_quotes_gpc()) ? addslashes($GLOBALS["x_lejart"]) : $GLOBALS["x_lejart"]; 
	$theValue = ($theValue != "") ? " '" . $theValue . "'" : "NULL";
	$fieldList["`lejart`"] = $theValue;

	// Field kepek
	$theValue = (!get_magic_quotes_gpc()) ? addslashes($GLOBALS["x_kepek"]) : $GLOBALS["x_kepek"]; 
	$theValue = ($theValue != "") ? " '" . $theValue . "'" : "NULL";
	$fieldList["`kepek`"] = $theValue;

	// Insert
	$sSql = "INSERT INTO `esemeny` (";
	$sSql .= implode(",", array_keys($fieldList));
	$sSql .= ") VALUES (";
	$sSql .= implode(",", array_values($fieldList));
	$sSql .= ")";

	// Inserting event
	if (Recordset_Inserting($fieldList)) {
		phpmkr_query($sSql, $conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSql);
		$fieldList["`kod`"] = phpmkr_insert_id($conn);
		$result = (phpmkr_affected_rows($conn) > 0);

		// Inserted event
		if ($result) Recordset_Inserted($fieldList);
	} else {
		$result = false;
	}
	return $result;
}

// Inserting event
function Recordset_Inserting($newrs)
{

	// Enter your customized codes here
	return true;
}

// Inserted event
function Recordset_Inserted($newrs)
{
	$table = "esemeny";
}
?>
