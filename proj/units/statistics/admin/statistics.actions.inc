<?php

	namespace Proj\Admin\Actions;

	use Base\Units;
	use Proj\Units\Consts;

	require DIR_UNITS . 'statistics/statistics.consts.inc';

	abstract class Statistics extends Units implements Consts\Statistics {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, $file);
		}

		public static function RegActions() {  }

	}

	Statistics::RegActions();