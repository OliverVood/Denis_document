<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'catalogs/site/catalogs.actions.inc';

	require DIR_UNITS . 'catalogs/site/views/buttons.tpl';
	require DIR_UNITS . 'catalogs/site/views/estimate.tpl';
	require DIR_UNITS . 'catalogs/site/views/certificate.tpl';
	require DIR_UNITS . 'catalogs/site/views/priceList.tpl';

	use Base\Instance;
	use Proj\Site\Actions;

	class Catalogs extends Actions\Catalogs {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

	}

	Catalogs::init();