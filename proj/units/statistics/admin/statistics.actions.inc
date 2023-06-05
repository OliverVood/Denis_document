<?php

	namespace Proj\Admin\Actions;

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	require DIR_UNITS . 'statistics/statistics.consts.inc';

	abstract class Statistics extends Units implements Consts\Statistics {
		public static Action $out_menu;

		protected function __construct() {
			parent::__construct(self::ID, self::NAME);
		}

		public static function RegActions() {
			self::$out_menu		= new Action('always', 'always');
		}

	}

	Statistics::RegActions();