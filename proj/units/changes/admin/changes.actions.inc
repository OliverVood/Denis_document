<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'changes/changes.consts.inc';

	use Base\Units;
	use Proj\Units\Consts;

	abstract class Changes extends Units implements Consts\Changes {
		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, $file);
		}

		public static function RegActions() { }

	}

	Changes::RegActions();