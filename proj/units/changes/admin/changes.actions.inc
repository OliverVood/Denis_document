<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'changes/changes.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class Changes extends UnitAccess implements Consts\Changes {
		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Changes::RegActions();