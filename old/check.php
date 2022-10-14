<?php

	require 'index.php';

	$t = $db->Check();
	SendJSONData($t);