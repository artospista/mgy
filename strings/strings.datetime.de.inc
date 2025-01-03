<?php
	// ISO-Latin-1 encoded (due to PHP bug)
	$fileinfo	= array(
		'code'		=> 'de',
		'name'		=> 'Deutsch',
		'english'	=> 'german',
		'is_utf8'	=> false,
	);
	$strings	= array(
		'de'		=> array( // deutsch (german)
			'is_utf8'	=> false,
			'days'		=> array(
				0			=> 'Montag',
				1			=> 'Dienstag',
				2			=> 'Mittwoch',
				3			=> 'Donnerstag',
				4			=> 'Freitag',
				5			=> 'Samstag',
				6			=> 'Sonntag',
			),
			'months'	=> array(
				1			=> 'Januar',
				2			=> 'Februar',
				3			=> 'März',
				4			=> 'April',
				5			=> 'Mai',
				6			=> 'Juni',
				7			=> 'Juli',
				8			=> 'August',
				9			=> 'September',
				10			=> 'Oktober',
				11			=> 'November',
				12			=> 'Dezember',
			),
			'errors'		=> array(
				'nomatch'			=> 'Es wurde keine Datums- oder Zeitangabe im Text erkannt.',
				'invalidday'		=> 'Der Monat %B hat weniger als %i Tage.',
				'invalidmonth'		=> 'UngŸltige Monatsangabe \'%m\'.',
				'invalidmonthname'	=> 'Unbekannter Monatsname \'%B\'.',
				'invalidyear'		=> 'Das Jahr %Y is ausserhalb des GŸltigkeitsbereichs.',
				'invalidhour'		=> 'UngŸltige Stundenangabe \'%H\' (0-23 ist erlaubt).',
				'invalidminute'		=> 'UngŸltige Minutenangabe \'%M\' (0-59 ist erlaubt).',
				'invalidsecond'		=> 'UngŸltige Sekundenangabe \'%S\' (0-59 ist erlaubt).',
			),
			'representations'	=> array(
				'time'	=> "%H:%M",
				'date'	=> "%d.%m.'%y",
				'short'	=> "%a, %d. %b %y",
				'long'	=> "%A, %d. %B %Y",
			),
			'zodiacs'	=> array(
				'aquarius'		=> 'Wassermann',	// 21.01. - 19.02.
				'aries'			=> 'Widder',		// 21.03. - 20.04.
				'cancer'		=> 'Krebs',			// 22.06. - 22.07.
				'capricornus'	=> 'Steinbock',		// 22.12. - 20.01.
				'gemini'		=> 'Zwilling',		// 22.05. - 21.06.
				'leo'			=> 'Löwe',			// 23.07. - 23.08.
				'libra'			=> 'Waage',			// 23.09. - 22.10.
				'pisces'		=> 'Fisch',			// 20.02. - 20.03.
				'sagittarius'	=> 'Schütze',		// 23.11. - 21.12
				'scorpius'		=> 'Skorpion',		// 24.10. - 22.11
				'taurus'		=> 'Stier',			// 21.04. - 21.05.
				'virgo'			=> 'Jungfrau',		// 24.08. - 23.09.
			),
			'timezones'	=> array(
				'normal'	=> array(
					'UTC'		=> array('WEZ', 'Westeuropäische Zeit'),
					'UTC+1'		=> array('MEZ', 'Mitteleuropäische Zeit'),
				),
				'dst'		=> array(
					'UTC+1'		=> array('MESZ', 'Mitteleuropäische Sommerzeit'),
				),
			),
		),
	);
	$recognize	= array(
		'de'		=> array(
			'is_utf8' => false,
			'months'	=> array(
				3	=> array('Maerz'),
			),
			'patterns'	=> array(
				'#(gestern)#'										=> array('yesterday'),	//current date-1d
				'#(heute)#'											=> array('today'),		//current date
				'#(morgen)#'										=> array('tomorrow'),	//current date+1d
				'#(jetzt)#'											=> array('now'),		//current datetime
				'#(\d{1,2})\.(\d{1,2})\.(\d{4}|\d{2})?#'			=> array('d','m','y'),	//23.5.((19)82) | 23. 5. ((19)82)
				'#(\d{1,2})\. (\d{1,2})\. (\d{4}|\d{2}(?![.:]))?#'	=> array('d','m','y'),	//23.5.((19)82) | 23. 5. ((19)82)
				'#(\d{1,2})\. (\w{3,})\.? ?(\d{4}|\d{2})?#'			=> array('d','T','y'),	//23. Mai ((19)82)
				'#(\d{1,2})\:(\d{1,2})h?#'							=> array('H','M'),		//19:42:57
				'#(\d{1,2})\:(\d{1,2})(h| uhr)?#'					=> array('H','M'),		//19:42 | 19:42h | 19:42 Uhr
				'#(?<!\.)(\d{1,2})\.(\d{1,2})(?!\.)(h| uhr)?#'		=> array('H','M', 0),	//19.42 | 19.42h | 19.42 Uhr
				'#(\d{1,2})(h| uhr)#'								=> array('H', 0),		//19h | 19 Uhr
			),
		),
	);
?>