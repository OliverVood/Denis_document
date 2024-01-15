<?php

	namespace Proj\Admin\Actions;

	use Base\UnitAccess;
	use Proj\Units\Consts;

	require DIR_UNITS . 'statistics/statistics.consts.inc';

	abstract class Statistics extends UnitAccess implements Consts\Statistics {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Statistics::RegActions();