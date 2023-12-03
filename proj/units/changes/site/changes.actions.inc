<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'changes/changes.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class Changes extends Units implements Consts\Changes {
		public static Action $last;
		public static Action $list;
		public static Action $show;

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, $file);
		}

		public static function RegActions() {
			self::$last					= new Action('null', 'null');
			self::$list					= new Action(self::NAME, 'null', 'default');
			self::$show					= new Action(self::NAME, 'show', "/changes/show?id=%id%");
		}

	}

	Changes::RegActions();