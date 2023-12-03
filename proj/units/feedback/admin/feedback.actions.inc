<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'feedback/feedback.consts.inc';

	use Base\Units;
	use Proj\Units\Consts;

	abstract class Feedback extends Units implements Consts\Feedback {
		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, $file);
		}

		public static function RegActions() {  }

	}

	Feedback::RegActions();