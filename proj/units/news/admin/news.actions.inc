<?php

	namespace Proj\Admin\Actions;

	require DIR_UNITS . 'news/news.consts.inc';

	use Base\UnitAccess;
	use Proj\Units\Consts;

	abstract class News extends UnitAccess implements Consts\News {
		protected function __construct(string $file) {
			parent::__construct(self::ID, self::NAME, self::TITLE, $file);
		}

		public static function RegActions() {  }

	}

	News::RegActions();