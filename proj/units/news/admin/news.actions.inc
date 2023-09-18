<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'news/news.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class News extends Units implements Consts\News {
		public static Action $out_menu;

		protected function __construct($file) {
			parent::__construct($file);
		}

		public static function RegActions() {
			self::$out_menu		= new Action('always', 'always');
		}

	}

	News::RegActions();