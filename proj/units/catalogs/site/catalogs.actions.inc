<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'catalogs/catalogs.consts.inc';

	use Base\Unit;
	use Proj\Units\Consts;

	abstract class Catalogs extends Unit implements Consts\Catalogs {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() { }

	}

	Catalogs::RegActions();