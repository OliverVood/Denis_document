<?php

	namespace Proj\Site;

	class Params {

		static string $support = 'support@_____.com';
		static string $site_name;
	}

	Params::$site_name = $_SERVER['SERVER_NAME'];