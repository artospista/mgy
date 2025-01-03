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
$nStartRec = 0;
$nStopRec = 0;
$nTotalRecs = 0;
$nRecCount = 0;
$nRecActual = 0;
$sKeyMaster = "";
$sDbWhereMaster = "";
$sSrchAdvanced = "";
$psearch = "";
$psearchtype = "";
$sDbWhereDetail = "";
$sSrchBasic = "";
$sSrchWhere = "";
$sDbWhere = "";
$sOrderBy = "";
$sSqlMaster = "";
$sListTrJs = "";
$bEditRow = "";
$nEditRowCnt = "";
$sDeleteConfirmMsg = "";
$nDisplayRecs = "20";
$nRecRange = 10;

// Open connection to the database
$conn = phpmkr_db_connect(HOST, USER, PASS, DB, PORT);

// Handle reset command
ResetCmd();

// Build filter condition
$sDbWhere = "";
if ($sDbWhereDetail <> "") {
	if ($sDbWhere <> "") $sDbWhere .= " AND ";
	$sDbWhere .= "(" . $sDbWhereDetail . ")";
}
if ($sSrchWhere <> "") {
	if ($sDbWhere <> "") $sDbWhere .= " AND ";
	$sDbWhere .= "(" . $sSrchWhere . ")";
}

// Set up sorting order
$sOrderBy = "";
SetUpSortOrder();
$sSql = ewBuildSql(ewSqlSelect, ewSqlWhere, ewSqlGroupBy, ewSqlHaving, ewSqlOrderBy, $sDbWhere, $sOrderBy);

// echo $sSql . "<br>"; // Uncomment to show SQL for debugging
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
var firstrowoffset = 1; // first data row start at
var tablename = 'ewlistmain'; // table name
var lastrowoffset = 0; // footer row
var usecss = true; // use css
var rowclass = 'ewTableRow'; // row class
var rowaltclass = 'ewTableAltRow'; // row alternate class
var rowmoverclass = 'ewTableHighlightRow'; // row mouse over class
var rowselectedclass = 'ewTableSelectRow'; // row selected class
var roweditclass = 'ewTableEditRow'; // row edit class
var rowcolor = '#FFFFFF'; // row color
var rowaltcolor = '#EDEDED'; // row alternate color
var rowmovercolor = '#FF3333'; // row mouse over color
var rowselectedcolor = '#CCFFFF'; // row selected color
var roweditcolor = '#FFFF99'; // row edit color

//-->
</script>
<script type="text/javascript">
<!--
	var EW_DHTMLEditors = [];

//-->
</script>
<script type="text/javascript">
<!--
function EW_selectKey(elem) {
	var f = elem.form;	
	if (!f.elements["key_d[]"]) return;
	if (f.elements["key_d[]"][0]) {
		for (var i=0; i<f.elements["key_d[]"].length; i++)
			f.elements["key_d[]"][i].checked = elem.checked;	
	} else {
		f.elements["key_d[]"].checked = elem.checked;	
	}
	if (f.elements["checkall"])
	{
		if (f.elements["checkall"][0])
		{
			for (var i = 0; i<f.elements["checkall"].length; i++)
				f.elements["checkall"][i].checked = elem.checked;
		} else {
			f.elements["checkall"].checked = elem.checked;
		}
	}
	ew_clickall(elem);
}
function EW_selected(elem) {
	var f = elem.form;	
	if (!f.elements["key_d[]"]) return false;
	if (f.elements["key_d[]"][0]) {
		for (var i=0; i<f.elements["key_d[]"].length; i++)
			if (f.elements["key_d[]"][i].checked) return true;
	} else {
		return f.elements["key_d[]"].checked;
	}
	return false;
}

//-->
</script>
<?php

