<?php

	namespace Proj\Admin\Units;

    require DIR_UNITS . 'pages/admin/pages.actions.inc';

	use Base\Instance;
	use Proj\Units\Consts;
	use Proj\Admin\Actions;

	class Pages extends Actions\Pages implements Consts\Pages {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

	}

	Pages::init();