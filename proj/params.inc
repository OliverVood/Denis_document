<?php

	namespace Proj;

	class Params {

		static string $support = EMAIL_SUPPORT;
		static string $site_name = 'DocRoom.pro';
		static string $site_address;
	}

	Params::$site_address = $_SERVER['SERVER_NAME'];