// Set up recordset
$rs = phpmkr_query($sSql, $conn) or die("Query-t nem tudtam futtatni" . __LINE__ . ": " . phpmkr_error($conn) . '<br>SQL: ' . $sSql);
$nTotalRecs = phpmkr_num_rows($rs);
if ($nDisplayRecs <= 0) { // Display all records
	$nDisplayRecs = $nTotalRecs;
}
$nStartRec = 1;
SetUpStartRec(); // Set up start record position
?>
<p><span class="phpmaker">Tábla: esemeny
</span></p>
<table class="ewListAdd">
	<tr>
		<td><span class="phpmaker"><a href="esemenyadd.php">Hozzáad</a></span></td>
	</tr>
</table>
<p>
<?php
if (@$_SESSION[ewSessionMessage] <> "") {
?>
<p><span class="ewmsg"><?php echo $_SESSION[ewSessionMessage]; ?></span></p>
<?php
	$_SESSION[ewSessionMessage] = ""; // Clear message
}
?>
<form action="esemenylist.php" name="ewpagerform" id="ewpagerform">
<table>
	<tr>
		<td nowrap>
<?php
if ($nTotalRecs > 0) {
	$rsEof = ($nTotalRecs < ($nStartRec + $nDisplayRecs));
	$PrevStart = $nStartRec - $nDisplayRecs;
	if ($PrevStart < 1) { $PrevStart = 1; }
	$NextStart = $nStartRec + $nDisplayRecs;
	if ($NextStart > $nTotalRecs) { $NextStart = $nStartRec ; }
	$LastStart = intval(($nTotalRecs-1)/$nDisplayRecs)*$nDisplayRecs+1;
	?>
	<table border="0" cellspacing="0" cellpadding="0"><tr><td><span class="phpmaker">Oldal&nbsp;</span></td>
<!--first page button-->
	<?php if ($nStartRec == 1) { ?>
	<td><img src="images/firstdisab.gif" alt="Elsõ" width="16" height="16" border="0"></td>
	<?php } else { ?>
	<td><a href="esemenylist.php?start=1"><img src="images/first.gif" alt="Elsõ" width="16" height="16" border="0"></a></td>
	<?php } ?>
<!--previous page button-->
	<?php if ($PrevStart == $nStartRec) { ?>
	<td><img src="images/prevdisab.gif" alt="Elõzõ" width="16" height="16" border="0"></td>
	<?php } else { ?>
	<td><a href="esemenylist.php?start=<?php echo $PrevStart; ?>"><img src="images/prev.gif" alt="Elõzõ" width="16" height="16" border="0"></a></td>
	<?php } ?>
<!--current page number-->
	<td><input type="text" name="pageno" value="<?php echo intval(($nStartRec-1)/$nDisplayRecs+1); ?>" size="4"></td>
<!--next page button-->
	<?php if ($NextStart == $nStartRec) { ?>
	<td><img src="images/nextdisab.gif" alt="Következõ" width="16" height="16" border="0"></td>
	<?php } else { ?>
	<td><a href="esemenylist.php?start=<?php echo $NextStart; ?>"><img src="images/next.gif" alt="Következõ" width="16" height="16" border="0"></a></td>
	<?php  } ?>
<!--last page button-->
	<?php if ($LastStart == $nStartRec) { ?>
	<td><img src="images/lastdisab.gif" alt="Utolsó" width="16" height="16" border="0"></td>
	<?php } else { ?>
	<td><a href="esemenylist.php?start=<?php echo $LastStart; ?>"><img src="images/last.gif" alt="Utolsó" width="16" height="16" border="0"></a></td>
	<?php } ?>
	<td><span class="phpmaker">&nbsp;a(z) <?php echo intval(($nTotalRecs-1)/$nDisplayRecs+1);?></span></td>
	</tr></table>
	<?php if ($nStartRec > $nTotalRecs) { $nStartRec = $nTotalRecs; }
	$nStopRec = $nStartRec + $nDisplayRecs - 1;
	$nRecCount = $nTotalRecs - 1;
	if ($rsEof) { $nRecCount = $nTotalRecs; }
	if ($nStopRec > $nRecCount) { $nStopRec = $nRecCount; } ?>
	<span class="phpmaker">Rekordok <?php echo $nStartRec; ?> tól <?php echo $nStopRec; ?> a(z) <?php echo $nTotalRecs; ?></span>
<?php } else { ?>
	<?php if ($sSrchWhere == "0=101") { ?>
	<span class="phpmaker"></span>
	<?php } else { ?>
	<span class="phpmaker">Nem találtam rekordokat</span>
	<?php } ?>
<?php } ?>
		</td>
	</tr>
