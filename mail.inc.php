<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              Jegyrendel�s - Miller el�ad�s" . "\n\n ";
	$eleje_text = $eleje_text . "     Megrendelt jegyek sz�ma (db): " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     �tv�telkor fizetend� �sszeg (Ft): " . $sz2 . "\n ";
	$eleje_text = $eleje_text . "     Megrendel� neve: " . $sz3 . "\n ";
	$eleje_text = $eleje_text . "     Ir�ny�t�sz�m: " . $sz4 . "\n ";
	$eleje_text = $eleje_text . "     V�ros: " . $sz5 . "\n ";
	$eleje_text = $eleje_text . "     Utca, h�zsz�m: " . $sz6 . "\n ";
	$eleje_text = $eleje_text . "     �rtes�t�si e-mail c�m: " . $sz7 . "\n ";
	$eleje_text = $eleje_text . "     1 �d�t�/�sv�nyv�z, 1 k�v�/tea, �des-s�s apr�s�tem�ny 1.320,-Ft/k�v�sz�net - igen : " . $pipa01 . "\n ";
	$eleje_text = $eleje_text . "     1 �d�t�/�sv�nyv�z, 1 k�v�/tea, �des-s�s apr�s�tem�ny 1.320,-Ft/k�v�sz�net - nem : " . $pipa02 . "\n ";
	$eleje_text = $eleje_text . "     Ha igen, akkor 1 sz�netben (1.320,-Ft) (db): " . $sz8 . "\n ";
	$eleje_text = $eleje_text . "     Mindk�t sz�netben (2.640,-Ft)(db): " . $sz9 . "\n ";
	$eleje_text = $eleje_text . "     1 �d�t�/�sv�nyv�z, 1 k�v�/tea 1.100,-Ft/k�v�sz�net  - igen: " . $pipa03 . "\n ";
	$eleje_text = $eleje_text . "     1 �d�t�/�sv�nyv�z, 1 k�v�/tea 1.100,-Ft/k�v�sz�net  - nem: " . $pipa04 . "\n ";
	$eleje_text = $eleje_text . "     Ha igen, akkor 1 sz�netben(1.100,-Ft) (db): " . $sz10 . "\n ";
	$eleje_text = $eleje_text . "     Mindk�t sz�netben (2.200,-Ft) (db): " . $sz11 . "\n ";
	$eleje_text = $eleje_text . "     Vev� neve: " . $sz12 . "\n ";
	$eleje_text = $eleje_text . "     Ir�ny�t�sz�m: " . $sz13 . "\n ";
	$eleje_text = $eleje_text . "     V�ros: " . $sz14 . "\n ";	
	$eleje_text = $eleje_text . "     Utca/h�zsz�m: " . $sz15 . "\n ";
	$eleje_text = $eleje_text . "     Ad�azonos�t� sz�m: " . $sz16 . "\n ";	
	$eleje_text = $eleje_text . "     K�z�ss�gi ad�sz�m: " . $sz17 . "\n ";
	
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'Jegyrendel�s mgy',$message2,'From: jegy@mgy.hu');
		mail ($emailcc,'Jegyrendel�s mgy',$message2,'From: jegy@mgy.hu');		
?>