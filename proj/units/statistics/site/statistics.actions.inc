<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'statistics/statistics.consts.inc';

	use Base\Unit;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Statistics extends Unit implements Consts\Statistics {
		public static Action $collect;
		public static Action $act;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {
			self::$collect				= new Action('always', 'always');
			self::$act					= new Action(self::NAME, 'act', 'default');
		}

	}

	Statistics::RegActions();