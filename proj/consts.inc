<?php

	const DIR_UNITS					= DIR_PROJ . 'units/';
	const DIR_RESOURCE				= DIR_PROJ . 'resource/';
	const DIR_RESOURCE_IMAGE		= DIR_RESOURCE . 'image/';
	const DIR_FILES					= DIR_PROJ . 'files/';
	const DIR_FILES_IMAGE			= DIR_FILES . 'image/';

	const DIR_REL_ROOT				= '/';
	const DIR_REL_PROJ				= DIR_REL_ROOT . 'proj/';
	const DIR_REL_TPL				= DIR_REL_PROJ . 'templates/';
	const DIR_REL_RESOURCE			= DIR_REL_PROJ . 'resource/';
	const DIR_REL_RESOURCE_IMAGE	= DIR_REL_RESOURCE . 'image/';
	const DIR_REL_FILES				= DIR_REL_PROJ . 'files/';
	const DIR_REL_FILES_IMAGE		= DIR_REL_FILES . 'image/';

	define('PROTOCOL', (isset($_SERVER['HTTPS'])) ? 'https' : 'http');
	define('ADDRESS', PROTOCOL . '://' . $_SERVER['SERVER_NAME']);