</table>
</form>
<?php if ($nTotalRecs > 0)  { ?>
<form method="post">
<table id="ewlistmain" class="ewTable">
	<!-- Table header -->
	<tr class="ewTableHeader">
		<td valign="top" style="width: 8%;"><span>
	<a href="esemenylist.php?order=<?php echo urlencode("datum"); ?>">
	Dátum<?php if (@$_SESSION[ewSessionTblSort . "_x_datum"] == "ASC") { ?><img src="images/sortup.gif" width="10" height="9" border="0"><?php } elseif (@$_SESSION[ewSessionTblSort . "_x_datum"] == "DESC") { ?><img src="images/sortdown.gif" width="10" height="9" border="0"><?php } ?>
	</a>
		</span></td>
		<td valign="top" style="width: 40%;"><span>
	<a href="esemenylist.php?order=<?php echo urlencode("hely"); ?>">
	Hely<?php if (@$_SESSION[ewSessionTblSort . "_x_hely"] == "ASC") { ?><img src="images/sortup.gif" width="10" height="9" border="0"><?php } elseif (@$_SESSION[ewSessionTblSort . "_x_hely"] == "DESC") { ?><img src="images/sortdown.gif" width="10" height="9" border="0"><?php } ?>
	</a>
		</span></td>
		<td valign="top" style="width: 6%;"><span>
	<a href="esemenylist.php?order=<?php echo urlencode("idopont"); ?>">
	Idopont<?php if (@$_SESSION[ewSessionTblSort . "_x_idopont"] == "ASC") { ?><img src="images/sortup.gif" width="10" height="9" border="0"><?php } elseif (@$_SESSION[ewSessionTblSort . "_x_idopont"] == "DESC") { ?><img src="images/sortdown.gif" width="10" height="9" border="0"><?php } ?>
	</a>
		</span></td>
		<td valign="top" style="width: 6%;"><span>
	<a href="esemenylist.php?order=<?php echo urlencode("lejart"); ?>">
	Lejárt<?php if (@$_SESSION[ewSessionTblSort . "_x_lejart"] == "ASC") { ?><img src="images/sortup.gif" width="10" height="9" border="0"><?php } elseif (@$_SESSION[ewSessionTblSort . "_x_lejart"] == "DESC") { ?><img src="images/sortdown.gif" width="10" height="9" border="0"><?php } ?>
	</a>
		</span></td>
		<td valign="top" style="width: 12%;"><span>
	<a href="esemenylist.php?order=<?php echo urlencode("kepek"); ?>">
	képek mappa<?php if (@$_SESSION[ewSessionTblSort . "_x_kepek"] == "ASC") { ?><img src="images/sortup.gif" width="10" height="9" border="0"><?php } elseif (@$_SESSION[ewSessionTblSort . "_x_kepek"] == "DESC") { ?><img src="images/sortdown.gif" width="10" height="9" border="0"><?php } ?>
	</a>
		</span></td>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td><input type="checkbox" name="checkall" class="phpmaker" onClick="EW_selectKey(this);"></td>
	</tr>
<?php

// Avoid starting record > total records
if ($nStartRec > $nTotalRecs) {
	$nStartRec = $nTotalRecs;
}

// Set the last record to display
$nStopRec = $nStartRec + $nDisplayRecs - 1;

// Move to the first record
$nRecCount = $nStartRec - 1;
if (phpmkr_num_rows($rs) > 0) {
	phpmkr_data_seek($rs, $nStartRec -1);
}
$nRecActual = 0;
while (($row = @phpmkr_fetch_array($rs)) && ($nRecCount < $nStopRec)) {
	$nRecCount = $nRecCount + 1;
	if ($nRecCount >= $nStartRec) {
		$nRecActual++;

		// Set row color
		$sItemRowClass = " class=\"ewTableRow\"";
		$sListTrJs = " onmouseover='ew_mouseover(this);' onmouseout='ew_mouseout(this);' onclick='ew_click(this);'";

		// Display alternate color for rows
		if ($nRecCount % 2 <> 1) {
			$sItemRowClass = " class=\"ewTableAltRow\"";
		}
		$x_kod = $row["kod"];
		$x_datum = $row["datum"];
		$x_hely = $row["hely"];
		$x_idopont = $row["idopont"];
		$x_lejart = $row["lejart"];
		$x_kepek = $row["kepek"];
?>
	<!-- Table body -->
	<tr<?php echo $sItemRowClass; ?><?php echo $sListTrJs; ?>>
		<!-- datum -->
		<td style="width: 8%;"><span>
<?php echo FormatDateTime($x_datum,5); ?>
</span></td>
		<!-- hely -->
		<td style="width: 40%;"><span>
<?php echo $x_hely; ?>
</span></td>
		<!-- idopont -->
		<td style="width: 6%;"><span>
<?php echo $x_idopont; ?>
</span></td>
		<!-- lejart -->
		<td style="width: 6%;"><span>
<?php
switch ($x_lejart) {
	case "i":
		$sTmp = "igen";
		break;
	case "n":
		$sTmp = "nem";
		break;
	default:
		$sTmp = "";
}
$ox_lejart = $x_lejart; // Backup original value
$x_lejart = $sTmp;
?>
<?php echo $x_lejart; ?>
<?php $x_lejart = $ox_lejart; // Restore original value ?>
</span></td>
		<!-- kepek -->
		<td style="width: 12%;"><span>
<?php echo $x_kepek; ?>
</span></td>
<td><span class="phpmaker"><a href="<?php if ($x_kod <> "") {echo "esemenyview.php?kod=" . urlencode($x_kod); } else { echo "javascript:alert('Hibás rekord! Kulcs nem lehet üres');";} ?>">Megtekint</a></span></td>
<td><span class="phpmaker"><a href="<?php if ($x_kod <> "") {echo "esemenyedit.php?kod=" . urlencode($x_kod); } else { echo "javascript:alert('Hibás rekord! Kulcs nem lehet üres');";} ?>">Szerkesztés</a></span></td>
<td><span class="phpmaker"><a href="<?php if ($x_kod <> "") {echo "esemenyadd.php?kod=" . urlencode($x_kod); } else { echo "javascript:alert('Hibás rekord! Kulcs nem lehet üres');";} ?>">Másol</a></span></td>
<td><span class="phpmaker"><input type="checkbox" name="key_d[]" value="<?php echo $x_kod; ?>" class="phpmaker" onclick='ew_clickmultidelete(this);'>Töröl</span></td>
	</tr>
<?php
	}
}
?>
</table>
<?php if ($nRecActual > 0) { ?>
<p>
	<input type="button" name="btndelete" value="Kiválasztottak törlése" onClick="if (!EW_selected(this)) alert('Nincs rekord kiválasztva'); else {this.form.action='esemenydelete.php';this.form.encoding='application/x-www-form-urlencoded';this.form.submit();}">
</p>
<?php } ?>
</form>
<?php 
}

