<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'news/news.consts.inc';

	use Base\Units;
	use Base\Action;
	use Proj\Units\Consts;

	abstract class News extends Units implements Consts\News {
		public static Action $last;
		public static Action $all;
		public static Action $show;

		protected function __construct($file) {
			parent::__construct($file);
		}

		public static function RegActions() {
			self::$last					= new Action('null', 'null');
			self::$all					= new Action(self::NAME, 'null', 'default');
			self::$show					= new Action(self::NAME, 'show', "/news/show?id=%id%");
		}

	}

	News::RegActions();