<?php

	namespace Proj\Site\Units\XHR;

	require DIR_UNITS . 'catalogs/site/catalogs.actions.inc';

	use Base\Instance;
	use Proj\Site\Actions;

	class Catalogs extends Actions\Catalogs {
		use Instance;

		private function __construct() {
			parent::__construct();
		}

	}

	Catalogs::init();