<?php

	namespace Proj\Admin\Actions;

	use Base\UnitAccess;
	use Proj\Units\Consts;

	require DIR_UNITS . 'catalogs/catalogs.consts.inc';

	abstract class Catalogs extends UnitAccess implements Consts\Catalogs {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Catalogs::RegActions();