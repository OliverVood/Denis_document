<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'news/news.consts.inc';

	use Base\Units;
	use Proj\Units\Consts;

	abstract class News extends Units implements Consts\News {
		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, $file);
		}

		public static function RegActions() {  }

	}

	News::RegActions();