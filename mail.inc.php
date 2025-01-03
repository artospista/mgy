<?

//function sendemail($email, $line, $totalsum, $username, $txt4, $txt5, $message) {
	/*
		Used in the initial registration function
		as well as the change email address function
	*/


	$eleje_text = "                              Jegyrendelés - Miller elõadás" . "\n\n ";
	$eleje_text = $eleje_text . "     Megrendelt jegyek száma (db): " . $sz1 . "\n ";
	$eleje_text = $eleje_text . "     Átvételkor fizetendõ összeg (Ft): " . $sz2 . "\n ";
	$eleje_text = $eleje_text . "     Megrendelõ neve: " . $sz3 . "\n ";
	$eleje_text = $eleje_text . "     Irányítószám: " . $sz4 . "\n ";
	$eleje_text = $eleje_text . "     Város: " . $sz5 . "\n ";
	$eleje_text = $eleje_text . "     Utca, házszám: " . $sz6 . "\n ";
	$eleje_text = $eleje_text . "     Értesítési e-mail cím: " . $sz7 . "\n ";
	$eleje_text = $eleje_text . "     1 üdítõ/ásványvíz, 1 kávé/tea, édes-sós aprósütemény 1.320,-Ft/kávészünet - igen : " . $pipa01 . "\n ";
	$eleje_text = $eleje_text . "     1 üdítõ/ásványvíz, 1 kávé/tea, édes-sós aprósütemény 1.320,-Ft/kávészünet - nem : " . $pipa02 . "\n ";
	$eleje_text = $eleje_text . "     Ha igen, akkor 1 szünetben (1.320,-Ft) (db): " . $sz8 . "\n ";
	$eleje_text = $eleje_text . "     Mindkét szünetben (2.640,-Ft)(db): " . $sz9 . "\n ";
	$eleje_text = $eleje_text . "     1 üdítõ/ásványvíz, 1 kávé/tea 1.100,-Ft/kávészünet  - igen: " . $pipa03 . "\n ";
	$eleje_text = $eleje_text . "     1 üdítõ/ásványvíz, 1 kávé/tea 1.100,-Ft/kávészünet  - nem: " . $pipa04 . "\n ";
	$eleje_text = $eleje_text . "     Ha igen, akkor 1 szünetben(1.100,-Ft) (db): " . $sz10 . "\n ";
	$eleje_text = $eleje_text . "     Mindkét szünetben (2.200,-Ft) (db): " . $sz11 . "\n ";
	$eleje_text = $eleje_text . "     Vevõ neve: " . $sz12 . "\n ";
	$eleje_text = $eleje_text . "     Irányítószám: " . $sz13 . "\n ";
	$eleje_text = $eleje_text . "     Város: " . $sz14 . "\n ";	
	$eleje_text = $eleje_text . "     Utca/házszám: " . $sz15 . "\n ";
	$eleje_text = $eleje_text . "     Adóazonosító szám: " . $sz16 . "\n ";	
	$eleje_text = $eleje_text . "     Közösségi adószám: " . $sz17 . "\n ";
	
	    
     $message2 = "\n".
	 $eleje_text . 
		$uzenet0 . "\n\n ".
		$uzenet1 . "\n\n ".
		$line . "\n\n ".
		$message;

// ez a teszt email cimre..
		mail ($emailto,'Jegyrendelés mgy',$message2,'From: jegy@mgy.hu');
		mail ($emailcc,'Jegyrendelés mgy',$message2,'From: jegy@mgy.hu');		
?>