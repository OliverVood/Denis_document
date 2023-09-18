<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'changes/changes.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Changes extends Units implements Consts\Changes {
		public static Action $out_menu;

		protected function __construct($file) {
			parent::__construct($file);
		}

		public static function RegActions() {
			self::$out_menu		= new Action('always', 'always');
		}

	}

	Changes::RegActions();