<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              Megrendel�s" . "\n\n ";
	$eleje_text = $eleje_text . "     N�v: " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     Postai c�m: " . $sz2 . "\n ";
	$eleje_text = $eleje_text . "     Telefonsz�m: " . $sz3 . "\n ";
	$eleje_text = $eleje_text . "     Email c�m: " . $sz4 . "\n ";
	$eleje_text = $eleje_text . "     Term�k le�r�sa: " . $sz5 . "\n ";
	$eleje_text = $eleje_text . "     Darabsz�m: "  . $sz6 . "\n ";
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'mgy - megrendel�s',$message2,'From: rendeles@mgy.hu');
		mail ($emailcc,'mgy - megrendel�s',$message2,'From: rendeles@mgy.hu');		
?>