// Close recordset and connection
phpmkr_free_result($rs);
phpmkr_db_close($conn);
?>
<?php include ("footer.php") ?>
<?php

//-------------------------------------------------------------------------------
// Function ResetSearch
// - Clear all search parameters

function ResetSearch() 
{

	// Clear search where
	$sSrchWhere = "";
	$_SESSION[ewSessionTblSearchWhere] = $sSrchWhere;

	// Clear advanced search parameters
	$_SESSION[ewSessionTblBasicSrch] = "";
	$_SESSION[ewSessionTblBasicSrchType] = "";
}

//-------------------------------------------------------------------------------
// Function RestoreSearch
// - Restore all search parameters
//

function RestoreSearch()
{

	// Restore advanced search settings
	$GLOBALS["psearch"] = @$_SESSION[ewSessionTblBasicSrch];
	$GLOBALS["psearchtype"] = @$_SESSION[ewSessionTblBasicSrchType];
}

//-------------------------------------------------------------------------------
// Function SetUpSortOrder
// - Set up Sort parameters based on Sort Links clicked
// - Variables setup: sOrderBy, Session(TblOrderBy), Session(Tbl_Field_Sort)

function SetUpSortOrder()
{
	global $sOrderBy;
	global $sDefaultOrderBy;

	// Check for an Order parameter
	if (strlen(@$_GET["order"]) > 0) {
		$sOrder = @$_GET["order"];

		// Field `datum`
		if ($sOrder == "datum") {
			$sSortField = "`datum`";
			$sLastSort = @$_SESSION[ewSessionTblSort . "_x_datum"];
			$sThisSort = ($sLastSort == "ASC") ? "DESC" : "ASC";
			$_SESSION[ewSessionTblSort . "_x_datum"] = $sThisSort;
		} else {
			if (@$_SESSION[ewSessionTblSort . "_x_datum"] <> "") { @$_SESSION[ewSessionTblSort . "_x_datum"] = ""; }
		}

		// Field `hely`
		if ($sOrder == "hely") {
			$sSortField = "`hely`";
			$sLastSort = @$_SESSION[ewSessionTblSort . "_x_hely"];
			$sThisSort = ($sLastSort == "ASC") ? "DESC" : "ASC";
			$_SESSION[ewSessionTblSort . "_x_hely"] = $sThisSort;
		} else {
			if (@$_SESSION[ewSessionTblSort . "_x_hely"] <> "") { @$_SESSION[ewSessionTblSort . "_x_hely"] = ""; }
		}

		// Field `idopont`
		if ($sOrder == "idopont") {
			$sSortField = "`idopont`";
			$sLastSort = @$_SESSION[ewSessionTblSort . "_x_idopont"];
			$sThisSort = ($sLastSort == "ASC") ? "DESC" : "ASC";
			$_SESSION[ewSessionTblSort . "_x_idopont"] = $sThisSort;
		} else {
			if (@$_SESSION[ewSessionTblSort . "_x_idopont"] <> "") { @$_SESSION[ewSessionTblSort . "_x_idopont"] = ""; }
		}

		// Field `lejart`
		if ($sOrder == "lejart") {
			$sSortField = "`lejart`";
			$sLastSort = @$_SESSION[ewSessionTblSort . "_x_lejart"];
			$sThisSort = ($sLastSort == "ASC") ? "DESC" : "ASC";
			$_SESSION[ewSessionTblSort . "_x_lejart"] = $sThisSort;
		} else {
			if (@$_SESSION[ewSessionTblSort . "_x_lejart"] <> "") { @$_SESSION[ewSessionTblSort . "_x_lejart"] = ""; }
		}

		// Field `kepek`
		if ($sOrder == "kepek") {
			$sSortField = "`kepek`";
			$sLastSort = @$_SESSION[ewSessionTblSort . "_x_kepek"];
			$sThisSort = ($sLastSort == "ASC") ? "DESC" : "ASC";
			$_SESSION[ewSessionTblSort . "_x_kepek"] = $sThisSort;
		} else {
			if (@$_SESSION[ewSessionTblSort . "_x_kepek"] <> "") { @$_SESSION[ewSessionTblSort . "_x_kepek"] = ""; }
		}
		$_SESSION[ewSessionTblOrderBy] = $sSortField . " " . $sThisSort;
		$_SESSION[ewSessionTblStartRec] = 1;
	}
	$sOrderBy = @$_SESSION[ewSessionTblOrderBy];
	if ($sOrderBy == "") {
		$sOrderBy = ewSqlOrderBy;
		@$_SESSION[ewSessionTblOrderBy] = $sOrderBy;
		if ($sOrderBy <> "") {
			$arOrderBy = explode(",", ewSqlOrderBySessions);
			for($i=0; $i<count($arOrderBy); $i+=2) {
				@$_SESSION[ewSessionTblSort . "_" . $arOrderBy[$i]] = $arOrderBy[$i+1];
			}
		}
	}
}

