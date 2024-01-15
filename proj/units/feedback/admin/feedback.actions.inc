<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'feedback/feedback.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class Feedback extends UnitAccess implements Consts\Feedback {
		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	Feedback::RegActions();