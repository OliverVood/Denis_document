<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'pages/pages.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class Pages extends UnitAccess implements Consts\Pages {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Pages::RegActions();