//-------------------------------------------------------------------------------
// Function SetUpStartRec
//- Set up Starting Record parameters based on Pager Navigation
// - Variables setup: nStartRec

function SetUpStartRec()
{

	// Check for a START parameter
	global $nStartRec;
	global $nDisplayRecs;
	global $nTotalRecs;
	if (strlen(@$_GET[ewTblStartRec]) > 0) {
		$nStartRec = @$_GET[ewTblStartRec];
		$_SESSION[ewSessionTblStartRec] = $nStartRec;
	} elseif (strlen(@$_GET["pageno"]) > 0) {
		$nPageNo = @$_GET["pageno"];
		if (is_numeric($nPageNo)) {
			$nStartRec = ($nPageNo-1)*$nDisplayRecs+1;
			if ($nStartRec <= 0) {
				$nStartRec = 1;
			} elseif ($nStartRec >= (($nTotalRecs-1)/$nDisplayRecs)*$nDisplayRecs+1) {
				$nStartRec = (($nTotalRecs-1)/$nDisplayRecs)*$nDisplayRecs+1;
			}
			$_SESSION[ewSessionTblStartRec] = $nStartRec;
		} else {
			$nStartRec = @$_SESSION[ewSessionTblStartRec];
			if  (!(is_numeric($nStartRec)) || ($nStartRec == "")) {
				$nStartRec = 1; // Reset start record counter
				$_SESSION[ewSessionTblStartRec] = $nStartRec;
			}
		}
	} else {
		$nStartRec = @$_SESSION[ewSessionTblStartRec];
		if (!(is_numeric($nStartRec)) || ($nStartRec == "")) {
			$nStartRec = 1; // Reset start record counter
			$_SESSION[ewSessionTblStartRec] = $nStartRec;
		}
	}
}

