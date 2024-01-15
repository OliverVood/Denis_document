<?php

	namespace Proj\Site\Actions;

	require DIR_UNITS . 'news/news.consts.inc';

	use Base\Unit;
	use Proj\Units\Consts;

	abstract class News extends Unit implements Consts\News {

		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	News::RegActions();