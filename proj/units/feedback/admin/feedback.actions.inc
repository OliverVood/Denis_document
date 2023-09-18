<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'feedback/feedback.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Feedback extends Units implements Consts\Feedback {
		public static Action $out_menu;

		protected function __construct($file) {
			parent::__construct($file);
		}

		public static function RegActions() {
			self::$out_menu		= new Action('always', 'always');
		}

	}

	Feedback::RegActions();