//-------------------------------------------------------------------------------
// Function ResetCmd
// - Clear list page parameters
// - RESET: reset search parameters
// - RESETALL: reset search & master/detail parameters
// - RESETSORT: reset sort parameters

function ResetCmd()
{

	// Get Reset command
	if (strlen(@$_GET["cmd"]) > 0) {
		$sCmd = @$_GET["cmd"];
		if (strtolower($sCmd) == "reset") { // Reset search criteria
			ResetSearch();
		} elseif (strtolower($sCmd) == "resetall") { // Reset search criteria and session vars
			ResetSearch();
		} elseif (strtolower($sCmd) == "resetsort") { // Reset sort criteria
			$sOrderBy = "";
			$_SESSION[ewSessionTblOrderBy] = $sOrderBy;
			if (@$_SESSION[ewSessionTblSort . "_x_datum"] <> "") { $_SESSION[ewSessionTblSort . "_x_datum"] = ""; }
			if (@$_SESSION[ewSessionTblSort . "_x_hely"] <> "") { $_SESSION[ewSessionTblSort . "_x_hely"] = ""; }
			if (@$_SESSION[ewSessionTblSort . "_x_idopont"] <> "") { $_SESSION[ewSessionTblSort . "_x_idopont"] = ""; }
			if (@$_SESSION[ewSessionTblSort . "_x_lejart"] <> "") { $_SESSION[ewSessionTblSort . "_x_lejart"] = ""; }
			if (@$_SESSION[ewSessionTblSort . "_x_kepek"] <> "") { $_SESSION[ewSessionTblSort . "_x_kepek"] = ""; }
		}

		// Reset start position (Reset command)
		$nStartRec = 1;
		$_SESSION[ewSessionTblStartRec] = $nStartRec;
	}
}
?>
