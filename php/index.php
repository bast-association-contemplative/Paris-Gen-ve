<?php
	
	$data = $_GET['p'];
	
	$fichier = fopen('variable.txt', 'r+');
		
		$filedata = fgets($fichier);
			
		fseek($fichier, 0);
		fputs($fichier, $data);
		
	fclose($fichier);
	
	echo($filedata);
?>