<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'catalogs/admin/catalogs.actions.inc';

	use Base\Instance;
	use Proj\Admin\Actions;
	use Proj\Units\Consts;

	class Catalogs extends Actions\Catalogs implements Consts\Catalogs {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

	}

	Catalogs::init();