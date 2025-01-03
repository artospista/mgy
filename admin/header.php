<html>
<head>
<title>Események</title>
<link href="mgy.css" rel="stylesheet" type="text/css" />
<meta http-equiv="Content-Type" content="text/html; charset=windows-1250" />
<meta name="generator" content="PHPMaker v4.0.0.1" />
</head>
<body>
<table width="100%" height="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
	<td height="100%" rowspan="10" width="5%">&nbsp;</td>
</tr>
<tr>
	<td height="20" width="95%" valign="top"><span class="phpmaker"><b>Események</b></span>&nbsp;
		<?php if (IsLoggedIn()) { ?>
			<span class="phpmaker"><a href="logout.php">Kijelentkezés</a></span>&nbsp;
		<?php } elseif (substr(ewScriptFileName(), 0 - strlen("login.php")) <> "login.php") { ?>
			<span class="phpmaker"><a href="login.php">Bejelentkezés</a></span>&nbsp;
		<?php } ?>
	</td></tr><tr>
	<!-- right column -->
	<td width="100%" valign="top">
