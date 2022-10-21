<?php

	const DIR_ROOT					= __DIR__ . '/../';
	const DIR_BASE					= DIR_ROOT . 'base/';
	const DIR_PROJ					= DIR_ROOT . 'proj/';
	const DIR_UNITS					= DIR_PROJ . 'units/';

	const DIR_REL_ROOT				= '/';
	const DIR_REL_PROJ				= DIR_REL_ROOT . 'proj/';
	const DIR_REL_TPL				= DIR_REL_PROJ . 'templates/';

	define('PROTOCOL', (isset($_SERVER['HTTPS'])) ? 'https' : 'http');;
	define('ADDRESS', PROTOCOL . '://' . $_SERVER['SERVER_NAME']);