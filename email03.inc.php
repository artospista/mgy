<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              Megrendelés" . "\n\n ";
	$eleje_text = $eleje_text . "     Név: " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     Postai cím: " . $sz2 . "\n ";
	$eleje_text = $eleje_text . "     Telefonszám: " . $sz3 . "\n ";
	$eleje_text = $eleje_text . "     Email cím: " . $sz4 . "\n ";
	$eleje_text = $eleje_text . "     Termék leírása: " . $sz5 . "\n ";
	$eleje_text = $eleje_text . "     Darabszám: "  . $sz6 . "\n ";
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'mgy - megrendelés',$message2,'From: rendeles@mgy.hu');
		mail ($emailcc,'mgy - megrendelés',$message2,'From: rendeles@mgy.hu');		
?>